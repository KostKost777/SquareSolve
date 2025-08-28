#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "unit_tests_solveline.h"
#include "unit_tests_solvesquare.h"
#include "equation_solve.h"
#include "double_operations.h"
#include "my_assert.h"
#include "print_many_stars.h"

NumberOfRoots convert_from_int(int num)
{
    switch(num){
        case -1:
            return inf_roots;
            break;
        case 0:
            return zero_roots;
            break;
        case 1:
            return one_roots;
            break;
        case 2:
            return two_roots;
            break;
        default:
            return inf_roots;
            break;
        }
}

void test_solve_line() {
    FILE *file_test = NULL;
    file_test = fopen("TestSolveSquare.txt", "r");
    assert(file_test != NULL);


    while (true) {
        int status = 0;
        Equation quadratic_test = {};
        Equation answer = {};
        int answer_n_roots = 0;
        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.coeff.a, &answer.coeff.b, &answer.coeff.c,
                                    &answer_n_roots,
                                    &answer.roots.x1,
                                    &answer.roots.x2);
        if (status == -1) break;

        if (!double_is_same(answer.coeff.a, 0)) continue;

        answer.roots.ans_number_of_x = convert_from_int(answer_n_roots);
        quadratic_test.coeff.a = answer.coeff.a;
        quadratic_test.coeff.b = answer.coeff.b;
        quadratic_test.coeff.c = answer.coeff.c;
        solve_square(&quadratic_test);

        if (!(quadratic_test.roots.ans_number_of_x == answer.roots.ans_number_of_x &&
                double_is_same(quadratic_test.roots.x1, answer.roots.x1) &&
                double_is_same(quadratic_test.roots.x2, answer.roots.x2))) {

         printf("Error b = %lg, c = %lg \nx1 = %lg \n n_r = %d \n Correct: x1_c = %lg\n",
                answer.coeff.b, answer.coeff.c,
                quadratic_test.roots.x1,
                quadratic_test.roots.ans_number_of_x,
                answer.roots.x1);
        }

    }
    fclose(file_test);
}



