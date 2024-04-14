//
// Created by 20473 on 2024/3/30.
//

#ifndef FILE_SYSTEM_BUFFER_H
#define FILE_SYSTEM_BUFFER_H

#include "config.h"
#include "mutex"  // NO_LINT
#include "unordered_map"

namespace FileSystem {
class Buffer {
 private:
  block_type block_id_{INVALID_BLOCK_ID}; /**缓存对应块号码*/
  unsigned ref_count_{0};                 /**缓存的引用计数*/
  std::mutex mu_;
  char data_[BLOCK_SIZE]{'0'}; /**具体数据*/

 public:
  explicit Buffer(block_type block_id, const char *data);
};

class BufferManager {
 private:
  int buffer_size_{0};
  std::mutex mu_;
  std::unordered_map<block_type, Buffer *> cache_;
  size_t timestamp_{0};
};
}  // namespace FileSystem
#endif  // FILE_SYSTEM_BUFFER_H
