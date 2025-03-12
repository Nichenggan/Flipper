cmake_minimum_required(VERSION 3.27)
project(Flipper)

# 设置 C++ 版本（建议 C++17）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关闭所有警告（可选）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")


# 查找 OpenGL 和 GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



# 设置包含目录
include_directories(${CMAKE_SOURCE_DIR})

# 创建主程序
add_executable(Flipper
        Eleve.cpp
        G2D.h
        G2DColor.cpp
        G2Dfull.h
        G2DKey.cpp
        G2DMain.cpp
        G2DMouse.cpp
        G2DPPM.cpp
        G2DX.cpp
        glut.h
        GlutImport.h
        V2.cpp
        V2.h)

# 链接 OpenGL/GLUT 库
target_link_libraries(Flipper PRIVATE
        GLUT::GLUT
        OpenGL::GL)

