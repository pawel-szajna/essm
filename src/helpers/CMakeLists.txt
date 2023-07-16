add_library(
    essm_helpers
    INTERFACE
)

add_library(
    essm::helpers
    ALIAS
        essm_helpers
)

#set_target_properties(
#    essm_helpers
#    PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#)

target_include_directories(
    essm_helpers
    INTERFACE
        include
#    PRIVATE
#        include/router
)

target_link_libraries(
    essm_helpers
    INTERFACE
)
