add_library(
    essm_service
    INTERFACE
)

add_library(
    essm::service
    ALIAS
        essm_service
)

set_target_properties(
    essm_service
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(
    essm_service
    INTERFACE
        include
#    PRIVATE
#        include/service
)

target_link_libraries(
    essm_service
    INTERFACE
        essm::types
        essm::events
        essm::logger
)
