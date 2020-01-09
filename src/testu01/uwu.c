/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2002 Richard Simard
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/util.h"
#include "TestU01/addstr.h"

#include "TestU01/uwu.h"
#include "TestU01/unif01.h"

#include <stdio.h>
#include <string.h>



#define LEN  200                  /* Max length of strings */


typedef struct {
   uint64_t S;
} LCGWu61_state;



/*=========================================================================*/

#define LOG_W 64
#define LOG_M 61
#define M 0x1fffffffffffffffULL
#define K1 30
#define K2 19

static double LCGWu61a_U01 (void *junk, void *vsta)
{
   LCGWu61_state *state = vsta;
   uint64_t w1, w2;
   int64_t x1;

   w1 = (state->S >> (LOG_M - K1)) +
      ((state->S << (K1 + LOG_W - LOG_M)) >> (LOG_W - LOG_M));
   w2 = (state->S >> (LOG_M - K2)) +
      ((state->S << (K2 + LOG_W - LOG_M)) >> (LOG_W - LOG_M));
   x1 = w1 - w2;
   if (x1 < 0)
      state->S = x1 + M;
   else
      state->S = x1;
   return state->S / (double) M;
}

/*-----------------------------------------------------------------------*/

static unsigned long LCGWu61a_Bits (void *vpar, void *vsta)
{
   return (unsigned long) (LCGWu61a_U01 (vpar, vsta) * unif01_NORM32);
}

/*-----------------------------------------------------------------------*/

static void WrLCGWu61 (void *vsta)
{
   LCGWu61_state *state = vsta;
   printf (" S = %1" PRIuLEAST64 " \n\n", state->S);
}

/*-----------------------------------------------------------------------*/

unif01_Gen * uwu_CreateLCGWu61a (int64_t s)
{
   unif01_Gen *gen;
   LCGWu61_state *state;
   size_t leng;
   char name[LEN + 1];

   gen = util_Malloc (sizeof (unif01_Gen));
   state = util_Malloc (sizeof (LCGWu61_state));

   strcpy (name,
      "uwu_CreateLCGWu61a:   m = 2^61 - 1,   a = 2^30 - 2^19,   c = 0");
   addstr_LONG (name, ",   s = ", s);
   leng = strlen (name);
   gen->name = util_Calloc (leng + 1, sizeof (char));
   strncpy (gen->name, name, leng);

   state->S = s;
   gen->GetBits = &LCGWu61a_Bits;
   gen->GetU01  = &LCGWu61a_U01;
   gen->Write   = &WrLCGWu61;
   gen->param   = NULL;
   gen->state   = state;
   return gen;
}


/*=========================================================================*/

#undef K1
#undef K2
#define K1 42
#define K2 31

static double LCGWu61b_U01 (void *junk, void *vsta)
{
   LCGWu61_state *state = vsta;
   uint64_t w1, w2;
   int64_t x1;

   w1 = (state->S >> (LOG_M - K1)) +
      ((state->S << (K1 + LOG_W - LOG_M)) >> (LOG_W - LOG_M));
   w2 = (state->S >> (LOG_M - K2)) +
      ((state->S << (K2 + LOG_W - LOG_M)) >> (LOG_W - LOG_M));
   x1 = w1 - w2;
   if (x1 < 0)
      state->S = x1 + M;
   else
      state->S = x1;
   return state->S / (double) M;
}

/*-----------------------------------------------------------------------*/

static unsigned long LCGWu61b_Bits (void *vpar, void *vsta)
{
   return (unsigned long) (LCGWu61b_U01 (vpar, vsta) * unif01_NORM32);
}

/*-----------------------------------------------------------------------*/

unif01_Gen * uwu_CreateLCGWu61b (int64_t s)
{
   unif01_Gen *gen;
   LCGWu61_state *state;
   size_t leng;
   char name[LEN + 1];

   gen = util_Malloc (sizeof (unif01_Gen));
   state = util_Malloc (sizeof (LCGWu61_state));
   strcpy (name,
      "uwu_CreateLCGWu61b:   m = 2^61 - 1,   a = 2^42 - 2^31,   c = 0");
   addstr_LONG (name, ",   s = ", s);
   leng = strlen (name);
   gen->name = util_Calloc (leng + 1, sizeof (char));
   strncpy (gen->name, name, leng);

   state->S = s;
   gen->GetBits = &LCGWu61b_Bits;
   gen->GetU01  = &LCGWu61b_U01;
   gen->Write   = &WrLCGWu61;
   gen->param   = NULL;
   gen->state   = state;
   return gen;
}


/*=========================================================================*/

void uwu_DeleteGen (unif01_Gen * gen)
{
   if (NULL == gen)
      return;
   gen->name = util_Free (gen->name);
   gen->state = util_Free (gen->state);
   util_Free (gen);
}
