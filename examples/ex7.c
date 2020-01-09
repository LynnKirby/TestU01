/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/unif01.h"
#include "TestU01/bbattery.h"

unsigned int xorshift (void);
double MRG32k3a (void);

int main (void)
{
   unif01_Gen *gen;

   gen = unif01_CreateExternGen01 ("MRG32k3a", MRG32k3a);
   bbattery_SmallCrush (gen);
   unif01_DeleteExternGen01 (gen);

   gen = unif01_CreateExternGenBits ("xorshift", xorshift);
   bbattery_SmallCrush (gen);
   unif01_DeleteExternGenBits (gen);

   return 0;
}
