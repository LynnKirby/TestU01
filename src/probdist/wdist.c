/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/wdist.h"
#include "TestU01/fdist.h"



/*=========================================================================*/

double wdist_Normal (double Junk[], double x)
{
   return fdist_Normal2 (x);
}


double wdist_ChiSquare (double W[], double x)
{
   long N = (long) W[0];
   return fdist_ChiSquare2 (N, 12, x);
}


double wdist_Unif (double Junk[], double x)
{
   return fdist_Unif (x);
}

