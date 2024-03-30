#pragma once

namespace FileSystem {

/**
 * @brief 读取虚拟磁盘的位置，返回其绝对路径。
 * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
 * disk-location:D:/Projects/Systems/operating-system/
 * 将会认为磁盘路径为D:/Projects/Systems/operating-system/。
 *
 * @return const char* 磁盘的绝对路径
 */
auto fetchDiskLocation() -> char *;

static constexpr const char *DISK_NAME = "data.iso";
static constexpr const char *CONFIG_PATH = "../config/config.conf";
static constexpr int PATH_LIMIT = 100;
static constexpr int BLOCK_SIZE = 4096;
static constexpr const char *PATH_SEPARATOR = "/";
static constexpr const char *CWD = ".";
static constexpr const char *PARENT_DIR = "..";
static constexpr const int ROOT_INODE_NUMBER = 1;

static constexpr const int TIME_LENGTH = 20;
}  // namespace FileSystem