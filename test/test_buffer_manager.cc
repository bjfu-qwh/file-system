#include <cassert>

#include "../src/include/buffer.h"
#include "../src/include/common.h"

namespace FileSystem {
void BasicBufferManagerTest() {
    constexpr size_t buffer_size{BUFFER_POOL_SIZE};
    auto* bm = new BufferManager(buffer_size);
    for (block_type id = 0; id < buffer_size; ++id) {
        assert(bm->AccessBlock(id) != nullptr);
    }
    for (block_type id = buffer_size; id < (buffer_size << 1); ++id) {
        assert(bm->AccessBlock(id) == nullptr);
    }
    delete bm;
    RemoveVDisk();
}
}  // namespace FileSystem

int main() { FileSystem::BasicBufferManagerTest(); }
