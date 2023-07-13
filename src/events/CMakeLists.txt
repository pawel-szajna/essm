add_library(
    essm_events
    INTERFACE
)

add_library(
    essm::events
    ALIAS
        essm_events
)

target_include_directories(
    essm_events
    INTERFACE
        include
)
