/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/ugranger.h"
#include "TestU01/utaus.h"
#include "TestU01/ulcg.h"
#include "TestU01/uinv.h"
#include "TestU01/ucubic.h"
#include "TestU01/unif01.h"
#include "TestU01/num.h"

#ifdef USE_GMP
#include <gmp.h>
#endif




/*========================================================================*/

unif01_Gen * ugranger_CreateCombLCGInvExpl (
   long m1, long a1, long c1, long s1, long m2, long a2, long c2)
{
   unif01_Gen *gen1, *gen2;
   double x = m1 * (double) a1;

   if (x + c1 >= num_TwoExp[53] || -x >= num_TwoExp[53]) {
      gen1 = ulcg_CreateLCG (m1, a1, c1, s1);
   } else
      gen1 = ulcg_CreateLCGFloat (m1, a1, c1, s1);

   gen2 = uinv_CreateInvExpl (m2, a2, c2);
   return unif01_CreateCombAdd2 (gen1, gen2, "ugranger_CreateCombLCGInvExpl:");
}

void ugranger_DeleteCombLCGInvExpl (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteGen (param->gen1);
   uinv_DeleteGen (param->gen2);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/
#ifdef USE_GMP

unif01_Gen * ugranger_CreateCombBigLCGInvExpl (
   char * m1, char * a1, char * c1, char * s1, long m2, long a2, long c2)
{
   unif01_Gen *gen1, *gen2;

   gen1 = ulcg_CreateBigLCG (m1, a1, c1, s1);
   gen2 = uinv_CreateInvExpl (m2, a2, c2);
   return unif01_CreateCombAdd2 (gen1, gen2, "ugranger_CreateCombBigLCGInvExpl:");
}

void ugranger_DeleteCombBigLCGInvExpl (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteBigLCG (param->gen1);
   uinv_DeleteGen (param->gen2);
   unif01_DeleteCombGen (gen);
}

#endif

/*========================================================================*/

unif01_Gen * ugranger_CreateCombLCGCub (
   long m1, long a1, long c1, long s1, long m2, long a2, long s2)
{
   unif01_Gen *gen1, *gen2;
   double x = m1 * (double) a1;

   if (x + c1 >= num_TwoExp[53] || -x >= num_TwoExp[53]) {
      gen1 = ulcg_CreateLCG (m1, a1, c1, s1);
   } else
      gen1 = ulcg_CreateLCGFloat (m1, a1, c1, s1);

   gen2 = ucubic_CreateCubic1Float (m2, a2, s2);
   return unif01_CreateCombAdd2 (gen1, gen2, "ugranger_CreateCombLCGCub:");
}

void ugranger_DeleteCombLCGCub (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteGen (param->gen1);
   ucubic_DeleteGen (param->gen2);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/

#ifdef USE_GMP
unif01_Gen * ugranger_CreateCombBigLCGCub (
   char * m1, char * a1, char * c1, char * s1, long m2, long a2, long s2)
{
   unif01_Gen *gen1, *gen2;

   gen1 = ulcg_CreateBigLCG (m1, a1, c1, s1);
   gen2 = ucubic_CreateCubic1Float (m2, a2, s2);
   return unif01_CreateCombAdd2 (gen1, gen2, "ugranger_CreateCombBigLCGCub:");
}

void ugranger_DeleteCombBigLCGCub (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteBigLCG (param->gen1);
   ucubic_DeleteGen (param->gen2);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/

unif01_Gen * ugranger_CreateCombTausBigLCG (
   unsigned int k1, unsigned int q1, unsigned int s1, unsigned int SS1,
   unsigned int k2, unsigned int q2, unsigned int s2, unsigned int SS2,
   char * m, char * a, char * c, char * SS3)
{
   unif01_Gen *gen1, *gen2;

   gen1 = utaus_CreateCombTaus2 (k1, k2, q1, q2, s1, s2, SS1, SS2);
   gen2 = ulcg_CreateBigLCG (m, a, c, SS3);
   return unif01_CreateCombAdd2 (gen1, gen2, "ugranger_CreateCombTausBigLCG:");
}

void ugranger_DeleteCombTausBigLCG (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteBigLCG (param->gen2);
   utaus_DeleteGen (param->gen1);
   unif01_DeleteCombGen (gen);
}

#endif

/*========================================================================*/

unif01_Gen * ugranger_CreateCombTausLCG21xor (
   unsigned int k1, unsigned int q1, unsigned int s1, unsigned int SS1,
   unsigned int k2, unsigned int q2, unsigned int s2, unsigned int SS2,
   long m, long a, long c, long SS3)
{
   unif01_Gen *gen1, *gen2;
   double x = m * (double) a;

   gen1 = utaus_CreateCombTaus2 (k1, k2, q1, q2, s1, s2, SS1, SS2);
   if (x + c >= num_TwoExp[53] || -x >= num_TwoExp[53]) {
      gen2 = ulcg_CreateLCG (m, a, c, SS3 % m);
   } else
      gen2 = ulcg_CreateLCGFloat (m, a, c, SS3 % m);
   return unif01_CreateCombXor2 (gen1, gen2,
       "ugranger_CreateCombTausLCG21xor:");
}

void ugranger_DeleteCombTausLCG21xor (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ulcg_DeleteGen (param->gen2);
   utaus_DeleteGen (param->gen1);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/

unif01_Gen * ugranger_CreateCombTausCub21xor (
   unsigned int k1, unsigned int q1, unsigned int s1, unsigned int SS1,
   unsigned int k2, unsigned int q2, unsigned int s2, unsigned int SS2,
   long m, long a, long SS3)
{
   unif01_Gen *gen1, *gen2;

   gen1 = utaus_CreateCombTaus2 (k1, k2, q1, q2, s1, s2, SS1, SS2);
   gen2 = ucubic_CreateCubic1Float (m, a, m % SS3);
   return unif01_CreateCombXor2 (gen1, gen2,
       "ugranger_CreateCombTausCub21xor:");
}

void ugranger_DeleteCombTausCub21xor (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   ucubic_DeleteGen (param->gen2);
   utaus_DeleteGen (param->gen1);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/

unif01_Gen * ugranger_CreateCombTausInvExpl21xor (
   unsigned int k1, unsigned int q1, unsigned int s1, unsigned int SS1,
   unsigned int k2, unsigned int q2, unsigned int s2, unsigned int SS2,
   long m, long a, long c)
{
   unif01_Gen *gen1, *gen2;

   gen1 = utaus_CreateCombTaus2 (k1, k2, q1, q2, s1, s2, SS1, SS2);
   gen2 = uinv_CreateInvExpl (m, a, c);
   return unif01_CreateCombXor2 (gen1, gen2,
       "ugranger_CreateCombTausInvExpl21xor:");
}

void ugranger_DeleteCombTausInvExpl21xor (unif01_Gen *gen)
{
   unif01_Comb2_Param *param = gen->param;

   uinv_DeleteGen (param->gen2);
   utaus_DeleteGen (param->gen1);
   unif01_DeleteCombGen (gen);
}


/*========================================================================*/
