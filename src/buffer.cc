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
}

BufferManager::~BufferManager() {
    for (const auto& iter : buffer_pool_) {
        delete iter.second;
    }
    delete dm_;
    delete replacer_;
    delete[] buffer_pool_;
}

auto BufferManager::AccessBlock(const block_type& block_id) -> Buffer* {}

auto BufferManager::FlushBlock(const block_type& block_id) -> bool {}
}  // namespace FileSystem
