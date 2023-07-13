add_library(
    essm_types
    INTERFACE
)

add_library(
    essm::types
    ALIAS
        essm_types
)

set_target_properties(
    essm_types
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(
    essm_types
    INTERFACE
        include
)
