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

#!!!添加系统磁盘的文件地址
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
        ${HEADER_LIST}/core.h
        ${SOURCE_LIST}/core.cc
)

target_compile_features(test_config PRIVATE cxx_std_11)

target_link_libraries(test_config PRIVATE file_system_lib)

add_test(NAME test_config COMMAND test_config)