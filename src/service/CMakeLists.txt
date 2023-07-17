add_essm_library(
    NAME service
    TYPE INTERFACE
    DEPENDENCIES
        essm::types
        essm::events
        essm::logger
    TESTS
        EventServiceTest.cpp
)
