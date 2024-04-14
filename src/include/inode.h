#pragma once

#include "config.h"

namespace FileSystem {
class INode {
 private:
  int nlink_;
  int uid_;
  unsigned size_;
  char atime_[TIME_LENGTH]{};
  char ctime_[TIME_LENGTH]{};
  char mtime_[TIME_LENGTH]{};

 public:
  explicit INode(int uid_, unsigned size_);

  inline auto GetMTime() -> char * { return mtime_; }

  inline auto GetCTime() -> char * { return ctime_; }

  inline auto GetATime() -> char * { return atime_; }

  [[nodiscard]] inline auto GetNLink() const -> int { return nlink_; }

  ~INode() = default;
};

class INodeOnDisk {};
}  // namespace FileSystem