cmake_minimum_required(VERSION 3.7)

# 设置对应的src列表
set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/")

# 设置对应的include列表
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/")

# 添加磁盘配置测试代码
add_executable(
        test_config
        test_config.cc
        ${HEADER_LIST}/core.h
        ${SOURCE_LIST}/core.cc
)

target_compile_features(test_config PRIVATE cxx_std_11)

target_link_libraries(test_config PRIVATE file_system_lib)

add_test(NAME test_config COMMAND test_config)