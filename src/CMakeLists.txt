cmake_minimum_required(VERSION 3.7)

# 设置对应的include列表
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/")

# 设置所有的源文件列表
set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src")

# 系统核心库
add_library(
    core
    ${SOURCE_LIST}/core.cc
    ${HEADER_LIST}/core.h
)

# 磁盘管理库
add_library(
    disk
    ${SOURCE_LIST}/disk.cc
    ${HEADER_LIST}/disk.h
)


# 添加一个库
add_library(
    file_system_lib 
    disk
)

# 在这里引入include目录
target_include_directories(
    file_system_lib 
    PUBLIC 
    ../include
)

# 指定库文件编译参数
target_compile_features(
    file_system_lib 
    PUBLIC 
    cxx_std_11
)

# 指定库文件链接参数
set_target_properties(
    file_system_lib 
    PROPERTIES 
    LINKER_LANGUAGE 
    CXX
)