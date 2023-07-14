add_executable(
    E04_StateMachine
        main.cpp
)

set_target_properties(
    E04_StateMachine
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
)

target_compile_definitions(
    E04_StateMachine
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)

target_link_libraries(
    E04_StateMachine
    PRIVATE
        essm::logger
        essm::events
        essm::state_machine
)
