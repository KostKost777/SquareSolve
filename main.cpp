#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "line_operations.h"
#include "double_operations.h"
#include "unit_tests.h"
#include "UI.h"






//*********************************MAIN**************************************

int main(void)
{
    TestSolveSquare();
    TestSolveLiner();
    TestDoubleIsSame();

    struct Equation quadratic = {};

    get_square_coeff(&quadratic);

    solve_square(&quadratic);

    print_roots(&quadratic);

}


