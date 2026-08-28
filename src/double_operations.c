#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "double_operations.h"
#include "equation_solve.h"
#include "my_assert.h"

bool IsDoubleSame(double num1, double num2)
{
    DETAIL_ASSERT(isfinite(num1));
    DETAIL_ASSERT(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

/**
** @brief Permissible error constant
**/

bool IsDoubleBigger(double num1, double num2)
{
    DETAIL_ASSERT(isfinite(num1));
    DETAIL_ASSERT(isfinite(num2));

    return (num1 - num2) > EPS;
}

void RemovMinusZero(double* num)
{
    DETAIL_ASSERT(num);

    if (IsDoubleSame(*num, -0))
        *num = 0;
}

