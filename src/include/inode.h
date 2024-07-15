#pragma once

#include "config.h"

namespace FileSystem {
class INode {
   public:
    explicit INode(int uid_, unsigned size_);

    auto GetMTime() -> char* { return mtime_; }

    auto GetCTime() -> char* { return ctime_; }

    auto GetATime() -> char* { return atime_; }

    [[nodiscard]] auto GetNLink() const -> int { return nlink_; }

    ~INode() = default;

   private:
    int nlink_;
    int uid_;
    unsigned size_;
    char atime_[TIME_LENGTH]{}; /**最近访问时间*/
    char ctime_[TIME_LENGTH]{}; /**创建时间*/
    char mtime_[TIME_LENGTH]{}; /**最近修改时间*/
};

class INodeOnDisk {};
}  // namespace FileSystem