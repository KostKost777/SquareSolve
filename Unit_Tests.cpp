#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "line_operations.h"
#include "double_operations.h"
#include "unit_tests.h"

///@file
NumberOfRoots convert_from_int(int num);


struct TestSuiteDoubleIsSame {
    double num1;
    double num2;
    bool verdict;
};


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

//********************test_solve_square****************

void test_solve_square()
{

    FILE *file_test;
    file_test = fopen("test_solve_square.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Equation quadratic_test;
        Equation answer;
        int answer_n_roots = 0;
        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.coeff.a, &answer.coeff.b, &answer.coeff.c,
                                    &answer_n_roots,
                                    &answer.roots.x1,
                                    &answer.roots.x2);
        if(status == -1) break;

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

    } while(true);
    fclose(file_test);
}

//**************************test_solve_line***************************

void test_solve_line()
{
    FILE *file_test;
    file_test = fopen("test_solve_square.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Equation quadratic_test;
        Equation answer;
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

    } while (true);
    fclose(file_test);
}

//**************************test_double_is_same***************************


void test_double_is_same() {

    FILE *file_test;
    file_test = fopen("test_double_is_same.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        TestSuiteDoubleIsSame answer;
        int verdict_int = 0;
        status = fscanf(file_test, "n1 = %lf n2 = %lf ver = %d\n",
                                    &answer.num1, &answer.num2,
                                    &verdict_int);
        if (status == -1) break;
        answer.verdict = verdict_int;

        if (!(double_is_same(answer.num1, answer.num2) == answer.verdict)) {
            printf("Error num1 = %lg, num2 = %lg, rez = %d\nCorrect: rez_c = %d\n",
                            answer.num1, answer.num2,
                            double_is_same(answer.num1, answer.num2),
                            answer.verdict);
        }
    } while(true);
    fclose(file_test);
}


