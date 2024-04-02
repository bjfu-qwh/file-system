cmake_minimum_required(VERSION 3.7)

add_library(
        core
        core.cc
        include/core.h
        super_block.cc
        include/super_block.h
)

add_library(
        inode
        include/inode.h
        common.cc
        include/common.h
        inode.cc
)

add_library(config config.cc include/config.h)

add_library(buffer buffer.cc include/buffer.h buffer.cc)

add_library(common common.cc include/common.h)

#磁盘管理库
add_library(disk disk.cc include/disk.h)

#添加一个库
add_library(file_system_lib disk core inode common
        buffer config)

#在这里引入include目录
target_include_directories(
        file_system_lib PUBLIC include)

#指定库文件编译参数
target_compile_features(
        file_system_lib PUBLIC cxx_std_11)

#指定库文件链接参数
set_target_properties(
        file_system_lib PROPERTIES
        LINKER_LANGUAGE CXX)