add_essm_library(
    NAME state_machine
    TYPE INTERFACE
    DEPENDENCIES
        essm::types
        essm::events
        essm::service
        essm::logger
)
