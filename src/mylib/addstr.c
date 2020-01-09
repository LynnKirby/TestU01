/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/addstr.h"

#include <stdio.h>
#include <string.h>

void addstr_Char(char *to, const char *add, char c)
{
    sprintf(to + strlen(to), "%s%c", add, c);
}

void addstr_Int(char *to, const char *add, int n)
{
    sprintf(to + strlen(to), "%s%i", add, n);
}

void addstr_Uint(char *to, const char *add, unsigned int n)
{
    sprintf(to + strlen(to), "%s%u", add, n);
}

void addstr_Long(char *to, const char *add, long n)
{
    sprintf(to + strlen(to), "%s%li", add, n);
}

void addstr_Ulong(char *to, const char *add, unsigned long n)
{
    sprintf(to + strlen(to), "%s%lu", add, n);
}

void addstr_LONG(char *to, const char *add, int64_t n)
{
    sprintf(to + strlen(to), "%s%" PRIi64, add, n);
}

void addstr_ULONG(char *to, const char *add, uint64_t n)
{
    sprintf(to + strlen(to), "%s%" PRIu64, add, n);
}

void addstr_Double(char *to, const char *add, double x)
{
    sprintf(to + strlen(to), "%s%.16G", add, x);
}

void addstr_Bool(char *to, const char *add, int b)
{
    sprintf(to + strlen(to), "%s%s", add, b ? "TRUE" : "FALSE");
}

void addstr_ArrayInt(char *to, const char *add, size_t high, int val[])
{
    strcat(to, add);
    addstr_Int(to, "(", val[0]);

    for (size_t j = 1; (j < high) && (j < 5); j++) {
        addstr_Int(to, ", ", val[j]);
    }

    if (high > 5) {
        strcat(to, ", ... )");
    } else {
        strcat(to, ")");
    }
}

void addstr_ArrayUint(char *to, const char *add, size_t high, unsigned int val[])
{
    strcat(to, add);
    addstr_Uint(to, "(", val[0]);

    for (size_t j = 1; (j < high) && (j < 5); j++) {
        addstr_Uint(to, ", ", val[j]);
    }

    if (high > 5) {
        strcat(to, ", ... )");
    } else {
        strcat(to, ")");
    }
}

void addstr_ArrayLong(char *to, const char *add, size_t high, long val[])
{
    strcat(to, add);
    addstr_Long(to, "(", val[0]);

    for (size_t j = 1; (j < high) && (j < 5); j++) {
        addstr_Long(to, ", ", val[j]);
    }

    if (high > 5) {
        strcat(to, ", ... )");
    } else {
        strcat(to, ")");
    }
}

void addstr_ArrayUlong(char *to, const char *add, size_t high, unsigned long val[])
{
    strcat(to, add);
    addstr_Ulong(to, "(", val[0]);

    for (size_t j = 1; (j < high) && (j < 5); j++) {
        addstr_Ulong(to, ", ", val[j]);
    }

    if (high > 5) {
        strcat(to, ", ... )");
    } else {
        strcat(to, ")");
    }
}

void addstr_ArrayDouble(char *to, const char *add, size_t high, double val[])
{
    strcat(to, add);
    addstr_Double(to, "(", val[0]);

    for (size_t j = 1; (j < high) && (j < 5); j++) {
        addstr_Double(to, ", ", val[j]);
    }

    if (high > 5) {
        strcat(to, ", ... )");
    } else {
        strcat(to, ")");
    }
}
