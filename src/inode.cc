#include "include/inode.h"

#include "common.h"
#include "cstring"

namespace FileSystem {
FileSystem::INode::INode(int uid_, unsigned int size_)
    : uid_(uid_), size_(size_) {
    std::string current_time = GetCurrentTime();
    strncpy(atime, current_time.c_str(), TIME_LENGTH);
    strncpy(ctime, GetCurrentTime().c_str(), TIME_LENGTH);
    strncpy(mtime, GetCurrentTime().c_str(), TIME_LENGTH);
    nlink_ = 0;
}
}  // namespace FileSystem
