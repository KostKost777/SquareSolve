#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "skipline.h"
#include "double_operations.h"
#include "my_assert.h"

///@file

void solve_square(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));

    if (double_is_same(quadratic->coeff.a, 0))  // a = 0
        solve_line(quadratic);

    else {
        if (double_is_same(quadratic->coeff.c, 0)) {           // c = 0
            quadratic->roots.x1 = max(0.0, -quadratic->coeff.b / quadratic->coeff.a);
            quadratic->roots.x2 = min(0.0, -quadratic->coeff.b / quadratic->coeff.a);
            remove_minus_zero(&quadratic->roots.x1);
            remove_minus_zero(&quadratic->roots.x2);
            quadratic->roots.ans_number_of_x = two_roots;
        }
        else {
            double dis = quadratic->coeff.b * quadratic->coeff.b -
                                4 * quadratic->coeff.a * quadratic->coeff.c;

            if (double_is_same(dis, 0)) {         // dis = 0

                quadratic->roots.x1 = -quadratic->coeff.b / 2 / quadratic->coeff.a;
                quadratic->roots.x2 = -quadratic->coeff.b / 2 / quadratic->coeff.a;
                remove_minus_zero(&quadratic->roots.x1);
                remove_minus_zero(&quadratic->roots.x2);
                quadratic->roots.ans_number_of_x = one_roots;
            }

            else if (comparison_of_double(0, dis)){// dis > 0
                quadratic->roots.ans_number_of_x = zero_roots;
                quadratic->roots.x1 = 0;
                quadratic->roots.x2 = 0;
            }
            else if (comparison_of_double(dis, 0)) {// dis < 0
                double sqrt_dis = sqrt(dis);
                quadratic->roots.x1 = max((-quadratic->coeff.b + sqrt_dis) /
                                                    (2 * quadratic->coeff.a),
                                          (-quadratic->coeff.b - sqrt_dis) /
                                                    (2 * quadratic->coeff.a));

                quadratic->roots.x2 = min((-quadratic->coeff.b + sqrt_dis) /
                                                                (2 * quadratic->coeff.a),
                                          (-quadratic->coeff.b - sqrt_dis) /
                                                                (2 * quadratic->coeff.a));
                remove_minus_zero(&quadratic->roots.x1);
                remove_minus_zero(&quadratic->roots.x2);
                quadratic->roots.ans_number_of_x = two_roots;
            }
        }
    }
}


void solve_line(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));

    if (double_is_same(quadratic->coeff.b, 0) && double_is_same(quadratic->coeff.c, 0)) {
        quadratic->roots.ans_number_of_x = inf_roots; // 0 = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }
    else if (double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0))
    {
        quadratic->roots.ans_number_of_x = zero_roots;  // c = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }
    else if (!double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0))
    {
        quadratic->roots.x1 = -quadratic->coeff.c / quadratic->coeff.b;
        quadratic->roots.x2 = -quadratic->coeff.c / quadratic->coeff.b; // bx + c = 0

        quadratic->roots.ans_number_of_x = one_roots;
        remove_minus_zero(&quadratic->roots.x1);
        remove_minus_zero(&quadratic->roots.x2);
    }
    else {
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;                // bx = 0
        quadratic->roots.ans_number_of_x = one_roots;
    }
}
