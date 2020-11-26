cmake_minimum_required(VERSION 3.16.3)
project(cpp_project)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DEZFW_SIMULATION)

include_directories(ezfw/include cyder_project/include)

file(GLOB_RECURSE sources src/*.cpp ezfw/src/*.cpp)
add_executable(cpp_project ${sources} ezfw)
