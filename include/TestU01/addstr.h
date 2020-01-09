/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#ifndef TESTU01_ADDSTR_H
#define TESTU01_ADDSTR_H

#include "TestU01/gdef.h"
#include <stddef.h>

/**
 * # addstr
 *
 * The functions described here are convenient tools for constructing character
 * strings that contain a series of numeric parameters, with their values.
 *
 * For example, suppose one wishes to put "`LCG with m = 101, a = 12, s = 1`" in
 * the string `str`, where the actual numbers 101, 12, and 1 must be taken as
 * the values of `long` integer variables `m`, `a`, and `s`. This can be
 * achieved by the instructions:
 *
 * ```c
 * strcpy(str, "LCG with ");
 * addstr_Long(str, " m = ", m);
 * addstr_Long(str, ", a = ", m);
 * addstr_Long(str, ", s = ", s);
 * ```
 *
 * Each function `addstr_...(char *to, const char *add, ...)` first appends the
 * string `add` to the string `to`, then appends to it a character string
 * representation of the number (or array of numbers) specified by its last
 * parameter.
 *
 * In the case of an array of numbers (e.g., `addstr_ArrayLong()`), the
 * parameter `high` specifies the size of the array, and the elements
 * `[0..high-1]` are added to `str`.
 *
 * The `...LONG` versions are for 64-bit integers.
 *
 * In all cases, the string `to` should be large enough to accomodate what is
 * appended to it.
 *
 * ## Prototypes
 */

void addstr_Int(char *to, const char *add, int n);
void addstr_Uint(char *to, const char *add, unsigned int n);
void addstr_Long(char *to, const char *add, long n);
void addstr_Ulong(char *to, const char *add, unsigned long n);
void addstr_Bool(char *to, const char *add, int b);
void addstr_Char(char *to, const char *add, char c);
void addstr_Double(char *to, const char *add, double x);
void addstr_LONG(char *to, const char *add, int64_t n);
void addstr_ULONG(char *to, const char *add, uint64_t n);
void addstr_ArrayInt(char *to, const char *add, size_t high, int[]);
void addstr_ArrayUint(char *to, const char *add, size_t high, unsigned int[]);
void addstr_ArrayLong(char *to, const char *add, size_t high, long[]);
void addstr_ArrayUlong(char *to, const char *add, size_t high, unsigned long[]);
void addstr_ArrayDouble(char *to, const char *add, size_t high, double[]);

#endif
