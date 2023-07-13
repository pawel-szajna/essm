add_executable(
    E02_Subservice
        services/Bank.cpp
        services/Payment.cpp
        main.cpp
)

set_target_properties(
    E02_Subservice
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_link_libraries(
    E02_Subservice
    PRIVATE
        essm::logger
        essm::events
        essm::service
)

target_compile_definitions(
    E02_Subservice
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)
