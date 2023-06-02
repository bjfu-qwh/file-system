cmake_minimum_required(VERSION 3.7)

# 设置对应的src列表
set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/")

# 设置对应的include列表
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/")

# 添加测试代码
add_executable(
    testconfig 
    testconfig.cc 
    ${HEADER_LIST}/core.h
    ${SOURCE_LIST}/core.cc
)

target_compile_features(testconfig PRIVATE cxx_std_11)

target_link_libraries(testconfig PRIVATE file_system_lib)

add_test(NAME test_config COMMAND testconfig) 