#pragma once

#include "config.h"

namespace FileSystem {
class INode {
   private:
    int nlink_;
    int uid_;
    unsigned size_;
    char atime[TIME_LENGTH]{};
    char ctime[TIME_LENGTH]{};
    char mtime[TIME_LENGTH]{};

   public:
    explicit INode(int uid_, unsigned size_);

    ~INode() = default;
};
}  // namespace FileSystem