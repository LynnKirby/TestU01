/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/gdef.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/utsname.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gdef_GetHostName (char machine[], int n)
{
   if (n <= 0 || machine == NULL)
      return;
   machine[0] = '\0';

#ifdef _WIN32
   char buf[MAX_COMPUTERNAME_LENGTH + 1];
   DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
   GetComputerNameA (buf, &size);
	snprintf (machine, n, "%s, Windows", buf);
#else
   struct utsname Z;

   if (uname(&Z) != -1) {
      snprintf(machine, n, "%s, %s", Z.nodename, Z.sysname);
   }
#endif
}


/*------------------------------------------------------------------------*/
#define MAXBYTES 255

void gdef_WriteHostName (void)
{
   char machine[1 + MAXBYTES] = {'\0'};
   gdef_GetHostName (machine, MAXBYTES);
   printf ("%s\n", machine);
}
