#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "double_operations.h"
#include "my_assert.h"

//mkvfvkmvkfvkmfv

void SolveSquare(Equation* quadratic)
{
    DETAIL_ASSERT(quadratic);

    double a = quadratic->coeff.a;
    double b = quadratic->coeff.b;
    double c = quadratic->coeff.c;

    DETAIL_ASSERT(isfinite(a));
    DETAIL_ASSERT(isfinite(b));
    DETAIL_ASSERT(isfinite(c));


    if (IsDoubleSame(a, 0))   // a = 0
    {
        SolveLine(quadratic);
        return;
    } 

        
    if (IsDoubleSame(c, 0)) // c = 0
    {           
        quadratic->roots.x1 = fmax(0.0, -b / a);
        quadratic->roots.x2 = fmin(0.0, -b / a);

        RemovMinusZero(&quadratic->roots.x1);
        RemovMinusZero(&quadratic->roots.x2);

        quadratic->roots.ans_number_of_x = two_roots;

        return;
    }

    double dis = b * b - 4 * a * c;

    if (IsDoubleSame(dis, 0))  // dis = 0
    {        

        quadratic->roots.x1 = -b / 2 / a;
        quadratic->roots.x2 = -b / 2 / a;

        RemovMinusZero(&quadratic->roots.x1);
        RemovMinusZero(&quadratic->roots.x2);

        quadratic->roots.ans_number_of_x = one_roots;
    }

    else if (IsDoubleBigger(0, dis)) // dis > 0
    {
        quadratic->roots.ans_number_of_x = zero_roots;
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }

    else //dis < 0
    {
        double sqrt_dis = sqrt(dis);

        quadratic->roots.x1 = fmax((-b + sqrt_dis) / (2 * a),
                                  (-b - sqrt_dis) / (2 * a));

        quadratic->roots.x2 = fmin((-b + sqrt_dis) / (2 * a),
                                  (-b - sqrt_dis) / (2 * a));

        RemovMinusZero(&quadratic->roots.x1);
        RemovMinusZero(&quadratic->roots.x2);

        quadratic->roots.ans_number_of_x = two_roots;
    }

}


void SolveLine(Equation* quadratic)
{
    DETAIL_ASSERT(quadratic);

    double b = quadratic->coeff.b;
    double c = quadratic->coeff.c;

    DETAIL_ASSERT(isfinite(b));
    DETAIL_ASSERT(isfinite(c));

    if (IsDoubleSame(b, 0) && IsDoubleSame(c, 0)) 
    {
        quadratic->roots.ans_number_of_x = inf_roots; // 0 = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }

    else if (IsDoubleSame(b, 0) && !IsDoubleSame(c, 0))
    {
        quadratic->roots.ans_number_of_x = zero_roots;  // c = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }

    else if (!IsDoubleSame(b, 0) && !IsDoubleSame(c, 0))
    {
        quadratic->roots.x1 = -c / b;
        quadratic->roots.x2 = -c / b; // bx + c = 0

        quadratic->roots.ans_number_of_x = one_roots;

        RemovMinusZero(&quadratic->roots.x1);
        RemovMinusZero(&quadratic->roots.x2);
    }

    else 
    {
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;                      // bx = 0
        quadratic->roots.ans_number_of_x = one_roots;
    }
}

NumOfRoots ConvertNumOfRootsEnum(int num)
{
    switch(num)
    {
        case inf_roots:
            return inf_roots;

        case zero_roots:
            return zero_roots;

        case one_roots:
            return one_roots;

        case two_roots:
            return two_roots;

        default:
            DETAIL_ASSERT(0 && "Vse ploho");
            return inf_roots;
        }
}

