cmake_minimum_required(VERSION 3.7)

# 设置对应的src列表
set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/")

# 设置对应的include列表
set(HEADER_LIST "${SOURCE_LIST}/include/")

# 这是build中的资源文件,在build中增加config目录
set(
        config_directory
        ${BUILD_DIR}/test/config
)

configure_file(
        ${PROJECT_SOURCE_DIR}/config/config.conf
        ${config_diretory}/config.conf
        COPYONLY
)

# 添加磁盘配置测试代码
add_executable(
        test_config
        test_config.cc
        ${HEADER_LIST}/config.h
        ${SOURCE_LIST}/config.cc
)

add_executable(
        test_common
        test_common.cc
        ${HEADER_LIST}/common.h
        ${SOURCE_LIST}/common.cc
)

add_test(NAME test_config COMMAND test_config)

add_test(NAME test_common COMMAND test_common)