//
// Created by 20473 on 2024/3/30.
//

#include "include/buffer.h"

#include "cstring"

namespace FileSystem {
Buffer::Buffer(const block_type &block_id, const char *data) : block_id_(block_id) {
  strncpy(data_, data, BLOCK_SIZE);
  ref_count_ = 0;
}

auto Buffer::GetBlockId() const -> block_type { return block_id_; }

auto Buffer::GetRefCount() const -> size_t { return ref_count_; }

auto Buffer::GetData() const -> char * {
  auto data_copy = new char[BLOCK_SIZE];
  strncpy(data_copy, data_, BLOCK_SIZE);
  return data_copy;
}

auto Buffer::IsDirty() const -> bool { return is_dirty_; }

auto Buffer::GetTimestamp() const -> size_t { return timestamp_; }

void Buffer::SetTimestamp(const size_t &new_timestamp) { timestamp_ = new_timestamp; }

void Buffer::Increment() { ++ref_count_; }

void Buffer::Decrement() {
  if (ref_count_ > 0) {
    --ref_count_;
  }
}

void Buffer::SetDirty(const bool &is_dirty) { is_dirty_ = is_dirty; }

void Buffer::Reset() {
  ref_count_ = 0;
  is_dirty_ = false;
  memset(data_, 0, BLOCK_SIZE);
}

BufferManager::BufferManager(const size_t &buffer_size) {
  buffer_size_ = buffer_size;
  replacer_ = new LRUReplacer(buffer_size);
  dm_ = new DiskManager();
}

BufferManager::~BufferManager() {
  for (const auto &iter : cache_) {
    delete iter.second;
  }
  delete dm_;
  delete replacer_;
}

auto BufferManager::AccessBlock(const block_type &block_id) -> Buffer * {
  Buffer *buf = nullptr;
  shared_lock_.lock();
  auto search = cache_.find(block_id);
  if (search != cache_.end()) {
    buf = search->second;
  }
  shared_lock_.unlock();
  return buf;
}
}  // namespace FileSystem
