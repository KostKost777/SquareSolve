#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "equation_solve.h"
#include "skipline.h"
#include "double_operations.h"
#include "user_interface.h"
#include "my_assert.h"
#include "print_many_stars.h"

static int CheckCorrectInput(double* input);

static int CheckCorrectInput(double* input)
{
    DETAIL_ASSERT(input != NULL);

    int status = scanf("%lf", input);

    if (status == EOF) 
    {
        printf("GG WP");
        return -1;
    }

    int ch = 0;

    if (status && ((ch = getchar()) == '\n')) 
    {
        return 0;
    }

    SkipLine();

    return 1;
}

int GetCoeffFromUser(Equation* quadratic)
{
    DETAIL_ASSERT(quadratic != NULL);

    double a = quadratic->coeff.a;
    double b = quadratic->coeff.b;
    double c = quadratic->coeff.c;

    DETAIL_ASSERT(isfinite(a));
    DETAIL_ASSERT(isfinite(b));
    DETAIL_ASSERT(isfinite(c));

    int  da_ne_bombit_y_menya = 0;
    char arr_char_coeff[NUM_OF_COEFFS] = {'a', 'b', 'c'};
    double* arr_coeff[NUM_OF_COEFFS] = {&a, &b, &c};

    int counter = 0;
    do {
        if (counter == 0)
            printf("I can solve this equation ax^2 + bx + c, input coeffs:\n");

        printf("Input coeff %c: ", arr_char_coeff[counter]);

        da_ne_bombit_y_menya = ISCorrectInput(arr_coeff[counter]);

        if (da_ne_bombit_y_menya == 1) 
        {
            counter = 0;
            continue;
        }

        if (da_ne_bombit_y_menya == -1)
        {
            return 1;
        }

        counter++;

    } while(counter !=  NUM_OF_COEFFS);

    return 0;
}

void PrintRoots(const Equation* quadratic)
{
    DETAIL_ASSERT(quadratic);
    DETAIL_ASSERT(isfinite((int)quadratic->roots.ans_number_of_x));
    DETAIL_ASSERT(isfinite(quadratic->roots.x1));
    DETAIL_ASSERT(isfinite(quadratic->roots.x2));

    PrintLineWithStars();

    switch (quadratic->roots.ans_number_of_x) {
        case inf_roots:
            printf("Infinite rootsn");
            break;

        case zero_roots:
            printf("This equation have 0 roots\n");
            break;

        case one_roots:
            printf("This equation have 1 root: %lg\n", 
                    quadratic->roots.x1);
            break;

        case two_roots:
            printf("This equation have 2 roots: \n"
                   "1) %lg\n2) %lg",
                    quadratic->roots.x1,
                    quadratic->roots.x2);
            break;

        default:
            DETAIL_ASSERT(0 && "Vse ploho");
            break;
     }

     PrintLineWithStars();
}
