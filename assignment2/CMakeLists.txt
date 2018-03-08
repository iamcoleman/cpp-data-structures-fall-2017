cmake_minimum_required(VERSION 3.8)
project(assignment2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp StudentList.cpp StudentList.h LL.cpp LL.h)
add_executable(assignment2 ${SOURCE_FILES})