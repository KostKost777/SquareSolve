#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "equation_solve.h"
#include "skipline.h"
#include "double_operations.h"
#include "unit_tests_solvesquare.h"
#include "unit_tests_solveline.h"
#include "unit_tests_doubleissame.h"
#include "console_interface.h"
#include "UI.h"


//*********************************MAIN**************************************

int main(int argc, const char* argv[])
{
    printf("biba\n");

    const int NumberOfFlags = 3;

    Flags arr_with_flags[NumberOfFlags];

    initialization_flags(arr_with_flags);

    if (argc > 1)
        custom_run_with_flags(argc, argv, arr_with_flags, NumberOfFlags);

    else
        run_interactive_default();

    printf("\nboba");
    return 0;
}


