cmake_minimum_required(VERSION 3.24)
project(essm)

set(CMAKE_CXX_STANDARD 23)
set(ESSM_LOGGER_BACKEND fmt)

add_subdirectory(src)
add_subdirectory(example)
