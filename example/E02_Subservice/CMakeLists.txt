add_executable(
    Subservice
        services/Bank.cpp
        services/Payment.cpp
        main.cpp
)

set_target_properties(
    Subservice
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_link_libraries(
    Subservice
    PRIVATE
        essm::logger
        essm::events
        essm::service
)

target_compile_definitions(
    Subservice
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)
