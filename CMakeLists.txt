cmake_minimum_required(VERSION 3.27)
project(obj)

set(CMAKE_CXX_STANDARD 17)

add_executable(obj
        main.cpp
        Object3d.h
        Object3d.cpp
        Vertex.h
        Vertex.cpp
        Face.h
        Face.cpp
)
