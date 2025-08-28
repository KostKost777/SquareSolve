#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "unit_tests_solvesquare.h"
#include "equation_solve.h"
#include "double_operations.h"
#include "my_assert.h"
#include "print_many_stars.h"

void test_solve_square()
{

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

        answer.roots.ans_number_of_x = convert_from_int(answer_n_roots);
        quadratic_test = answer;

        solve_square(&quadratic_test);

        if (!((quadratic_test.roots.ans_number_of_x == answer.roots.ans_number_of_x) &&
          double_is_same(quadratic_test.roots.x2, answer.roots.x2) &&

          double_is_same(quadratic_test.roots.x1, answer.roots.x1))) {

         printf("Error a = %lg, b = %lg, c = %lg \n"
                "\nx1 = %lg, x2 = %lg\n"
                "\nn_r = %d\n"
                " Correct: x1_c = %lg, x2_c = %lg, c_n_r = %d\n",
                  answer.coeff.a, answer.coeff.b, answer.coeff.c,
                  quadratic_test.roots.x1,
                  quadratic_test.roots.x2,
                  quadratic_test.roots.ans_number_of_x,
                  answer.roots.x1,
                  answer.roots.x2,
                  answer.roots.ans_number_of_x);
          }

    }
    fclose(file_test);
}

