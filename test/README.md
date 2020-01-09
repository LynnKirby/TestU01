<!-- SPDX-License-Identifier: CC0-1.0 -->
<!-- SPDX-FileCopyrightText: 2020 Lynn Kirby -->

# Test Guide

Tests are done with [CMocka](https://cmocka.org) but we provide some useful
features on top of that.

Tests are defined in the `*.c` files in this directory. They have the general
structure:

```c
#include "test.h"

TEST(my_test1) {
    // assertions
}

TEST(my_test2) {
    // assertions
}
```

Each test file is listed in `test_files.cmake`. CMake uses this file to build
the test executable. The `tu01_add_test_file()` command is a macro that simply
appends the file to a list. We use `test_files.cmake` for dependency tracking
instead of globbing.

The script `gen_runner.py` generates the source of the test runner executable.
It gets the list of files from `test_files.cmake` then extracts each test
name from the `*.c` source files.
