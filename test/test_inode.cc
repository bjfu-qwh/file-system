#include "../src/include/inode.h"
#include "cassert"
#include "cstdio"

namespace FileSystem {
    void testINodeInit() {
      INode node(2, 4);
      assert(node.GetNLink() == 0);
      printf("%s\n", node.GetATime());
    }
}  // namespace FileSystem

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  FileSystem::testINodeInit();
}