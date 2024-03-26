#include "../include/core.h"
#include "../include/config.h"
#include <iostream>

using namespace std;

namespace FileSystem {
    void testDiskConfig() {
        const char *config = fetchDiskLocation();
        cout << config << endl;
        printf("disk name:%s\n", DISK_NAME);
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    FileSystem::testDiskConfig();
}