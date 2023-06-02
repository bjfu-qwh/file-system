#include "../include/core.h"
#include <fstream>
#include <assert.h>
using std::fstream;
/**
 * @brief 读取虚拟磁盘的位置，返回其绝对路径。
 * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
 * disk-location:D:/Projects/Systems/operating-system/
 * 将会认为磁盘路径为D:/Projects/Systems/operating-system/。
 *
 * @return string
 */
string fetchDiskLocation(void)
{
    fstream configFile("../config/config.conf");
    string value, data;
    configFile >> data;
    int index = data.find(":");
    assert(index >= 0);
    value = data.substr(index + 1);
    return value;
}