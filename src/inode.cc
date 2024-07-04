#include "include/inode.h"

#include "cstring"
#include "include/common.h"

namespace FileSystem {
INode::INode(int uid_, unsigned int size_) : uid_(uid_), size_(size_) {
  std::string current_time = GetCurrentTime();
  strncpy(atime_, current_time.c_str(), TIME_LENGTH);
  strncpy(ctime_, GetCurrentTime().c_str(), TIME_LENGTH);
  strncpy(mtime_, GetCurrentTime().c_str(), TIME_LENGTH);
  nlink_ = 0;
}
}  // namespace FileSystem
