# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby

set(examples bat1 bat2 bat3 birth1 birth2 ex1 ex4 fbirth fcoll scat scat2)

foreach(example IN LISTS examples)
    add_executable(testu01_example-${example} ${example}.c)
    target_link_libraries(testu01_example-${example}
                          testu01_build_config testu01)
endforeach()

add_executable(testu01_example-ex3 ex3.c my16807.c)
target_link_libraries(testu01_example-ex3 testu01_build_config testu01)

add_executable(testu01_example-ex7 ex7.c mrg32k3a.c xorshift.c)
target_link_libraries(testu01_example-ex7 testu01_build_config testu01)
