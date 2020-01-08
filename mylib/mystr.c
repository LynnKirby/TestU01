/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "util.h"
#include "mystr.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


void mystr_Delete (char S[], unsigned int index, unsigned int len)
{
   int i;
   unsigned int length = strlen (S);
   if (index + len > length)
      S[index] = '\0';
   else
      for (i = index; (unsigned int) i <= length - len; ++i)
         S[i] = S[i + len];
}


void mystr_Insert (char Res[], char Source[], unsigned int Pos)
{
   int i;
   unsigned int ResLength = strlen (Res);
   unsigned int SourceLength = strlen (Source);
   if (Pos > ResLength)
      util_Error ("mystr_Insert : Index out of array bound.");
   for (i = ResLength; (unsigned) i >= Pos; --i) {
      Res[i + SourceLength] = Res[i]; /* end of Res */
   }
   for (i = Pos; (unsigned) i < Pos + SourceLength; ++i)
      Res[i] = Source[i - Pos];      /* adding Source to Res */
}


void mystr_ItemS (char R[], char S[], const char T[], unsigned int N)
{
   unsigned int i;
   char *temp;
   temp = strtok (S, T);             /* first time */
   for (i = 1; i <= N; ++i) {        /* 2nd to Nth time */
      if (temp == NULL)
         break;
      temp = strtok (NULL, T);
   }
   if (temp == NULL) {
      strncpy (R, "\0", (size_t) 1);
      return;
   }
   strcpy (R, temp);                 /* assignation */
}


static int mystr_Rmatch (char s[], unsigned int i, char p[], unsigned int j)
{
   int matched;
   unsigned int k;
   unsigned int s_len = strlen (s);
   unsigned int p_len = strlen (p);
   if (p[0] == 0)
      return 1;
   for (;;) {
      if ((i > s_len - 1 || s[i] == 0) && (j > p_len - 1 || p[j] == 0))
         return 1;
      if (j > p_len - 1 || p[j] == 0)
         return 0;
      if (p[j] == '*') {
         k = i;
         if (j == p_len - 1 || p[j + 1] == 0)
            return 1;
         else {
            for (;;) {
               matched = mystr_Rmatch (s, k, p, j + 1);
               if ((matched || k > s_len - 1) || s[k] == 0)
                  return matched;
               ++k;
            }
         }
      }
      if ((p[j] == '?' && s[i]) || (toupper (p[j]) == toupper (s[i]))) {
         ++i;
         ++j;
      } else
         return 0;
   }
   return 0;
}


int mystr_Match (char Source[], char Pattern[])
/*
   returns true if the string in Source matches the string in Pattern
   The pattern may contain any number of the wild characters '*' and '?'
   '?' matches any single character
   '*' matches any sequence of charcters (including a zero length sequence)
   EG '*m?t*i*' will match 'Automatic'
 */
{
   return mystr_Rmatch (Source, 0, Pattern, 0);
}


void mystr_Slice (char R[], char S[], unsigned int P, unsigned int L)
{
   unsigned int i;
   if (P + L > strlen (S))
      util_Error ("*** ERROR : mystr_Slice Pattern longer then Source");
   for (i = 0; i < L; i++) {
      R[i] = S[i + P];
   }
   if (L <= strlen (R) - 1)
      R[L] = 0;
}


void mystr_Subst (char source[], char OldPattern[], char NewPattern[])
{
   unsigned int len;
   unsigned int index;
   char *PatternFound;
   PatternFound = strstr (source, OldPattern);
   if (PatternFound != NULL) {
      len = strlen (OldPattern);
      index = PatternFound - source;
      mystr_Delete (source, index, len);
      mystr_Insert (source, NewPattern, index);
   }
}


void mystr_Position (char Substring[], char Source[], unsigned int at,
                     unsigned int *pos, int *found)
{
   char *result = strstr (Source + at, Substring);
   if (at > strlen (Source))
      util_Error ("mystr_Position : Index out of array bound.");
   if (result != NULL) {
      *pos = result - Source;
      *found = 1;
   } else
      *found = 0;
}
