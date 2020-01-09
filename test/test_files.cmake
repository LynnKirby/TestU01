# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: 2020 Lynn Kirby
#
# This file is used by CMake and contains all of the *.c test sources in this
# directory. It should only contain tu01_add_test_file() commands because it
# is also parsed by gen_runner.py to produce the runner executable source.

tu01_add_test_file(addstr.c)
