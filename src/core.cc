#include "../include/core.h"
#include <fstream>
#include <string>
#include <cassert>

using std::fstream;
using std::string;

/**
 * @brief 读取虚拟磁盘的位置，返回其绝对路径。
 * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
 * disk-location:D:/Projects/Systems/operating-system/
 * 将会认为磁盘路径为D:/Projects/Systems/operating-system/。
 *
 * @return const char* 返回对应的字符数组
 */
const char *fetchDiskLocation() {
    fstream configFile("../config/config.conf");
    assert(!configFile.fail());
    string value, data;
    configFile >> data;
    size_t index = data.find(':');
    assert(index != string::npos);
    value = data.substr(index + 1);
    return value.data();
}