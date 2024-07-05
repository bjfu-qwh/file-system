//
// Created by 20473 on 2024/7/5.
//

#ifndef LRUREPLACER_H
#define LRUREPLACER_H
#include <shared_mutex>
#include <unordered_map>

#include "config.h"

namespace FileSystem {
class LRUNode {
 public:
  explicit LRUNode(const buffer_type &buffer_id, const size_t &timestamp);

  ~LRUNode() = default;

  LRUNode(const LRUNode &other);

  void Update(const size_t &new_timestamp);

  [[nodiscard]] auto IsReady() const -> bool;

  void SetReady(const bool &ready);

  [[nodiscard]] auto GetBufferId() const -> buffer_type;

  [[nodiscard]] auto GetTimestamp() const -> size_t;

  auto better(const LRUNode &other) const -> bool;

 private:
  bool ready_{true};
  buffer_type buffer_id_{INVALID_BUFFER_ID};
  size_t timestamp_{0};
};

class LRUReplacer {
 public:
  auto GetVictim(buffer_type &victim_id) -> bool;

  auto Remove(const buffer_type &buffer_id) -> bool;

  void Record(const buffer_type &buffer_id, const size_t &timestamp);

  explicit LRUReplacer(const size_t &size);

 private:
  std::unordered_map<buffer_type, LRUNode *> cache_; /**基于缓冲单元编号的映射*/
  std::mutex mu_;
  size_t size_{0};
  auto Decide() const -> buffer_type;
};
}  // namespace FileSystem

#endif  // LRUREPLACER_H
