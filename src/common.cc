#include "include/common.h"

#include "ctime"
#include "include/config.h"
#include "string"

namespace FileSystem {
auto GetCurrentTime() -> std::string {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char time[TIME_LENGTH];
    sprintf(time, "%04d/%02d/%02d-%02d:%02d:%02d", ltm->tm_year + 1900,
            ltm->tm_mon + 1, ltm->tm_mday, ltm->tm_hour, ltm->tm_min,
            ltm->tm_sec);
    return time;
}
}  // namespace FileSystem