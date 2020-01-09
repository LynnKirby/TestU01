/*
 * SPDX-License-Identifier: CC0-1.0
 * SPDX-FileCopyrightText: 2020 Lynn Kirby
 *
 * Common test header file.
 */

#ifndef TESTU01_TEST_H
#define TESTU01_TEST_H

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#ifndef __has_extension
#define __has_extension(x) 0
#endif

#if defined(_MSC_VER) && !__has_extension(c_static_assert)
#define _Static_assert(cond, msg) \
    typedef int _static_assert_##__COUNTER__[(cond) ? 1 : -1];
#endif

#define TEST(name)                       \
    static void testactual_##name(void); \
    void test_##name(void** state)       \
    {                                    \
        (void)state; /* unused */        \
        testactual_##name();             \
    }                                    \
    void testactual_##name(void)

#endif
