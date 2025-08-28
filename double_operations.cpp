#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "double_operations.h"
#include "equation_solve.h"
#include "my_assert.h"

// __func__
// __PRETTY_FUNCTION__
//
//
//

// assert(condition, return 1);
                                          \

//
// functional_assert(condition, code)

///@file

/**
** @brief Permissible error constant
**/
const double EPS = 1E-7;

bool double_is_same(double num1, double num2)
{
    assert(isfinite(num1));
    assert(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if (double_is_same(*num, -0))
        *num = 0;
}

