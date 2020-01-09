/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/smarsa.h"
#include "TestU01/sres.h"
#include "TestU01/swrite.h"
#include "TestU01/ulcg.h"
#include "TestU01/unif01.h"

int main(void)
{
    swrite_Basic = false;

    unif01_Gen *gen = ulcg_CreateLCG(2147483647, 397204094, 0, 12345);
    sres_Poisson *res = sres_CreatePoisson();

    smarsa_BirthdaySpacings(gen, res, 1, 1000, 0, 10000, 2, 1);
    /* .... Examine or postprocess res */

    smarsa_BirthdaySpacings(gen, res, 1, 10000, 0, 1000000, 2, 1);
    /* .... Examine or postprocess res */

    sres_DeletePoisson(res);
    ulcg_DeleteGen(gen);
    return 0;
}
