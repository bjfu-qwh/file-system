# 基于C++的简易文件系统实现

## 项目构建说明
项目基于**cmake**进行构建，要求使用cmake**3.7及以上**的版本。cmake的各个release可以在**https://cmake.org/download/** 找到。

项目要求**C++ 11及以上、C99及以上的编译器支持**。

若计算机已安装**MSYS2或MINGW，或者本身就是Linux计算机**，并且拥有make程序，则可以**基于make进行构建**。指令如下：
```shell 基于make的构建指令
cmake -B build -G "MinGW Makefiles" # 基于MINGW进行构建
cd build # 进入新建的目录下
make # 调用make进行真正的构建
```

若计算机安装了**Visual Studio实例**，亦可通过cmake生成解决方案。
