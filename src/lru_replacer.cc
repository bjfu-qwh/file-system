//
// Created by 20473 on 2024/7/5.
//

#include "include/lru_replacer.h"

#include <mutex>
#include <variant>

#include "include/exception.h"

namespace FileSystem {
LRUNode::LRUNode(const buffer_type& buffer_id, const size_t& timestamp) {
    timestamp_ = timestamp;
    buffer_id_ = buffer_id;
}

LRUNode::LRUNode(const LRUNode& other) {
    buffer_id_ = other.buffer_id_;
    timestamp_ = other.timestamp_;
    ready_ = other.ready_;
}

void LRUNode::Update(const size_t& new_timestamp) {
    timestamp_ = new_timestamp;
}

auto LRUNode::IsReady() const -> bool { return ready_; }

void LRUNode::SetReady(const bool& ready) { ready_ = ready; }

auto LRUNode::GetBufferId() const -> buffer_type { return buffer_id_; }

auto LRUNode::GetTimestamp() const -> size_t { return timestamp_; }

auto LRUNode::better(const LRUNode& other) const -> bool {
    if (this->GetTimestamp() == other.GetTimestamp()) {
        return this->GetBufferId() < other.GetBufferId();
    }
    return GetTimestamp() < other.GetTimestamp();
}

auto LRUReplacer::GetVictim(buffer_type& victim_id) -> bool {
    std::scoped_lock<std::mutex> lock(mu_);
    auto result = Decide();
    if (result != INVALID_BUFFER_ID && cache_[result]->IsReady()) {
        victim_id = result;
        return true;
    }
    return false;
}

auto LRUReplacer::Evict(buffer_type& buffer_id) -> bool {
    std::scoped_lock<std::mutex> lock(this->mu_);
    auto target = Decide();
    if (target == INVALID_BUFFER_ID) {
        return false;
    }
    --evictable_size_;
    buffer_id = target;
    cache_.erase(target);
    return true;
}

auto LRUReplacer::Remove(const buffer_type& buffer_id) -> bool {
    std::scoped_lock<std::mutex> lock(mu_);
    auto search = cache_.find(buffer_id);
    if (search == cache_.end()) {
        return false;
    }
    if (!search->second->IsReady()) {
        throw SystemExpection("Remove unevictable buffer.");
    }
    --evictable_size_;
    cache_.erase(buffer_id);
    return true;
}

void LRUReplacer::Record(const buffer_type& buffer_id) {
    std::scoped_lock<std::mutex> lock(mu_);
    ++timestamp_;
    if (buffer_id < 0 || buffer_id > size_) {
        throw OutOfRangeException("buffer id larger than replacer's size.");
    }
    auto search = cache_.find(buffer_id);
    if (search != cache_.end()) {
        search->second->Update(timestamp_);
        return;
    }
    cache_[buffer_id] = new LRUNode(buffer_id, timestamp_);
}

LRUReplacer::LRUReplacer(const size_t& size) { size_ = size; }

void LRUReplacer::SetEvictable(const buffer_type& buffer_id,
                               const bool& set_evictable) {
    std::unique_lock<std::mutex> lock(mu_);
    auto target = cache_.at(buffer_id);
    if (target->IsReady() != set_evictable) {
        if (set_evictable) {
            ++evictable_size_;
        } else {
            --evictable_size_;
        }
        target->SetReady(set_evictable);
    }
}

auto LRUReplacer::Decide() const -> buffer_type {
    auto* target = new LRUNode(INVALID_BUFFER_ID, std::variant_npos);
    for (const auto& iter : cache_) {
        if (!iter.second->IsReady()) {
            continue;
        }
        if (iter.second->better(*target)) {
            target = iter.second;
        }
    }
    return target->GetBufferId();
}
}  // namespace FileSystem
