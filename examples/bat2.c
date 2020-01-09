/*
 * SPDX-License-Identifier: GPL-3.0-or-later AND LicenseRef-testu01
 * Copyright (c) 2002 Pierre L'Ecuyer, DIRO, Université de Montréal
 * Copyright (c) 2020 Lynn Kirby
 * Code derived from TestU01: http://simul.iro.umontreal.ca/testu01/tu01.html
 */

#include "TestU01/bbattery.h"
#include "TestU01/gdef.h"
#include "TestU01/swrite.h"

int main(void)
{
    swrite_Basic = false;
    bbattery_RabbitFile("vax.bin", 1048576);
    return 0;
}
