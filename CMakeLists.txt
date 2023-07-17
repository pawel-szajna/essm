cmake_minimum_required(VERSION 3.24)
project(essm)

set(CMAKE_CXX_STANDARD 23)

option(ESSM_BUILD_EXAMPLES "Build ESSM library examples" OFF)
option(ESSM_BUILD_UT "Build ESSM library unit tests" OFF)

add_subdirectory(src)
add_subdirectory(example)
