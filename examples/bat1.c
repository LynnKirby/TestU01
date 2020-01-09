/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/bbattery.h"
#include "TestU01/ulcg.h"
#include "TestU01/unif01.h"

int main(void)
{
    unif01_Gen *gen = ulcg_CreateLCG(2147483647, 16807, 0, 12345);
    bbattery_SmallCrush(gen);
    ulcg_DeleteGen(gen);
    return 0;
}
