#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "equastion_solve.h"
#include "checkers.h"


bool double_is_same(double num1, double num2)
{
    assert(isfinite(num1));
    assert(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if(double_is_same(*num, -0))
        *num = 0;
}

void skip_line(void)
{
    char ch = '\0';
    while ((ch = getchar()) != '\n')
        continue;
}


bool chek_correct_input(double* input)
{
    assert(input != NULL);

    int status = scanf("%lf", input);


    if (status == -1) {
        printf("GG WP");
        exit(0);
    }

    char ch = '\0';

    if ( status && ((ch = getchar()) == '\n')) {
        return false;
    }

    skip_line();
    return true;
}
