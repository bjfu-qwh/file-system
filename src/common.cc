#include "include/common.h"

#include <ctime>
#include <string>

#include "include/config.h"

namespace FileSystem {
auto GetCurrentTime() -> std::string {
    const time_t now = time(nullptr);
    const tm *ltm = localtime(&now);
    char time[TIME_LENGTH];
    sprintf(time, "%04d/%02d/%02d-%02d:%02d:%02d", ltm->tm_year + 1900,
            ltm->tm_mon + 1, ltm->tm_mday, ltm->tm_hour, ltm->tm_min,
            ltm->tm_sec);
    return time;
}

auto RemoveVDisk() -> bool {
    std::string disk_path(fetchDiskLocation());
    disk_path += DISK_NAME;
    return remove(disk_path.c_str());
}
}  // namespace FileSystem