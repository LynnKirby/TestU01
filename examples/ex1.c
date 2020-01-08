/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "unif01.h"
#include "ulcg.h"
#include "ulec.h"
#include <stdio.h>

int main (void)
{
   int i;
   double x;
   unsigned long z;
   unif01_Gen *gen;

   gen = ulcg_CreateLCG (2147483647, 16807, 0, 12345);
   x = 0.0;
   for (i = 0; i < 50; i++)
      x += gen->GetU01(gen->param, gen->state);
   for (i = 0; i < 50; i++)
      x += unif01_StripD (gen, 0);
   printf ("Sum = %14.10f\n\n", x);
   ulcg_DeleteGen (gen);

   gen = ulec_Createlfsr113 (12345, 12345, 12345, 12345);
   for (i = 0; i < 5; i++) {
      z = unif01_StripB (gen, 4, 10);
      printf ("%10lu\n", z);
      }
   ulec_DeleteGen (gen);
   return 0;
}
