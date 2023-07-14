add_executable(
    E03_Routing
        main.cpp
)

target_compile_definitions(
    E03_Routing
    PRIVATE
        ESSM_LOGGER_BACKEND_FMT
)

target_link_libraries(
    E03_Routing
    PRIVATE
        essm::types
        essm::logger
        essm::service
        essm::router
)
