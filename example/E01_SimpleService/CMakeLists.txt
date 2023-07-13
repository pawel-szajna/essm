add_executable(SimpleService main.cpp)

set_target_properties(
    SimpleService
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_link_libraries(
    SimpleService
    PRIVATE
        essm::service
)
