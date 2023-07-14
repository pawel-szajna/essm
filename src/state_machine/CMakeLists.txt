add_library(
    essm_state_machine
    INTERFACE
)

add_library(
    essm::state_machine
    ALIAS
        essm_state_machine
)

set_target_properties(
    essm_state_machine
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(
    essm_state_machine
    INTERFACE
        include
#    PRIVATE
#        include/state_machine
)

target_link_libraries(
    essm_state_machine
    INTERFACE
        essm::types
        essm::events
        essm::service
        essm::logger
)
