cmake_minimum_required(VERSION 3.29)
project(Flipper)


set(CMAKE_CXX_STANDARD 11)  # 指定 C++11 标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")  # 关闭所有警告

find_package(OpenGL REQUIRED)  # 查找 OpenGL
find_package(GLUT REQUIRED)    # 查找 GLUT

include_directories(.)

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

target_link_libraries(Flipper
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        "-framework OpenGL"
        "-framework GLUT"
        "-framework Cocoa"
)