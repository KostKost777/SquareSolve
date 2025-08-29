#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// -I
// src/...
// include/...
// test/...


#include "equation_solve.h"
#include "skipline.h"
#include "double_operations.h"
#include "unit_tests_solvesquare.h"
#include "unit_tests_solveline.h"
#include "unit_tests_doubleissame.h"
#include "console_interface.h"
#include "UI.h"
#include "my_assert.h"
#include "print_many_stars.h"

//*********************************MAIN**************************************

int main(const int argc, const char* argv[])
{
    printf("biba\n");

    const int NumberOfFlags = 3;

    const char* h_doc = "-h (--help): информация о программе.\n";
    const char* f_doc = "-t (--tests): запуск с тестами.\n";
    const char* t_doc = "-f (--file) file_name.txt: поиск корней по коэффицентам из файла.\n";

    Flags arr_with_flags[NumberOfFlags] = {{"-h", "--help", print_documentation, h_doc},
                                           {"-f", "--help", input_coeff_by_file, f_doc},
                                           {"-t", "--tests", all_tests_runner, t_doc}};


    if (argc > 1){
        int status_exit = 0;
        status_exit = custom_run_with_flags(argc, argv, arr_with_flags, NumberOfFlags);
        if(status_exit)
            return 0;
    }
    else {
        int status_EOF = 0;
        status_EOF = run_interactive_default();
        if (status_EOF)
            return 0;
    }

    printf("boba");
    return 0;
}


