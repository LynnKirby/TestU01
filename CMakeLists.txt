# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

cmake_minimum_required(VERSION 3.12)

project(TestU01 C)

include(CheckIncludeFile)
include(CheckSymbolExists)

# Request C11 but decay to lower version if it's not available. We also set
# per-target compile features below which require C99 or higher. In other words,
# we need C99 but having C11 would be better (just not required).
set(CMAKE_C_STANDARD 11)

#
# Define global source and output directories.
#

set(_TU01_UTILS_DIR ${CMAKE_CURRENT_LIST_DIR}/utils)
set(_TU01_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

set(_TU01_BIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(_TU01_LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/lib)
set(_TU01_INCLUDE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/include)
set(_TU01_DOC_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${_TU01_BIN_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${_TU01_LIB_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${_TU01_LIB_OUTPUT_DIR})

#
# Define build options.
#

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(testu01_is_root_project ON)
else()
    set(testu01_is_root_project OFF)
endif()

set(TESTU01_ENABLE_WARNINGS ${testu01_is_root_project} CACHE BOOL
    "Show or suppress build warnings.")

set(TESTU01_ENABLE_TESTS ${testu01_is_root_project} CACHE BOOL
    "Build tests.")

set(TESTU01_ENABLE_EXAMPLES ${testu01_is_root_project} CACHE BOOL
    "Build examples.")

set(TESTU01_BUILD_THIRDPARTY ON CACHE BOOL
    "Download and build dependencies if they cannot be found locally.")

#
# Handle compilation options.
#

add_library(testu01_build_config INTERFACE)

if(TESTU01_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(testu01_build_config INTERFACE /W2)
    else()
	    target_compile_options(
            testu01_build_config
            INTERFACE
            -Wall -Wextra -pedantic
            -Wno-unused-parameter)
    endif()
endif()

#
# Global settings.
#

if(WIN32)
    target_compile_definitions(
        testu01_build_config
        INTERFACE
        _CRT_SECURE_NO_WARNINGS)
endif()

target_compile_features(testu01_build_config INTERFACE c_std_99)

#
# Generate config headers.
#

set(TESTU01_PACKAGE_NAME "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

# FIXME: Replace with FindGMP
check_include_file(gmp.h HAVE_GMP_H)
check_symbol_exists(random stdlib.h HAVE_RANDOM)

configure_file(include/TestU01/gdefconf.h.in include/TestU01/gdefconf.h)

#
# Subdirectories.
#

# TODO: Remove this project-level variable once all the headers have been
# converted. Currently the include/ and src/ build scripts rely on it.
set(_TU01_INVERTED_HEADERS addstr)

add_subdirectory(include)
add_subdirectory(src)

if(TESTU01_ENABLE_EXAMPLES)
    add_subdirectory(examples)
endif()

if(TESTU01_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
