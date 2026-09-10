cmake_minimum_required(VERSION 3.20)
project(Lab3 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab3_cpp hello.cpp
        hello.cpp
        seqlist.c)
add_executable(lab3_c seqlist.c
        hello.cpp
        seqlist.c)