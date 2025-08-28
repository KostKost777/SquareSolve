#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>


#include "skipline.h"
#include "equation_solve.h"

/// @file
void skip_line(void)
{
    int ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}







