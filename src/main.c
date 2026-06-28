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
    const char* H_DOC = "-h (--help):               посмотреть документацию по флагам.\n";
    const char* F_DOC = "-t (--tests):              запустить тесты.\n";
    const char* T_DOC = "-f (--file) file_name.txt: запустить программу из файла.\n";

    struct Flags arr_with_flags[] = {{"-h", "--help",  H_DOC, print_documentation},
                                     {"-f", "--help",  F_DOC, input_coeff_by_file, },
                                     {"-t", "--tests", T_DOC, all_tests_runner}};

    if (argc > 1)
    {
        if (custom_run_with_flags(argc, argv, arr_with_flags))
            return EXIT_SUCCESS;
    }

    else 
    {
        if (run_interactive_default())
            return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}


