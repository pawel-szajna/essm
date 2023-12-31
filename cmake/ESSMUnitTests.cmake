function(essm_acquire_google_test)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)
endfunction()

function(add_essm_ut)
    set(VALUE_ARGS TESTED_LIBRARY)
    set(LIST_ARGS SOURCES)
    cmake_parse_arguments(
        UT
        "" "${VALUE_ARGS}" "${LIST_ARGS}" ${ARGN}
    )

    set(UT_TESTS_MODULE ut_${UT_TESTED_LIBRARY})
    list(TRANSFORM UT_SOURCES PREPEND test/)

    add_executable(
        ${UT_TESTS_MODULE}
        ${UT_SOURCES}
    )

    set_target_properties(
        ${UT_TESTS_MODULE}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/ut"
    )

    target_compile_definitions(
        ${UT_TESTS_MODULE}
        PRIVATE
            ESSM_LOGGER_BACKEND_FMT
            ESSM_LOGGER_ENABLE_DEBUG
    )

    gtest_discover_tests(${UT_TESTS_MODULE})

    target_include_directories(
        ${UT_TESTS_MODULE}
        PRIVATE
            $<TARGET_PROPERTY:essm_${UT_TESTED_LIBRARY},INCLUDE_DIRECTORIES>
    )

    target_link_libraries(
        ${UT_TESTS_MODULE}
        PRIVATE
            essm::${UT_TESTED_LIBRARY}
            fmt
            gmock
            gtest_main
    )
endfunction()
