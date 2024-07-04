#include "include/disk_manager.h"
#include <cassert>

#include "cstring"

#include "include/exception.h"

namespace FileSystem {
void DiskManager::ReadBlock(block_type block_id, char *block_data) {
  assert(disk_ptr_ != nullptr);
  std::scoped_lock scoped_lock(io_lock_);
  const size_t offset = BLOCK_SIZE * block_id;  // TODO:fix the offset
  if (offset >= GetFileSize()) {
    throw OutOfRangeException("read block out of file range.");
  }
  fseek(disk_ptr_, static_cast<long>(offset), SEEK_SET);
  fread(block_data, sizeof(char), BLOCK_SIZE, disk_ptr_);
  fflush(disk_ptr_);
}

void DiskManager::WriteBlock(const block_type block_id, const char *block_data) {
  assert(disk_ptr_ != nullptr);
  std::scoped_lock scoped_lock(io_lock_);
  const size_t offset = BLOCK_SIZE * block_id;  // TODO:fix the offset
  fseek(disk_ptr_, static_cast<long>(offset), SEEK_SET);
  fwrite(block_data, sizeof(char), BLOCK_SIZE, disk_ptr_);
  fflush(disk_ptr_);
}

DiskManager::DiskManager(const char *path) {
  disk_ptr_ = fopen(path, "rb+");
  if (disk_ptr_ == nullptr) {
    CreateVirtualDisk();
  }
  disk_path_ = new char[strlen(path)];
  strncpy(disk_path_, path, strlen(path));
}

auto DiskManager::GetFileSize() const -> size_t {
  size_t result;
#ifdef _WIN32
  fpos_t fpos;  // 当前位置
  fgetpos(disk_ptr_, &fpos);
  fseek(disk_ptr_, 0, SEEK_END);
  result = static_cast<size_t>(ftell(disk_ptr_));
  fsetpos(disk_ptr_, &fpos);
#endif
#ifdef __linux__
  struct stat stat_buf;
  int rc = stat(disk_path_, &stat_buf);
  result = (rc == 0 ? static_cast<size_t>(stat_buf.st_size) : std::npos);
#endif
  return result;
}

DiskManager::~DiskManager() { fclose(disk_ptr_); }

void DiskManager::CreateVirtualDisk() {
  std::string disk_path(fetchDiskLocation());
  disk_path += DISK_NAME;
  disk_ptr_ = fopen(disk_path.c_str(), "rb+");
  fseek(disk_ptr_, DISK_SIZE - 1, SEEK_SET);
  constexpr char ch = 0;
  fwrite(&ch, 1, sizeof(ch), disk_ptr_);
}
}  // namespace FileSystem
