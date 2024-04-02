/**
 * @file disk.h
 * @author bfu qwh
 * @brief 磁盘结构的设计
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef DISK_H_
#define DISK_H_

#include "config.h"
#include "fstream"
#include "mutex"

namespace FileSystem {
/**
 * DiskManager负责以块为单位维护虚拟磁盘读写操作。
 */
class DiskManager {
   private:
    std::mutex io_mutex_;
    std::fstream io_;
    std::string file_name_;

   public:
    void ReadBlock(block_type block_id, char *block_data);

    void WriteBlock(block_type block_id, const char *block_data);

    explicit DiskManager(std::string file_name);

    DiskManager() = default;

    ~DiskManager() = default;

    DiskManager(const DiskManager &that) = delete;

    DiskManager operator=(DiskManager that) = delete;
};
}  // namespace FileSystem
#endif