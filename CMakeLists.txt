cmake_minimum_required(VERSION 3.27)
project(Flipper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)



include_directories(${CMAKE_SOURCE_DIR})

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

target_link_libraries(Flipper PRIVATE
        GLUT::GLUT
        OpenGL::GL)

