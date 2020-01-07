/*************************************************************************\
 *
 * Package:        MyLib
 * File:           gdef.c
 * Environment:    ANSI C
 *
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal.
 * e-mail: lecuyer@iro.umontreal.ca
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted without a fee for private, research,
 * academic, or other non-commercial purposes.
 * Any use of this software in a commercial environment requires a
 * written licence from the copyright owner.
 *
 * Any changes made to this package must be clearly identified as such.
 *
 * In scientific publications which used this software, a reference to it
 * would be appreciated.
 *
 * Redistributions of source code must retain this copyright notice
 * and the following disclaimer.
 *
 * THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
\*************************************************************************/

#include "gdef.h"

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
   strncat (machine, buf, n);
#else
   struct utsname Z;

   if (uname(&Z) != -1) {
      strncpy (machine, Z.nodename, (size_t) n);
      int j = strlen (machine);
      if (n - j > 2)
         strncat (machine, ", ", (size_t) 2);
      j = strlen (machine);
      if (n - j > 0)
         strncat (machine, Z.sysname, (size_t) (n - j));
      machine[n - 1] = '\0';  
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
