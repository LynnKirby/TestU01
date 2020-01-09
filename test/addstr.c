/*
 * SPDX-License-Identifier: CC0-1.0
 * SPDX-FileCopyrightText: 2020 Lynn Kirby
 */

#include "TestU01/addstr.h"
#include "test.h"

#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define CONCAT(x, y) x##y

#define COMMON_INT_INIT(fn, type)             \
    char str_min[100];                        \
    char str_max[100];                        \
    char str_42[100];                         \
    strcpy(str_min, "foo");                   \
    strcpy(str_max, "foo");                   \
    strcpy(str_42, "foo");                    \
    fn(str_min, "bar: ", CONCAT(type, _MIN)); \
    fn(str_max, "bar: ", CONCAT(type, _MAX)); \
    fn(str_42, "bar: ", 42);

#define COMMON_ARRAY_INIT(fn, type_lc, type)                          \
    char str3[100];                                                   \
    char str6[100];                                                   \
    type_lc data[]                                                    \
        = { CONCAT(type, _MIN), CONCAT(type, _MAX), 42, 43, 44, 46 }; \
    strcpy(str3, "foo");                                              \
    strcpy(str6, "foo");                                              \
    fn(str3, "bar: ", 3, data);                                       \
    fn(str6, "bar: ", 6, data);

#define UINT_MIN 0
#define ULONG_MIN 0
#define UINT64_MIN 0

#define INT32_MIN_STR "-2147483648"
#define INT32_MAX_STR "2147483647"
#define UINT32_MAX_STR "4294967295"

#define INT64_MIN_STR "-9223372036854775808"
#define INT64_MAX_STR "9223372036854775807"
#define UINT64_MAX_STR "18446744073709551615"

_Static_assert(INT_MAX == INT32_MAX, "assumed 32-bit int");
#define INT_MIN_STR INT32_MIN_STR
#define INT_MAX_STR INT32_MAX_STR
#define UINT_MAX_STR UINT32_MAX_STR

#if LONG_MAX == INT32_MAX
#define LONG_MIN_STR INT32_MIN_STR
#define LONG_MAX_STR INT32_MAX_STR
#define ULONG_MAX_STR UINT32_MAX_STR
#elif LONG_MAX == INT64_MAX
#define LONG_MIN_STR INT64_MIN_STR
#define LONG_MAX_STR INT64_MAX_STR
#define ULONG_MAX_STR UINT64_MAX_STR
#endif

TEST(addstr_Char)
{
    char str[100];
    strcpy(str, "foo");
    addstr_Char(str, "bar: ", 'b');
    assert_string_equal(str, "foobar: b");
}

TEST(addstr_Int)
{
    COMMON_INT_INIT(addstr_Int, INT)
    assert_string_equal(str_min, "foobar: " INT_MIN_STR);
    assert_string_equal(str_max, "foobar: " INT_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_Uint)
{
    COMMON_INT_INIT(addstr_Uint, UINT)
    assert_string_equal(str_min, "foobar: 0");
    assert_string_equal(str_max, "foobar: " UINT_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_Long)
{
    COMMON_INT_INIT(addstr_Long, LONG)
    assert_string_equal(str_min, "foobar: " LONG_MIN_STR);
    assert_string_equal(str_max, "foobar: " LONG_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_Ulong)
{
    COMMON_INT_INIT(addstr_Ulong, ULONG)
    assert_string_equal(str_min, "foobar: 0");
    assert_string_equal(str_max, "foobar: " ULONG_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_LONG)
{
    COMMON_INT_INIT(addstr_LONG, INT64)
    assert_string_equal(str_min, "foobar: " INT64_MIN_STR);
    assert_string_equal(str_max, "foobar: " INT64_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_ULONG)
{
    COMMON_INT_INIT(addstr_ULONG, UINT64)
    assert_string_equal(str_min, "foobar: 0");
    assert_string_equal(str_max, "foobar: " UINT64_MAX_STR);
    assert_string_equal(str_42, "foobar: 42");
}

TEST(addstr_Double)
{
    char str[100];

    strcpy(str, "foo");
    addstr_Double(str, "bar: ", 0.0);
    assert_string_equal(str, "foobar: 0");

    strcpy(str, "foo");
    addstr_Double(str, "bar: ", 0.1234567890123456789);
    assert_string_equal(str, "foobar: 0.1234567890123457");
}

TEST(addstr_Bool)
{
    char str[100];

    strcpy(str, "foo");
    addstr_Bool(str, "bar: ", true);
    assert_string_equal(str, "foobar: TRUE");

    strcpy(str, "foo");
    addstr_Bool(str, "bar: ", false);
    assert_string_equal(str, "foobar: FALSE");
}

TEST(addstr_ArrayInt)
{
    COMMON_ARRAY_INIT(addstr_ArrayInt, int, INT)
    assert_string_equal(str3, "foobar: (" INT_MIN_STR ", " INT_MAX_STR ", 42)");
    assert_string_equal(
        str6, "foobar: (" INT_MIN_STR ", " INT_MAX_STR ", 42, 43, 44, ... )");
}

TEST(addstr_ArrayUint)
{
    COMMON_ARRAY_INIT(addstr_ArrayUint, unsigned, UINT)
    assert_string_equal(str3, "foobar: (0, " UINT_MAX_STR ", 42)");
    assert_string_equal(
        str6, "foobar: (0, " UINT_MAX_STR ", 42, 43, 44, ... )");
}

TEST(addstr_ArrayLong)
{
    COMMON_ARRAY_INIT(addstr_ArrayLong, long, LONG)
    assert_string_equal(
        str3, "foobar: (" LONG_MIN_STR ", " LONG_MAX_STR ", 42)");
    assert_string_equal(
        str6, "foobar: (" LONG_MIN_STR ", " LONG_MAX_STR ", 42, 43, 44, ... )");
}

TEST(addstr_ArrayUlong)
{
    COMMON_ARRAY_INIT(addstr_ArrayUlong, unsigned long, ULONG)
    assert_string_equal(str3, "foobar: (0, " ULONG_MAX_STR ", 42)");
    assert_string_equal(
        str6, "foobar: (0, " ULONG_MAX_STR ", 42, 43, 44, ... )");
}

TEST(addstr_ArrayDouble)
{
    char str3[100];
    char str6[100];
    double data[] = { 0, 0.1234567890123456789, 42, 43, 44, 46 };
    strcpy(str3, "foo");
    strcpy(str6, "foo");
    addstr_ArrayDouble(str3, "bar: ", 3, data);
    addstr_ArrayDouble(str6, "bar: ", 6, data);

    assert_string_equal(str3, "foobar: (0, 0.1234567890123457, 42)");
    assert_string_equal(
        str6, "foobar: (0, 0.1234567890123457, 42, 43, 44, ... )");
}
