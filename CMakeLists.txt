# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

cmake_minimum_required(VERSION 3.16)

project(TestU01 C)

include(CheckIncludeFile)
include(CheckSymbolExists)

# Request C11 but decay to lower version if it's not available. We also set
# per-target compile features below which require C99 or higher. In other words,
# we need C99 but having C11 would be better (just not required).
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(testu01_is_root_project ON)
else()
    set(testu01_is_root_project OFF)
endif()

#
# Define build options.
#

set(TESTU01_ENABLE_WARNINGS ${testu01_is_root_project} CACHE BOOL
    "Show or suppress build warnings.")

set(TESTU01_ENABLE_TESTS ${testu01_is_root_project} CACHE BOOL
    "Enable building and running tests.")

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
        list(APPEND all_sources src/${module_group}/${module}.c)
    endforeach()
endforeach()

#
# Generate config headers.
#

set(TESTU01_PACKAGE_NAME "${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}")

# FIXME: Replace with FindGMP
check_include_file(gmp.h HAVE_GMP_H)
check_symbol_exists(random stdlib.h HAVE_RANDOM)

configure_file(include/TestU01/gdefconf.h.in include/TestU01/gdefconf.h)

#
# Build the TeX to header file converter.
#

add_executable(tcode src/mylib/tcode.c)
target_link_libraries(tcode PRIVATE testu01_build_config)

#
# The main library. We build this as one static library instead of multiple
# smaller libraries.
#

add_library(testu01 STATIC ${all_sources})
target_link_libraries(testu01 PRIVATE testu01_build_config)
target_compile_features(testu01 PUBLIC c_std_99)

if(UNIX)
    target_link_libraries(testu01 PUBLIC m)
endif()

target_include_directories(
    testu01
    PUBLIC
    include
    ${CMAKE_CURRENT_BINARY_DIR}/include)

#
# Build headers from TeX source.
#

foreach(module_group IN ITEMS mylib probdist testu01)
    foreach(module IN LISTS ${module_group}_modules)
        set(src "${CMAKE_CURRENT_LIST_DIR}/src/${module_group}/${module}.tex")
        set(dest "${CMAKE_CURRENT_BINARY_DIR}/include/TestU01/${module}.h")
        # Generate the header.
        add_custom_command(
            OUTPUT ${dest}
            MAIN_DEPENDENCY ${src}
            COMMAND tcode ${src} ${dest})

        # Add generated header as a source to create a file level dependency.
        target_sources( testu01 PRIVATE ${dest})
    endforeach()
endforeach()

#
# Build examples.
#

set(examples bat1 bat2 bat3 birth1 birth2 ex1 ex4 fbirth fcoll scat scat2)

foreach(example IN LISTS examples)
    add_executable(testu01_example-${example} examples/${example}.c)
    target_link_libraries(testu01_example-${example}
                          testu01_build_config testu01)
endforeach()

add_executable(testu01_example-ex3 examples/ex3.c examples/my16807.c)
target_link_libraries(testu01_example-ex3 testu01_build_config testu01)

add_executable(testu01_example-ex7
               examples/ex7.c examples/mrg32k3a.c examples/xorshift.c)
target_link_libraries(testu01_example-ex7 testu01_build_config testu01)


#
# Tests.
#

if(TESTU01_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
