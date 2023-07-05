#include "../include/core.h"
#include <iostream>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    const char *config = fetchDiskLocation();
    cout << config << endl;
    printf("disk name:%s\n", DISK_NAME);
    return 0;
}