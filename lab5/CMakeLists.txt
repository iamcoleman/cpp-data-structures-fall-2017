cmake_minimum_required(VERSION 3.8)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES OLL.cpp studentClass.cpp studentClass.h main.cpp)
add_executable(lab5 ${SOURCE_FILES} main.cpp)