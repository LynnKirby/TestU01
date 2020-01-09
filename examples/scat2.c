/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/unif01.h"
#include "TestU01/usoft.h"
#include "TestU01/scatter.h"

int Proj[] = { 1, 3 };
long LacI[] = { 1, 2, 6};
double Lower[] = { 0.0, 0.0, 0.0 };
double Upper[] = { 0.0001, 0.5, 1.0 };

int main (void)
{
   unif01_Gen *gen;

   gen = usoft_CreateVisualBasic (12345);
   scatter_PlotUnif1 (gen, 10000000, 3, false, Proj, Lower, Upper,
		      scatter_latex, 8, true, LacI, "bone");
   usoft_DeleteGen (gen);
   return 0;
}
