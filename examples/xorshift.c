/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

static unsigned int y = 2463534242U;

unsigned int xorshift (void)
{
   y ^= (y << 13);
   y ^= (y >> 17);
   return y ^= (y << 5);
}
