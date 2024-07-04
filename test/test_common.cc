#include <iostream>

#include "../src/include/common.h"

namespace FileSystem {
void testGetCurrentTime() { std::cout << GetCurrentTime() << "\n"; }
}  // namespace FileSystem

int main() { FileSystem::testGetCurrentTime(); }