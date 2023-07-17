function(add_essm_library)
    set(VALUE_ARGS NAME TYPE)
    set(LIST_ARGS SOURCES TESTS DEPENDENCIES PRIVATE_DEPENDENCIES)
    cmake_parse_arguments(
        LIBRARY
        "" "${VALUE_ARGS}" "${LIST_ARGS}" ${ARGN}
    )

    message(STATUS "Added library essm::${LIBRARY_NAME}")

    list(LENGTH LIBRARY_SOURCES SOURCES_COUNT)
    if(LIBRARY_TYPE STREQUAL INTERFACE AND SOURCES_COUNT GREATER 0)
        message(FATAL_ERROR "Library ${LIBRARY_NAME} has type set to ${LIBRARY_TYPE}, but was given sources")
    endif()
    if(NOT LIBRARY_TYPE STREQUAL INTERFACE AND SOURCES_COUNT EQUAL 0)
        message(FATAL_ERROR "Library ${LIBRARY_NAME} has type set to ${LIBRARY_TYPE}, but has no source files")
    endif()

    list(TRANSFORM LIBRARY_SOURCES PREPEND src/)
    set(INTERNAL_NAME "essm_${LIBRARY_NAME}")
    add_library(
        ${INTERNAL_NAME}
        ${LIBRARY_TYPE}
        ${LIBRARY_SOURCES}
    )
    add_library(
        "essm::${LIBRARY_NAME}"
        ALIAS ${INTERNAL_NAME}
    )
    set_target_properties(
        ${INTERNAL_NAME}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    if(${LIBRARY_TYPE} STREQUAL "INTERFACE")
        target_include_directories(
            ${INTERNAL_NAME}
            INTERFACE include
        )
    else()
        string(TOLOWER ${LIBRARY_NAME} LIBRARY_NAME_LOWERCASE)
        target_include_directories(
            ${INTERNAL_NAME}
            PUBLIC
                include
            PRIVATE
                include/essm/${LIBRARY_NAME_LOWERCASE}
        )
    endif()

    list(LENGTH LIBRARY_DEPENDENCIES DEPENDENCIES_COUNT)
    list(LENGTH LIBRARY_PRIVATE_DEPENDENCIES DEPENDENCIES_PRIVATE_COUNT)

    if(DEPENDENCIES_COUNT GREATER 0 OR PRIVATE_DEPENDENCIES_COUNT GREATER 0)
        if(${LIBRARY_TYPE} STREQUAL "INTERFACE")
            if(DEPENDENCIES_PRIVATE_COUNT GREATER 0)
                message(FATAL_ERROR "Library ${LIBRARY_NAME} has private dependencies defined, but is an interface library")
            endif()
            target_link_libraries(
                ${INTERNAL_NAME}
                INTERFACE
                    ${LIBRARY_DEPENDENCIES}
            )
        else()
            target_link_libraries(
                ${INTERNAL_NAME}
                PUBLIC
                    ${LIBRARY_DEPENDENCIES}
                PRIVATE
                    ${LIBRARY_PRIVATE_DEPENDENCIES}
            )
        endif()
    endif()

    if(ESSM_BUILD_UT)
        list(LENGTH LIBRARY_TESTS TESTS_COUNT)
        if(TESTS_COUNT GREATER 0)
            add_essm_ut(
                TESTED_LIBRARY ${LIBRARY_NAME}
                SOURCES
                    ${LIBRARY_TESTS}
            )
        endif()
    endif()
endfunction()
