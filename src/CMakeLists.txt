cmake_minimum_required(VERSION 3.7)

add_library(
        file_system_lib
        disk_manager.cc
        include/disk_manager.h
        buffer.cc
        include/buffer.h
        config.cc
        include/config.h
        core.cc
        include/core.h
        inode.cc
        include/inode.h
        super_block.cc
        include/super_block.h
        directory.cc
        include/directory.h
        include/exception.h
        lru_replacer.cc
        include/lru_replacer.h
        include/rw_lock.h
)

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