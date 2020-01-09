/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/bbattery.h"
#include "TestU01/unif01.h"
#include "TestU01/usoft.h"

int main(void)
{
    int n = 1024 * 1024;

    /* Test the first n bits of binary file vax.bin */
    bbattery_AlphabitFile("vax.bin", n);

    /* Test the Java random number generator */
    unif01_Gen *gen = usoft_CreateJava48(1234567, 1);
    bbattery_Alphabit(gen, n, 0, 32);

    return 0;
}
