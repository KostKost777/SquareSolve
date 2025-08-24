#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "equastion_solve.h"
#include "UI.h"
#include "checkers.h"
#include "unit_tests.h"




void get_square_coeff(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));


    bool da_ne_bombit_y_menya;
    char arr_char_coeff[3] = {'a', 'b', 'c'};
    double* arr_coeff[3] = {&quadratic->coeff.a, &quadratic->coeff.b, &quadratic->coeff.c};

    int counter = 0;
    do {
        if(counter == 0)
            printf("������� ��� �������������� ����������� ax^2 + bx + c ����� ������:\n");

        printf("������� ���������� %c: ", arr_char_coeff[counter]);

        da_ne_bombit_y_menya = chek_correct_input(arr_coeff[counter]);


        if (da_ne_bombit_y_menya){
            counter = 0;
            continue;
        }
        counter++;


    }while(counter !=  3);

}


void print_roots(const Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite((int)quadratic->roots.ans_number_of_x));
    assert(isfinite(quadratic->roots.x1));
    assert(isfinite(quadratic->roots.x2));

    switch(quadratic->roots.ans_number_of_x){
        case inf_roots:
            printf("���������� ������ ����������\n");
            break;

        case zero_roots:
            printf("� ����� ��������� ��� �������������� ������\n");
            break;

        case one_roots:
            printf("� ����� ��������� ���� �������������� ������: %lg\n", quadratic->roots.x1);
            break;

        case two_roots:
            printf("� ����� ��������� ��� �������������� �����: \n"
                   "1) %lg\n2) %lg",
                                                                quadratic->roots.x1,
                                                                quadratic->roots.x2);
            break;
        default:
            break;
     }
}
