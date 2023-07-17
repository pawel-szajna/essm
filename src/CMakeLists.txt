if(ESSM_BUILD_UT)
    message(STATUS "ESSM unit tests enabled")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)
endif()

add_subdirectory(types)
add_subdirectory(helpers)
add_subdirectory(logger)
add_subdirectory(events)
add_subdirectory(service)
add_subdirectory(router)
add_subdirectory(state_machine)
