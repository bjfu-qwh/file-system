#include <cassert>

#include "../src/include/exception.h"
#include "../src/include/lru_replacer.h"

namespace FileSystem {
void TestBasicReplacer() {
  std::cout << "TestBasicReplacer started...\n";
  auto replacer = LRUReplacer(5);
  for (int i = 1; i <= 5; ++i) {
    replacer.Record(i, i);
  }
  try {
    replacer.Record(6, 6);
  } catch (OutOfRangeException &oor [[maybe_unused]]) {
  }
  buffer_type buffer_id;
  replacer.GetVictim(buffer_id);
  assert(buffer_id == 1);
  replacer.Remove(buffer_id);
  replacer.Record(2, 7);
  replacer.GetVictim(buffer_id);
  assert(buffer_id == 3);
  replacer.Remove(buffer_id);
  replacer.Record(5, 7);
  replacer.Record(4, 8);
  replacer.GetVictim(buffer_id);
  assert(buffer_id == 2);
  replacer.Remove(buffer_id);
  replacer.GetVictim(buffer_id);
  assert(buffer_id == 5);
  replacer.Remove(buffer_id);
  replacer.GetVictim(buffer_id);
  assert(buffer_id == 4);
  replacer.Remove(buffer_id);
  std::cout << "Test Passed.\n";
}
}  // namespace FileSystem

int main() { FileSystem::TestBasicReplacer(); }
