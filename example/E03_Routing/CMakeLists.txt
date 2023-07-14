add_executable(
    E03_Routing
        main.cpp
)

set_target_properties(
    E03_Routing
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_compile_definitions(
    E03_Routing
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)

target_link_libraries(
    E03_Routing
    PRIVATE
        essm::types
        essm::logger
        essm::service
        essm::router
)
