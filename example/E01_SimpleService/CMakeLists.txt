add_executable(E01_SimpleService main.cpp)

set_target_properties(
    E01_SimpleService
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_link_libraries(
    E01_SimpleService
    PRIVATE
        essm::logger  # The logging library, not needed, but useful
        essm::events  # The library providing events generation
        essm::service # The library providing service implementations
)

target_compile_definitions(
    E01_SimpleService
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)
