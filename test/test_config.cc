#include <cassert>
#include <iostream>

#include "../src/include/config.h"

using namespace std;
using namespace FileSystem;

namespace FileSystem {
    void testDiskConfig() {
      const char *config = fetchDiskLocation();
      assert(config != nullptr);
      printf("disk name:%s\n", DISK_NAME);
      delete config;
    }
}  // namespace FileSystem

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  FileSystem::testDiskConfig();
}