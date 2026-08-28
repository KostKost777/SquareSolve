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

int TestSolveLine() 
{
    FILE *file_test = NULL;

    file_test = fopen("unit_tests/TestSolveSquare.txt", "r");
    DETAIL_ASSERT(file_test != NULL);

    int tests_failed = 0;

    while (true) 
    {
        int status = 0;
        int answer_n_roots = 0;

        Equation quadratic_test = {};
        Equation answer = {};

        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.coeff.a, &answer.coeff.b, &answer.coeff.c,
                                    &answer_n_roots,
                                    &answer.roots.x1,
                                    &answer.roots.x2);
        if (status == EOF) break;

        if (!IsDoubleSame(answer.coeff.a, 0)) continue;

        answer.roots.ans_number_of_x = ConvertNumOfRootsEnum(answer_n_roots);

        quadratic_test.coeff.a = answer.coeff.a;
        quadratic_test.coeff.b = answer.coeff.b;
        quadratic_test.coeff.c = answer.coeff.c;

        SolveSquare(&quadratic_test);

        if (!(quadratic_test.roots.ans_number_of_x == answer.roots.ans_number_of_x &&
                IsDoubleSame(quadratic_test.roots.x1, answer.roots.x1) &&
                IsDoubleSame(quadratic_test.roots.x2, answer.roots.x2))) 
        {
             printf("Error b = %lg, c = %lg \nx1 = %lg \n n_r = %d \n Correct: x1_c = %lg\n",
                                                        answer.coeff.b, answer.coeff.c,
                                                        quadratic_test.roots.x1,
                                                        quadratic_test.roots.ans_number_of_x,
                                                        answer.roots.x1);

            tests_failed++;

        }

    }

    fclose(file_test);

    return tests_failed;
}



