//
// Created by 20473 on 2024/3/30.
//

#ifndef FILE_SYSTEM_BUFFER_H
#define FILE_SYSTEM_BUFFER_H

#include <shared_mutex>

#include "atomic"
#include "config.h"
#include "disk_manager.h"
#include "lru_replacer.h"
#include "mutex"  // NO_LINT
#include "unordered_map"

namespace FileSystem {
class Buffer {
 public:
  explicit Buffer(const block_type &block_id, const char *data);

  [[nodiscard]] auto GetBlockId() const -> block_type;

  [[nodiscard]] auto GetRefCount() const -> size_t;

  [[nodiscard]] auto GetData() const -> char *;

  [[nodiscard]] auto IsDirty() const -> bool;

  [[nodiscard]] auto GetTimestamp() const -> size_t;

  void SetTimestamp(const size_t &new_timestamp);

  void Increment();

  void Decrement();

  void SetDirty(const bool &is_dirty);

  void Reset();

 private:
  block_type block_id_{INVALID_BLOCK_ID}; /**缓存对应块号码，与inode块号等无关*/
  size_t ref_count_{0};                   /**缓存的引用计数*/
  size_t timestamp_{0};                   /**最近一次访问时间*/
  bool is_dirty_{false};
  char data_[BLOCK_SIZE]{'0'}; /**具体数据*/
};

class BufferManager {
 public:
  BufferManager() = delete;

  BufferManager(const BufferManager &other) = delete;

  explicit BufferManager(const size_t &buffer_size);

  ~BufferManager();

  auto AccessBlock(const block_type &block_id) -> Buffer *;

 private:
  size_t buffer_size_{0};                    /**缓存池最大容量*/
  std::shared_lock<std::mutex> shared_lock_; /**全局锁*/
  std::atomic<size_t> next_block_id_{0};     /**用于分配块编号*/
  std::unordered_map<block_type, Buffer *> cache_;
  size_t timestamp_{0};
  DiskManager *dm_;
  LRUReplacer *replacer_;
};
}  // namespace FileSystem
#endif  // FILE_SYSTEM_BUFFER_H
