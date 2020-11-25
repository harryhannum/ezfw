cmake_minimum_required(VERSION 3.16.3)
project(cpp_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(ezfw/include)

file(GLOB sources *.c *.cpp)
add_executable(cpp_project ${sources})