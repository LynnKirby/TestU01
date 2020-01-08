/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "usoft.h"
#include "unif01.h"
#include "bbattery.h"

int main (void)
{
   unif01_Gen *gen;
   int n = 1024*1024;

   /* Test the first n bits of binary file vax.bin */
   bbattery_AlphabitFile ("vax.bin", n);

   /* Test the Java random number generator */
   gen = usoft_CreateJava48 (1234567, 1);
   bbattery_Alphabit (gen, n, 0, 32);

   return 0;
}
