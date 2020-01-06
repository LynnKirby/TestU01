# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

cmake_minimum_required(VERSION 3.16)

project(TestU01 C)

include(CheckIncludeFile)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

#
# Handle build options.
#

# Enable warnings by default if we're a standalone project. Disable them if
# we're built as a subdirectory.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(enable_warnings ON)
else()
    set(enable_warnings OFF)
endif()

set(TESTU01_ENABLE_WARNINGS enable_warnings CACHE BOOL "Enable warnings.")

if(NOT TESTU01_ENABLE_WARNINGS)
    if(MSVC)
        add_compile_options(/w)
    else()
        add_compile_options(-w)
    endif()
endif()

#
# Global settings.
#

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

#
# Lists of all modules (i.e. source files).
#

set(mylib_modules gdef addstr bitset chrono mystr num num2 tables util)

set(probdist_modules fmass fdist fbar finv gofs gofw statcoll wdist)

set(testu01_modules unif01    ulcg      umrg      ucarry    utaus    ugfsr
                    uinv      uquad     ucubic    ulec      utezuka  umarsa
                    uweyl     uknuth    uwu       unumrec   uvaria   usoft
                    ugranger  ucrypto   ufile     udeng     utouzin  uautomata
                    uxorshift ubrent    rijndael-alg-fst    tu01_sha1
                    scatter   swrite    sres      smultin   sknuth   smarsa
                    sstring   svaria    snpair    swalk     sentrop  sspectral
                    scomp     sspacings vectorsF2 bbattery
                    ffam      fcong     ffsr      ftab      fres     fcho
                    fmultin   fmarsa    fknuth    fwalk     fstring  fspectral
                    fvaria    fnpair)

foreach(module_group IN ITEMS testu01 probdist mylib)
    foreach(module IN LISTS ${module_group}_modules)
        list(APPEND all_sources ${module_group}/${module}.c)
    endforeach()
endforeach()

#
# Generate config headers.
#

if(UNIX)
    list(APPEND CMAKE_REQUIRED_LIBRARIES m)
endif()

set(PACKAGE_STRING "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

check_include_file(dlfcn.h       HAVE_DLFCN_H)
check_include_file(gmp.h         HAVE_GMP_H)
check_include_file(memory.h      HAVE_MEMORY_H)
check_include_file(strings.h     HAVE_STRINGS_H)
check_include_file(sys/stat.h    HAVE_SYS_STAT_H)
check_include_file(sys/types.h   HAVE_SYS_TYPES_H)
check_include_file(sys/utsname.h HAVE_SYS_UTSNAME_H)
check_include_file(unistd.h      HAVE_UNISTD_H)
check_include_file(windows.h     HAVE_WINDOWS_H)

check_symbol_exists(erf    math.h   HAVE_ERF)
check_symbol_exists(lgamma math.h   HAVE_LGAMMA)
check_symbol_exists(log1p  math.h   HAVE_LOG1P)
check_symbol_exists(random stdlib.h HAVE_RANDOM)

configure_file(include/config.h.in   include/config.h)
configure_file(include/gdefconf.h.in include/gdefconf.h)

#
# Build the TeX to header file converter.
#

add_executable(tcode mylib/tcode.c)

#
# The main library. We build this as one static library instead of multiple
# smaller libraries.
#

add_library(testu01 STATIC ${all_sources})

if(UNIX)
    target_link_libraries(testu01 PUBLIC m)
endif()

target_include_directories(
    testu01
    PUBLIC
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_compile_definitions(testu01 PRIVATE HAVE_CONFIG_H)

#
# Build headers from TeX source.
#

configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/testu01/TestU01.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/TestU01.h
    COPYONLY
)

foreach(module_group IN ITEMS mylib probdist testu01)
    foreach(module IN LISTS ${module_group}_modules)
        # Generate the header.
        add_custom_command(
            OUTPUT
                ${CMAKE_CURRENT_BINARY_DIR}/include/${module}.h
            COMMAND
                tcode
                "${CMAKE_CURRENT_LIST_DIR}/${module_group}/${module}.tex"
                "${CMAKE_CURRENT_BINARY_DIR}/include/${module}.h"
        )

        # Add generated header as a source to create a file level dependency.
        target_sources(
            testu01
            PRIVATE
            ${CMAKE_CURRENT_BINARY_DIR}/include/${module}.h
        )
    endforeach()
endforeach()
