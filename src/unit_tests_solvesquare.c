#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "unit_tests_solvesquare.h"
#include "equation_solve.h"
#include "double_operations.h"
#include "my_assert.h"
#include "print_many_stars.h"

int TestSolveSquare()
{

    FILE *file_test = NULL;

    file_test = fopen("TestSolveSquare.txt", "r");
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

        answer.roots.ans_number_of_x = convert_from_int(answer_n_roots);
        quadratic_test = answer;

        SolveSquare(&quadratic_test);

        if (!((quadratic_test.roots.ans_number_of_x == answer.roots.ans_number_of_x) 
               && IsDoubleSame(quadratic_test.roots.x2, answer.roots.x2) 
               && IsDoubleSame(quadratic_test.roots.x1, answer.roots.x1))) 
        {

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

            tests_failed++;
        }

    }

    fclose(file_test);
    
    return tests_failed;
}

