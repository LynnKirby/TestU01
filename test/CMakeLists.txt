# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

include(FetchContent)

#
# Find installed CMocka or build it ourselves.
#

find_package(cmocka 1.1.5 QUIET)

if(NOT cmocka_FOUND)
    if(NOT TESTU01_BUILD_THIRDPARTY)
        message(FATAL_ERROR "Could not find cmocka-1.1.5")
    endif()

    FetchContent_Declare(
        cmocka_git
        GIT_REPOSITORY https://gitlab.com/cmocka/cmocka.git
        GIT_TAG cmocka-1.1.5
        GIT_SHALLOW ON)

    FetchContent_Populate(cmocka_git)

    # Ensure we don't build anything we don't need.
    set(WITH_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(UNIT_TESTING OFF CACHE BOOL "" FORCE)

    add_subdirectory(${cmocka_git_SOURCE_DIR} ${cmocka_git_BINARY_DIR})
endif()

#
# Include test files from `test_files.cmake`.
#

find_package(Python3 REQUIRED)

macro(tu01_add_test_file file)
    list(APPEND test_files ${file})
endmacro()

include(${CMAKE_CURRENT_LIST_DIR}/test_files.cmake)

#
# Build the test runner.
#

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/test_runner.c
    COMMAND
        ${Python3_EXECUTABLE}
        gen_runner.py
        ${CMAKE_CURRENT_BINARY_DIR}/test_runner.c
    DEPENDS
        gen_runner.py
        ${test_files}
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR})

add_executable(
    tu01_test_runner
    ${CMAKE_CURRENT_BINARY_DIR}/test_runner.c
    ${test_files})

target_include_directories(tu01_test_runner PRIVATE .)

target_link_libraries(
    tu01_test_runner
    PRIVATE
    testu01_build_config
    testu01 cmocka)

add_test(NAME alltests COMMAND tu01_test_runner)

#
# Lint tests.
#

add_test(
    NAME clang-format
    COMMAND ${Python3_EXECUTABLE} utils/run-clang-format.py -r .
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../)
