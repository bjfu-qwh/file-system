#ifndef FILE_SYSTEM_BUFFER_H
#define FILE_SYSTEM_BUFFER_H
#include <shared_mutex>

#include "atomic"
#include "config.h"
#include "disk_manager.h"
#include "free_list.h"
#include "lru_replacer.h"
#include "rw_lock.h"

namespace FileSystem {
/**
 *
 */
class Buffer {
   public:
    explicit Buffer(const block_type& block_id, const char* data);

    Buffer() = default;

    Buffer(const Buffer& other);

    [[nodiscard]] auto GetBlockId() const -> block_type;

    [[nodiscard]] auto GetRefCount() const -> size_t;

    [[nodiscard]] auto GetData() -> char*;

    [[nodiscard]] auto IsDirty() const -> bool;

    [[nodiscard]] auto GetTimestamp() -> size_t;

    void SetTimestamp(const size_t& new_timestamp);

    void Increment();

    void Decrement();

    void SetDirty(const bool& is_dirty);

    void SetBlockId(const block_type& block_id);

    void Reset();

   private:
    ReaderWriterLock lock_;
    block_type block_id_{INVALID_BLOCK_ID}; /**缓存对应物理块号码*/
    size_t ref_count_{0};                   /**缓存的引用计数*/
    size_t timestamp_{0};                   /**最近一次访问时间*/
    bool is_dirty_{false};                  /**该缓存是否已被修改*/
    char data_[BLOCK_SIZE]{'0'};            /**具体数据*/
};

/**
 *
 */
class BufferManager {
   public:
    BufferManager() = delete;

    BufferManager(const BufferManager& other) = delete;

    explicit BufferManager(const size_t& buffer_size = BUFFER_POOL_SIZE);

    ~BufferManager();

    auto AccessBlock(const block_type& block_id) -> Buffer*;

    auto FlushBlock(const block_type& block_id) -> bool;

    auto Unpin(const block_type& block_id, const bool& is_dirty) -> bool;

   private:
    size_t buffer_size_{0};
    std::shared_mutex mu_;                 /**全局锁*/
    std::atomic<size_t> next_block_id_{0}; /**用于分配块编号*/
    DiskManager* dm_;                      /**磁盘管理器*/
    LRUReplacer* replacer_;           /**基于lru策略的缓冲区替换*/
    Buffer* buffer_pool_{nullptr};    /**缓冲池*/
    FreeList<buffer_type> free_list_; /**缓冲池空闲列表*/
    std::unordered_map<buffer_type, block_type>
        block_2_buffer_; /**输入物理块号，查询缓冲池内是否有buffer对应*/
};
}  // namespace FileSystem
#endif  // FILE_SYSTEM_BUFFER_H
