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
void ReadBlock(block_type block_id, char *block_data);

void WriteBlock(block_type block_id, const char *block_data);
}  // namespace FileSystem
#endif