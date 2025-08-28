#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "skipline.h"
#include "double_operations.h"
#include "UI.h"
#include "my_assert.h"
#include "print_many_stars.h"

///@file


/**
    @brief End of file check function
**/


static int chek_correct_input(double* input);


int chek_correct_input(double* input)
{
    assert(input != NULL);

    int status = scanf("%lf", input);


    if (status == -1) {
        printf("GG WP");
        return -1;
    }

    int ch = 0;

    if (status && ((ch = getchar()) == '\n')) {
        return 0;
    }

    skip_line();
    return 1;
}

int get_square_coeff(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));

    const int NumberOfCoeffs = 3;

    int  da_ne_bombit_y_menya = 0;
    char arr_char_coeff[NumberOfCoeffs] = {'a', 'b', 'c'};
    double* arr_coeff[NumberOfCoeffs] = {&quadratic->coeff.a, &quadratic->coeff.b, &quadratic->coeff.c};

    int counter = 0;
    do {
        if (counter == 0)
            printf("Введите три действительных коэффицента ax^2 + bx + c через пробел:\n");

        printf("Введите коэффицент %c: ", arr_char_coeff[counter]);

        da_ne_bombit_y_menya = chek_correct_input(arr_coeff[counter]);


        if (da_ne_bombit_y_menya == 1) {
            counter = 0;
            continue;
        }

        if (da_ne_bombit_y_menya == -1) return 1;
        counter++;


    } while(counter !=  NumberOfCoeffs);
    return 0;
}

void print_roots(const Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite((int)quadratic->roots.ans_number_of_x));
    assert(isfinite(quadratic->roots.x1));
    assert(isfinite(quadratic->roots.x2));
    print_stars_func();
    switch (quadratic->roots.ans_number_of_x) {
        case inf_roots:
            printf("Количество корней бесконечно\n");
            break;

        case zero_roots:
            printf("У этого уравнения нет действительных корней\n");
            break;

        case one_roots:
            printf("У этого уравнения один действительный корень: %lg\n", quadratic->roots.x1);
            break;

        case two_roots:
            printf("У этого уравнения два действительных корня: \n"
                   "1) %lg\n2) %lg",
                                                                quadratic->roots.x1,
                                                                quadratic->roots.x2);
            break;

        default:
            break;
     }
     print_stars_func();
}
