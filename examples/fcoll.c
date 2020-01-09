/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/fcho.h"
#include "TestU01/fcong.h"
#include "TestU01/ffam.h"
#include "TestU01/fmultin.h"
#include "TestU01/smultin.h"

int main(void)
{
    int NbDelta = 1;
    double ValDelta[] = { -1 };
    int t = 2;

    ffam_Fam *fam = fcong_CreateLCG("LCGGood.par", 10, 30, 1);
    smultin_Param *par
        = smultin_CreateParam(NbDelta, ValDelta, smultin_GenerCellSerial, 2);
    fmultin_res *res = fmultin_CreateRes(par);
    fcho_Cho *chon = fcho_CreateSampleSize(0.5, 1, 0, NULL, "n");
    fcho_Cho *chod = fmultin_CreatePer_DT(t, 1);
    fcho_Cho2 *cho = fcho_CreateCho2(chon, chod);

    fmultin_Serial1(fam, par, res, cho, 1, 0, t, true, 21, 1, 5, 1);

    fcho_DeleteCho2(cho);
    fmultin_DeletePer(chod);
    fcho_DeleteSampleSize(chon);
    fmultin_DeleteRes(res);
    smultin_DeleteParam(par);
    fcong_DeleteLCG(fam);

    return 0;
}
