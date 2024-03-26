#include "include/core.h"
#include "include/config.h"
#include <cassert>
#include <cstdio>

using namespace FileSystem;

namespace FileSystem {
    /**
     * @brief 读取虚拟磁盘的位置，返回其绝对路径。
     * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
     * D:/Projects/Systems/operating-system/
     *
     * @return const char* 返回对应的字符数组
     */
    char *fetchDiskLocation() {
        FILE *config = fopen("../config/config.conf", "r");
        assert(config != nullptr);
        char *path = new char[PATH_LIMIT];
        fgets(path, PATH_LIMIT, config);
        return path;
    }
}