/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/unif01.h"
#include "TestU01/ulcg.h"
#include "TestU01/ulec.h"
#include "my16807.h"
#include <stdio.h>

int main (void)
{
   unif01_Gen *gen;
   double x = 0.0;
   int i;

   gen = ulcg_CreateLCGFloat (2147483647, 16807, 0, 12345);
   unif01_TimerSumGenWr (gen, 10000000, true);
   ulcg_DeleteGen (gen);

   gen = CreateMy16807 (12345);
   unif01_TimerSumGenWr (gen, 10000000, true);
   DeleteMy16807 (gen);

   gen = ulec_CreateMRG32k3a (123., 123., 123., 123., 123., 123.);
   unif01_TimerSumGenWr (gen, 10000000, true);
   ulec_DeleteGen (gen);

   gen = ulec_Createlfsr113 (12345, 12345, 12345, 12345);
   unif01_TimerSumGenWr (gen, 10000000, true);
   for (i = 0; i < 100; i++)
      x += unif01_StripD (gen, 0);
   printf ("Sum = %14.10f\n", x);
   ulec_DeleteGen (gen);

   return 0;
}
