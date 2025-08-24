#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "equastion_solve.h"
#include "UI.h"
#include "checkers.h"
#include "unit_tests.h"


//*********************************MAIN**************************************
int main(void)
{
    TestSolveSquare();
    TestSolveLiner();
    TestDoubleIsSame();

    struct Equation quadratic;

    get_square_coeff(&quadratic);

    solve_square(&quadratic);

    print_roots(&quadratic);

}


