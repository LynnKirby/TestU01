# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

find_package(Python3 REQUIRED)

set(headers ${_TU01_INVERTED_HEADERS})
set(script ${_TU01_UTILS_DIR}/extract-header-text.py)

foreach(header IN LISTS _TU01_INVERTED_HEADERS)
    set(src ${CMAKE_CURRENT_LIST_DIR}/TestU01/${header}.h)
    set(dest ${_TU01_DOC_OUTPUT_DIR}/${header}.md)

    list(APPEND docheaders_src ${dest})

    add_custom_command(
        OUTPUT ${dest}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${_TU01_DOC_OUTPUT_DIR}
        COMMAND ${Python3_EXECUTABLE} ${script} ${src} -o ${dest}
        MAIN_DEPENDENCY ${src}
        DEPENDS ${script})
endforeach()

add_custom_target(docheaders ALL DEPENDS ${docheaders_src})
