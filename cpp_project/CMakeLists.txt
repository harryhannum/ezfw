cmake_minimum_required(VERSION 3.16.3)
project(cpp_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(ezfw/include)
add_subdirectory(ezfw)

file(GLOB sources src/*.c src/*.cpp)
list(APPEND sources main.cpp)
add_executable(cpp_project ${sources})
