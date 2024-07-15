#include <cassert>
#include <cstring>
#include <random>

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
    char random_data[BLOCK_SIZE];
    std::random_device r;
    std::default_random_engine rng(r());
    std::uniform_int_distribution<int> uniform_dist(0);
    for (char& i : random_data) {
        i = static_cast<char>(uniform_dist(rng));
    }
    random_data[BLOCK_SIZE >> 1] = random_data[BLOCK_SIZE - 1] = '\0';
    Buffer* buf = bm->AccessBlock(0);
    memcpy(buf->GetData(), random_data, BLOCK_SIZE);
    assert(memcmp(buf->GetData(), random_data, BLOCK_SIZE) == 0);

    for (block_type id = 0; id < buffer_size; ++id) {
        assert(bm->Unpin(id, true) == true);
        bm->FlushBlock(id);
    }
    delete bm;
    RemoveVDisk();
}
}  // namespace FileSystem

int main() { FileSystem::BasicBufferManagerTest(); }
