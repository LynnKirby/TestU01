/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/unif01.h"
#include "TestU01/ulcg.h"
#include "TestU01/smarsa.h"
#include <stddef.h>

int main (void)
{
   unif01_Gen *gen;
   gen = ulcg_CreateLCG (2147483647, 397204094, 0, 12345);
   smarsa_BirthdaySpacings (gen, NULL, 1, 1000, 0, 10000, 2, 1);
   smarsa_BirthdaySpacings (gen, NULL, 1, 10000, 0, 1000000, 2, 1);
   ulcg_DeleteGen (gen);
   return 0;
}
