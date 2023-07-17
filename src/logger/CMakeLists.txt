add_library(
    essm_logger
    INTERFACE
)

add_library(
    essm::logger
    ALIAS
        essm_logger
)

if(ESSM_LOGGER_BACKEND STREQUAL "fmt")
    add_compile_definitions(ESSM_LOGGER_BACKEND_FMT)
    find_package(fmt REQUIRED)
    target_link_libraries(essm_logger INTERFACE fmt::fmt)
elseif(ESSM_LOGGER_BACKEND STREQUAL "std")
    add_compile_definitions(ESSM_LOGGER_BACKEND_STD)
elseif(ESSM_LOGGER_BACKEND STREQUAL "spdlog")
    add_compile_definitions(ESSM_LOGGER_BACKEND_SPDLOG)
    find_package(spdlog REQUIRED)
    target_link_libraries(essm_logger INTERFACE spdlog)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR
   CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_definitions(ESSM_LOGGER_ENABLE_DEBUG)
endif()

target_link_libraries(
    essm_logger
    INTERFACE
        essm::helpers
)

target_include_directories(
    essm_logger
    INTERFACE
        include
)
