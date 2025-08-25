#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "line_operations.h"
#include "double_operations.h"
#include "unit_tests.h"

Number_of_roots convert_from_int(int num);

struct Ans_DoubleIsSame{
    double num1;
    double num2;
    bool verdict;
};


Number_of_roots convert_from_int(int num)
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

//********************TestSolveSquare****************

void TestSolveSquare()
{

    FILE *file_test;
    file_test = fopen("TestSolveSquare.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Equation quadratic_test;
        Ans_SolveSquare answer;
        int answer_n_roots = 0;
        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.a, &answer.b, &answer.c,
                                    &answer_n_roots,
                                    &answer.x1,
                                    &answer.x2);
        if(status == -1) break;
        answer.n_roots = convert_from_int(answer_n_roots);
        quadratic_test.coeff.a = answer.a;
        quadratic_test.coeff.b = answer.b;
        quadratic_test.coeff.c = answer.c;
        solve_square(&quadratic_test);

        if (!((quadratic_test.roots.ans_number_of_x == answer.n_roots) &&
          double_is_same(quadratic_test.roots.x2, answer.x2) &&

          double_is_same(quadratic_test.roots.x1, answer.x1))) {

         printf("Error a = %lg, b = %lg, c = %lg \n"
                "\nx1 = %lg, x2 = %lg\n"
                "\nn_r = %d\n"
                " Correct: x1_c = %lg, x2_c = %lg, c_n_r = %d\n",
                  answer.a, answer.b, answer.c,
                  quadratic_test.roots.x1,
                  quadratic_test.roots.x2,
                  quadratic_test.roots.ans_number_of_x,
                  answer.x1,
                  answer.x2,
                  answer.n_roots);
          }

    } while(status != -1);
    fclose(file_test);


}

//**************************TestSolveLiner***************************

void TestSolveLiner()
{
    FILE *file_test;
    file_test = fopen("TestSolveSquare.txt", "r");
    assert(file_test != NULL);
    int status = 0;


    do {
        Equation quadratic_test;
        Ans_SolveSquare answer;
        int answer_n_roots = 0;
        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.a, &answer.b, &answer.c,
                                    &answer_n_roots,
                                    &answer.x1,
                                    &answer.x2);
        if(status == -1) break;

        answer.n_roots = convert_from_int(answer_n_roots);
        if (!double_is_same(answer.a, 0)) continue;

        quadratic_test.coeff.b = answer.b;
        quadratic_test.coeff.c = answer.c;
        solve_liner(&quadratic_test);

        if (!(quadratic_test.roots.ans_number_of_x == answer.n_roots &&
                double_is_same(quadratic_test.roots.x1, answer.x1) &&
                double_is_same(quadratic_test.roots.x2, answer.x2))) {

         printf("Error b = %lg, c = %lg \nx1 = %lg \n n_r = %d \n Correct: x1_c = %lg\n",
                answer.b, answer.c,
                quadratic_test.roots.x1,
                quadratic_test.roots.ans_number_of_x,
                answer.x1);
        }

    } while (status != -1);
    fclose(file_test);
}

//**************************TestDoubleIsSame***************************


void TestDoubleIsSame() {

    FILE *file_test;
    file_test = fopen("TestDoubleIsSame.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Ans_DoubleIsSame answer;
        int verdict_int = 0;
        status = fscanf(file_test, "n1 = %lf n2 = %lf ver = %d\n",
                                    &answer.num1, &answer.num2,
                                    &verdict_int);
        answer.verdict = verdict_int;

        if(!(double_is_same(answer.num1, answer.num2) == answer.verdict)){
            printf("Error num1 = %lg, num2 = %lg, rez = %d\nCorrect: rez_c = %d\n",
                            answer.num1, answer.num2,
                            double_is_same(answer.num1, answer.num2),
                            answer.verdict);
        }
    } while(status != -1);
    fclose(file_test);
}


