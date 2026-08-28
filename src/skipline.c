#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "skipline.h"

void SkipLine(void)
{
    int ch = 0;

    while ((ch = getchar()) != '\n')
        continue;
}







