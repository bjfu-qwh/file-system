//
// Created by 20473 on 2024/3/30.
//

#ifndef FILE_SYSTEM_BUFFER_H
#define FILE_SYSTEM_BUFFER_H

#include <shared_mutex>

#include "atomic"
#include "config.h"
#include "disk_manager.h"
#include "include/rw_lock.h"
#include "lru_replacer.h"
#include "mutex"  // NO_LINT

namespace FileSystem {
class Buffer {
   public:
    explicit Buffer(const block_type& block_id, const char* data);

    Buffer() = default;

    [[nodiscard]] auto GetBlockId() const -> block_type;

    [[nodiscard]] auto GetRefCount() const -> size_t;

    [[nodiscard]] auto GetData() -> char*;

    [[nodiscard]] auto IsDirty() const -> bool;

    [[nodiscard]] auto GetTimestamp() -> size_t;

    void SetTimestamp(const size_t& new_timestamp);

    void Increment();

    void Decrement();

    void SetDirty(const bool& is_dirty);

    void Reset();

   private:
    ReaderWriterLock lock_;
    block_type block_id_{INVALID_BLOCK_ID}; /**缓存对应物理块号码*/
    size_t ref_count_{0};                   /**缓存的引用计数*/
    size_t timestamp_{0};                   /**最近一次访问时间*/
    bool is_dirty_{false};                  /**该缓存是否已被修改*/
    char data_[BLOCK_SIZE]{'0'};            /**具体数据*/
};

class BufferManager {
   public:
    BufferManager() = delete;

    BufferManager(const BufferManager& other) = delete;

    explicit BufferManager(const size_t& buffer_size = BUFFER_POOL_SIZE);

    ~BufferManager();

    auto AccessBlock(const block_type& block_id) -> Buffer*;

    auto FlushBlock(const block_type& block_id) -> bool;

   private:
    size_t buffer_size_{0};                    /**缓存池最大容量*/
    std::shared_lock<std::mutex> shared_lock_; /**全局锁*/
    std::atomic<size_t> next_block_id_{0};     /**用于分配块编号*/
    DiskManager* dm_;                          /**磁盘管理器*/
    LRUReplacer* replacer_;        /**基于lru策略的缓冲区替换*/
    Buffer* buffer_pool_{nullptr}; /**缓冲池*/
};
}  // namespace FileSystem
#endif  // FILE_SYSTEM_BUFFER_H
