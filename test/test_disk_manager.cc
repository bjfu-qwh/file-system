#include <cassert>
#include <cstring>
#include <string>

#include "../src/include/disk_manager.h"
#include "../src/include/exception.h"

namespace FileSystem {
void testVDiskPath() {
    const std::string wrong_path = "wrong";
    try {
        DiskManager(wrong_path.c_str());
    } catch (SystemExpection &se) {
        assert(se.type_ == ExceptionType::SYSTEM_ERROR);
    }
}

void testBasicReadAndWrite() {
    char buf[BLOCK_SIZE] = {0};
    char data[BLOCK_SIZE] = {0};
    auto dm = DiskManager(fetchDiskLocation());
    strncpy(data, "A test string.", sizeof(data));

    dm.ReadBlock(0, buf);

    dm.WriteBlock(0, data);
    dm.ReadBlock(0, buf);
    assert(memcmp(buf, data, sizeof(buf)) == 0);

    memset(buf, 0, sizeof(buf));
    dm.WriteBlock(5, data);
    dm.ReadBlock(5, buf);
    assert(memcmp(buf, data, sizeof(buf)) == 0);
}
}  // namespace FileSystem

int main() {
    FileSystem::testVDiskPath();
    FileSystem::testBasicReadAndWrite();
}
