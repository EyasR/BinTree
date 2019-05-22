cmake_minimum_required(VERSION 3.13)
project(ASG2_EyasRashid)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ASG2_EyasRashid
        BinTree.cpp
        BinTree.h
        main.cpp
        nodedata.cpp
        nodedata.h)
