/**
 * @file core.h
 * @author bjfuqwh
 * @brief 系统的核心配置参数以及函数。比如磁盘大小以及划分设计、
 * 虚拟磁盘的路径读取等。
 *
 * @version 0.1
 * @date 2023-06-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CORE__H_
#define CORE__H_
#include <string>
using std::string;
/**
 * @brief 规定了磁盘文件的名称和后缀。
 */
const string DISK_NAME = "data.iso";
/**
 * @brief 读取虚拟磁盘的位置，返回其绝对路径。
 * @note 磁盘的绝对路径书写在config目录下的config.conf文件下。如
 * disk-location:D:/Projects/Systems/operating-system/
 * 将会认为磁盘路径为D:/Projects/Systems/operating-system/。
 *
 * @return string 磁盘的绝对路径
 */
string fetchDiskLocation(void);
#endif