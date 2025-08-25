#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "equation_solve.h"
#include "line_operations.h"
#include "double_operations.h"
#include "unit_tests.h"
#include "UI.h"

void check_flags(int argc, char* argv[]);






//*********************************MAIN**************************************

// -h
// ./main -h (--help)
int main(int argc, char* argv[]) // argc argv
{
    check_flags(argc, argv);

    struct Equation quadratic = {};

    get_square_coeff(&quadratic);

    solve_square(&quadratic);

    print_roots(&quadratic);

}

// -f, --file
//  ./main -f file_name
// ./main -f
// please enter file name:
// file_name
// ./main
// ./main 1 2 3
void check_flags(int argc, char* argv[]){
    if(argc > 1){
        for(int i = 1; i < argc; ++i){
            if(!(strcmp(argv[i], "-h")) || !(strcmp(argv[i], "--help")))
                printf("\nПрограмма для решения квадратного уравнения\n\n");

            else if(!(strcmp(argv[i], "-t")) || !(strcmp(argv[i], "--tests"))){
                TestSolveSquare();
                TestSolveLiner();
                TestDoubleIsSame();
            }

        }
    }
}



