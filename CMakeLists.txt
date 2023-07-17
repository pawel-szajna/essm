cmake_minimum_required(VERSION 3.24)
project(essm)

set(CMAKE_CXX_STANDARD 23)

option(ESSM_BUILD_EXAMPLES "Build ESSM library examples" OFF)
option(ESSM_BUILD_UT "Build ESSM library unit tests" OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(ESSM_BUILD_UT)
    message(STATUS "ESSM unit tests enabled")
    include(ESSMUnitTests)
    essm_acquire_google_test()
endif()
include(ESSMLibrary)

add_subdirectory(src)
add_subdirectory(example)
