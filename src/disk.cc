#include "include/disk.h"

#include <utility>

namespace FileSystem {
void DiskManager::ReadBlock(block_type block_id, char *block_data) {
    const int offset = 0;
}

void DiskManager::WriteBlock(block_type block_id, const char *block_data) {}

DiskManager::DiskManager(std::string file_name)
    : file_name_(std::move(file_name)) {
    io_.open(file_name,
             std::ios::binary | std::ios::in | std::ios::app | std::ios::out);
    if (!io_.is_open()) {
        throw std::runtime_error("cannot open file:" + file_name);
    }
}
}  // namespace FileSystem
