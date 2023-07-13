add_executable(SimpleService main.cpp)

set_target_properties(
    SimpleService
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_link_libraries(
    SimpleService
    PRIVATE
        essm::logger  # The logging library, not needed, but useful
        essm::service # The library providing service implementations
)

target_compile_definitions(
    SimpleService
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)
