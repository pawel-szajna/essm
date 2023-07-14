add_library(
    essm_router
    INTERFACE
)

add_library(
    essm::router
    ALIAS
        essm_router
)

#set_target_properties(
#    essm_router
#    PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#)

target_include_directories(
    essm_router
    INTERFACE
        include
    #    PRIVATE
    #        include/router
)

target_link_libraries(
    essm_router
    INTERFACE
        essm::types
        essm::events
        essm::service
        essm::logger
)
