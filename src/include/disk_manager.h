/**
 * @file disk_manager.h
 * @author bfu qwh
 * @brief 磁盘管理器的设计
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef DISK_H_
#define DISK_H_

#include <mutex>

#include "config.h"
#include "cstdio"

namespace FileSystem {
class DiskManager {
 public:
  void ReadBlock(block_type block_id, char *block_data);

  void WriteBlock(block_type block_id, const char *block_data);

  explicit DiskManager(const char *path = fetchDiskLocation());

  auto GetFileSize() const -> size_t;

  ~DiskManager();

 private:
  FILE *disk_ptr_{nullptr};
  char *disk_path_;
  std::mutex io_lock_;

  void CreateVirtualDisk();
};
}  // namespace FileSystem
#endif