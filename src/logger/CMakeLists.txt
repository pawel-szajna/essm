add_library(
    essm_logger
    STATIC
        src/Logger.cpp
)

add_library(
    essm::logger
    ALIAS
        essm_logger
)

set_target_properties(
    essm_logger
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

if(ESSM_LOGGER_BACKEND STREQUAL "fmt")
    add_compile_definitions(ESSM_LOGGER_BACKEND_FMT)
    find_package(fmt REQUIRED)
    target_link_libraries(essm_logger PUBLIC fmt::fmt)
elseif(ESSM_LOGGER_BACKEND STREQUAL "std")
    add_compile_definitions(ESSM_LOGGER_BACKEND_STD)
elseif(ESSM_LOGGER_BACKEND STREQUAL "spdlog")
    add_compile_definitions(ESSM_LOGGER_BACKEND_SPDLOG)
    find_package(spdlog REQUIRED)
    target_link_libraries(essm_logger PUBLIC spdlog)
endif()

target_include_directories(
    essm_logger
    PRIVATE
        include/essm/logger
    PUBLIC
        include
)
