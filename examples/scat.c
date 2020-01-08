/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "unif01.h"
#include "ufile.h"
#include "scatter.h"

int main (void)
{
   unif01_Gen *gen;
   gen = ufile_CreateReadText ("excel.pts", 100000);
   scatter_PlotUnif (gen, "excel");
   ufile_DeleteReadText (gen);
   return 0;
}
