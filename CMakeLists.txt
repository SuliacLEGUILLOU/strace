cmake_minimum_required(VERSION 3.6)
project(strace)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    hdrs/strace.h
    srcs/main.c
    srcs/strace.c)

add_executable(strace ${SOURCE_FILES})