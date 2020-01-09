# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

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

set(_TU01_INVERTED_HEADERS addstr)

foreach(module_group IN ITEMS testu01 probdist mylib)
    foreach(module IN LISTS ${module_group}_modules)
        list(APPEND all_sources ${module_group}/${module}.c)
    endforeach()
endforeach()

#
# Build the TeX to header file converter.
#

add_executable(tcode mylib/tcode.c)
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
    ${_TU01_INCLUDE_DIR}
    ${_TU01_INCLUDE_OUTPUT_DIR})

#
# Build headers from TeX source.
#

foreach(module_group IN ITEMS mylib probdist testu01)
    foreach(module IN LISTS ${module_group}_modules)
        if(${module} IN_LIST _TU01_INVERTED_HEADERS)
            continue()
        endif()

        set(src "${CMAKE_CURRENT_LIST_DIR}/${module_group}/${module}.tex")
        set(dest "${_TU01_INCLUDE_OUTPUT_DIR}/TestU01/${module}.h")

        # Generate the header.
        add_custom_command(
            OUTPUT ${dest}
            MAIN_DEPENDENCY ${src}
            COMMAND tcode ${src} ${dest})

        # Add generated header as a source to create a file level dependency.
        target_sources(testu01 PRIVATE ${dest})
    endforeach()
endforeach()
