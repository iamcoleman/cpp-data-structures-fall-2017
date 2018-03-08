cmake_minimum_required(VERSION 3.8)
project(lab6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES singleplayer.cpp stack.cpp stack.h queue.cpp queue.h multiplayer.cpp)
add_executable(lab6 ${SOURCE_FILES})