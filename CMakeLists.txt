cmake_minimum_required(VERSION 3.7)

project(file-system)
set(VERSION 1.0)
set(PROJECT_DESCRIPTION "基于C++实现一个简易文件系统")
set(LANGUAGE CXX)
set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)

# 设置构建目录，这里还是./build文件夹
set(
        BUILD_DIR
        ${CMAKE_CURRENT_BINARY_DIR}
)

# 这是build中的资源文件,在build中增加config目录（和应用程序同级）
set(
        config_directory
        ${BUILD_DIR}/config
)

# 包含程序的三个目录:配置、源文件、测试文件。
add_subdirectory(config)
add_subdirectory(src)
add_subdirectory(test)

# 项目的最终可执行文件
add_executable(
        file-system
        main.cc
)

# 指定项目编译方法
target_compile_features(file-system PRIVATE cxx_std_11)

# 链接src提供的库文件
target_link_libraries(file-system PRIVATE file_system_lib)
