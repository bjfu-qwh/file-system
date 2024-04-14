#pragma once
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
auto fetchDiskLocation() -> char *;

/**
 * 按格式描述，创建虚拟磁盘。
 */
auto createVirtualDisk() -> int;

static constexpr const char *DISK_NAME = "data.iso";
static constexpr const char *CONFIG_PATH = "../config/config.conf";
static constexpr int PATH_LIMIT = 100;
static constexpr int BLOCK_SIZE = 4096;
static constexpr const char *PATH_SEPARATOR = "/";
static constexpr const char *CWD = ".";
static constexpr const char *PARENT_DIR = "..";
static constexpr const int INVALID_BLOCK_ID = -1;
static constexpr const int SUPER_BLOCK_INODE_NUMBER = 0;
static constexpr const int NUM_INODE = 63; /**共计64，第一块超级块*/
static constexpr const int TIME_LENGTH = 20;

// TODO 实现虚拟磁盘设计
static constexpr const int INODE_LIST_START = 0; /**虚拟磁盘中INODE区的起始offset*/

using block_type = int;
}  // namespace FileSystem