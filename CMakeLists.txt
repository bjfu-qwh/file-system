cmake_minimum_required(VERSION 3.7)

project(file-system)
set(VERSION 1.0)
set(PROJECT_DESCRIPTION "基于C++实现一个简易文件系统")
set(LANGUAGE CXX)
set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED True)
#设置构建目录，这里还是./build文件夹
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
#这是build中的资源文件
set(config_diretory ${BUILD_DIR}/config)
include_directories(${config_diretory})
add_subdirectory(src)
add_subdirectory(test)
#!!!添加系统磁盘的文件地址
configure_file(
    config/config.conf 
    ${config_diretory}/config.conf
    COPYONLY)

# 可执行文件名称
add_executable(
    app 
    main.cc
)

target_compile_features(app PRIVATE cxx_std_11)
# 链接src提供的库文件
target_link_libraries(app PRIVATE file_system_lib)
