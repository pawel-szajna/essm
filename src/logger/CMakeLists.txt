add_essm_library(
    NAME logger
    TYPE INTERFACE
    DEPENDENCIES
        essm::helpers
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
