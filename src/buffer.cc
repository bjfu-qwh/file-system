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
}  // namespace FileSystem