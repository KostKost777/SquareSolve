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
#include "user_interface.h"
#include "my_assert.h"
#include "print_many_stars.h"

int main(const int argc, const char* argv[])
{
    if (argc > 1)
    {
        if (CustomRunWithFlags(argc, argv))
            return EXIT_SUCCESS;
    }


    if (RunInretactiveDefault())
        return EXIT_SUCCESS;

    return EXIT_FAILURE;
}


