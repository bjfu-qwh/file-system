//
// Created by 20473 on 2024/3/30.
//

#include "include/buffer.h"

#include "cstring"

namespace FileSystem {
Buffer::Buffer(const block_type& block_id, const char* data)
    : block_id_(block_id) {
    strncpy(data_, data, BLOCK_SIZE);
    ref_count_ = 0;
}

Buffer::Buffer(const Buffer& other) {
    is_dirty_ = other.is_dirty_;
    ref_count_ = other.ref_count_;
    timestamp_ = other.timestamp_;
    strncpy(data_, other.data_, BLOCK_SIZE);
}

auto Buffer::GetBlockId() const -> block_type { return block_id_; }

auto Buffer::GetRefCount() const -> size_t { return ref_count_; }

auto Buffer::GetData() -> char* {
    auto data_copy = new char[BLOCK_SIZE];
    lock_.RLock();
    strncpy(data_copy, data_, BLOCK_SIZE);
    lock_.RUnlock();
    return data_copy;
}

auto Buffer::IsDirty() const -> bool { return is_dirty_; }

auto Buffer::GetTimestamp() -> size_t {
    lock_.RLock();
    size_t timestamp = timestamp_;
    lock_.RUnlock();
    return timestamp;
}

void Buffer::SetTimestamp(const size_t& new_timestamp) {
    lock_.WLock();
    timestamp_ = new_timestamp;
    lock_.WUnlock();
}

void Buffer::Increment() {
    lock_.WLock();
    ++ref_count_;
    lock_.WUnlock();
}

void Buffer::Decrement() {
    lock_.WLock();
    if (ref_count_ > 0) {
        --ref_count_;
    }
    lock_.WUnlock();
}

void Buffer::SetDirty(const bool& is_dirty) { is_dirty_ = is_dirty; }

void Buffer::SetBlockId(const block_type& block_id) { block_id_ = block_id; }

void Buffer::Reset() {
    ref_count_ = 0;
    is_dirty_ = false;
    memset(data_, 0, BLOCK_SIZE);
}

BufferManager::BufferManager(const size_t& buffer_size) {
    buffer_size_ = buffer_size;
    replacer_ = new LRUReplacer(buffer_size);
    dm_ = new DiskManager();
    buffer_pool_ = new Buffer[buffer_size];
    for (buffer_type id = 0; id < buffer_size; ++id) {
        free_list_.Put(id);
    }
}

BufferManager::~BufferManager() {
    delete dm_;
    delete replacer_;
    delete[] buffer_pool_;
}

auto BufferManager::AccessBlock(const block_type& block_id) -> Buffer* {
    mu_.lock();
    buffer_type buffer_id{INVALID_BUFFER_ID};
    if (block_2_buffer_.find(block_id) == block_2_buffer_.end()) {
        if (free_list_.Empty()) {
            if (!replacer_->Evict(buffer_id)) {
                mu_.unlock();
                return nullptr;
            }
        }
        free_list_.Pop(buffer_id);
        block_2_buffer_[block_id] = buffer_id;

        buffer_pool_[buffer_id].Reset();
        buffer_pool_[buffer_id].SetBlockId(block_id);
        dm_->ReadBlock(block_id, buffer_pool_[buffer_id].GetData());
    }
    buffer_pool_[buffer_id].Increment();
    replacer_->Record(buffer_id);
    replacer_->SetEvictable(buffer_id,
                            buffer_pool_[buffer_id].GetRefCount() == 0);
    mu_.unlock();
    return &buffer_pool_[buffer_id];
}

auto BufferManager::FlushBlock(const block_type& block_id) -> bool {
    mu_.lock();
    const auto buffer_id = block_2_buffer_.find(block_id);
    if (buffer_id == block_2_buffer_.end()) {
        mu_.unlock();
        return false;
    }
    Buffer& buf = buffer_pool_[buffer_id->second];
    if (buf.IsDirty()) {
        dm_->WriteBlock(block_id, buf.GetData());
        buf.SetDirty(false);
    }
    mu_.unlock();
    return true;
}

auto BufferManager::Unpin(const block_type& block_id, const bool& is_dirty)
    -> bool {
    mu_.lock();
    const auto& search = block_2_buffer_.find(block_id);
    if (search == block_2_buffer_.end()) {
        mu_.unlock();
        return false;
    }
    Buffer& buf = buffer_pool_[search->second];
    if (!buf.GetRefCount()) {
        mu_.unlock();
        return false;
    }
    buf.Decrement();
    if (is_dirty) {
        buf.SetDirty(true);
    }
    replacer_->SetEvictable(search->second, buf.GetRefCount() == 0);
    mu_.unlock();
    return true;
}
}  // namespace FileSystem
