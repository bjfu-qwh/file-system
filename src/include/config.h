#pragma once
#include <cstddef>
/**
 * 在这里实现基本配置和功能。虚拟磁盘设计如下：
 * --------------------------------------------------------
 * | SuperBlock (inode 0) |inode 1 | ... | inode NUM_INODE|
 * |
 * --------------------------------------------------------
 */
namespace FileSystem {
/**
 * @brief 读取虚拟磁盘的位置，返回其绝对路径。
 * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
 *
 * @return const char* 磁盘的绝对路径
 */
auto fetchDiskLocation() -> char*;

using block_type = int;
using buffer_type = int; /**buffer单元编号类型*/
static constexpr const auto* DISK_NAME = "data.iso";
static constexpr size_t DISK_SIZE = (1 << 26); /**虚拟磁盘大小。64MB可修改*/
static constexpr auto* CONFIG_PATH = "../config/config.conf";
static constexpr int PATH_LIMIT = 100;
/**块大小，设为4KB*/
static constexpr int BLOCK_SIZE = 4096;
/**块数量，等于2^24*/
static constexpr int NUM_BLOCKS = DISK_SIZE / BLOCK_SIZE;
static constexpr const char* PATH_SEPARATOR = "/";
static constexpr const char* CWD = ".";
static constexpr const char* PARENT_DIR = "..";
static constexpr int SUPER_BLOCK_INODE_NUMBER = 0;
static constexpr int NUM_INODE = 63; /**共计64，第一块超级块*/
static constexpr int TIME_LENGTH = 20;
static constexpr size_t BUFFER_POOL_SIZE = 50;
static constexpr int INODE_LIST_START = 0; /**虚拟磁盘中INODE区的起始offset*/
static constexpr block_type INVALID_BLOCK_ID = -1;
static constexpr buffer_type INVALID_BUFFER_ID = -1;
}  // namespace FileSystem
