#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


/// @file

const double EPS = 1E-10;

enum Number_of_roots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};

struct Roots{
    double x1;
    double x2;
    Number_of_roots ans_number_of_x;
};

struct Coeffs {
    double a;
    double b;
    double c;
};

struct Equation {
    Roots roots;
    Coeffs coeff;
};

/**

    @brief Function to skip characters
**/
void skip_line(void);


/**
 *
 * @brief Solves quadratic equation
* @param a coefficient of x^2
* @param b coefficient of x
* @param c constant term
* @param x1 first root
* @param x2 second root
 *
**/
void solve_square(Equation* quadratic);

/**
 *
 * @brief Checks if two variables of type double are equal
* @param num1 first number
* @param num2 second number
**/

bool double_is_same(double num1, double num2);

/**
 *
 * @brief Solves a linear equation
* @param b coefficient before x
* @param c constant term
**/

void solve_liner(Equation *quadratic);

/**
 *
 * @brief Takes as input the coefficients of a quadratic equation
* @param a coefficient before x^2
* @param b coefficient before x
* @param c constant term
**/


void get_square_coeff(Equation* quadratic);

/**
 *
 * @brief Output number of roots
* @param ans_number_of_x number of roots
* @param x1 first root
* @param x2 second root

**/


void print_roots(const Equation* quadratic);

/**
 *
 * @brief Converts -0 to 0
* @param num number to check
**/

void remove_minus_zero(double* num);

//*********************************MAIN**************************************
int main(void)
{
    struct Equation quadratic;

    get_square_coeff(&quadratic);

    solve_square(&quadratic);

    print_roots(&quadratic);

}
//***********************************************************************

void solve_square(Equation* quadratic)
{
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));
    assert(&quadratic->roots.x1 != NULL);
    assert(&quadratic->roots.x2 != NULL);


    if (double_is_same(quadratic->coeff.a, 0))
        solve_liner(quadratic);

    double dis = quadratic->coeff.b * quadratic->coeff.b -
                        4 * quadratic->coeff.a * quadratic->coeff.c;

    if (double_is_same(dis, 0)) {
        quadratic->roots.x1 =  -quadratic->coeff.b / 2 / quadratic->coeff.a;
        remove_minus_zero(&quadratic->roots.x1);
        quadratic->roots.ans_number_of_x = one_roots;
    }

    if (dis < 0)
        quadratic->roots.ans_number_of_x = zero_roots;

    if (dis > 0) {
        double sqrt_dis = sqrt(dis);
        quadratic->roots.x1 = (-quadratic->coeff.b + sqrt_dis) / (2 * quadratic->coeff.a);
        quadratic->roots.x2 = (-quadratic->coeff.b - sqrt_dis) / (2 * quadratic->coeff.a);
        remove_minus_zero(&quadratic->roots.x1);
        remove_minus_zero(&quadratic->roots.x2);
        quadratic->roots.ans_number_of_x = two_roots;
    }
}

void solve_liner(Equation* quadratic)
{
    assert(&quadratic->roots.x1 != NULL);

    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));

    if (double_is_same(quadratic->coeff.b, 0) && double_is_same(quadratic->coeff.c, 0))
        quadratic->roots.ans_number_of_x = inf_roots; // 0 = 0

    if (double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0))
        quadratic->roots.ans_number_of_x = zero_roots;  // c = 0
    else {
        quadratic->roots.x1 = -quadratic->coeff.c / quadratic->coeff.b;

        remove_minus_zero(&quadratic->roots.x1); // bx + c = 0

        quadratic->roots.ans_number_of_x = one_roots;
    }
}

bool double_is_same(double num1, double num2)
{
    assert(isfinite(num1));
    assert(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

void get_square_coeff(Equation* quadratic)
{
    assert(&quadratic->coeff.a != NULL);
    assert(&quadratic->coeff.b != NULL);
    assert(&quadratic->coeff.c != NULL);

    int status = 0;
    printf("Введите три действительных коэффицента ax^2 + bx + c через пробел:\n");
    status = scanf("%lf %lf %lf", &quadratic->coeff.a,
                                  &quadratic->coeff.b,
                                  &quadratic->coeff.c);

    while (status != 3)
    {
        printf("Введите действительные числа, такие как 0, 1.545, -1.2E12:\n");
        skip_line();
        status = scanf("%lf %lf %lf", &quadratic->coeff.a,
                                      &quadratic->coeff.b,
                                      &quadratic->coeff.c);
    }

}


void print_roots(const Equation* quadratic)
{
    assert(isfinite(quadratic->roots.ans_number_of_x));
    assert(isfinite(quadratic->roots.x1));
    assert(isfinite(quadratic->roots.x2));

    switch(quadratic->roots.ans_number_of_x){
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
            printf("У этого уравнения два действительных корня: \n1) %lg\n2) %lg",
                                                                quadratic->roots.x1,
                                                                quadratic->roots.x2);
            break;
     }
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if(*num == -0)
        *num = 0;
}

void skip_line(void)
{
    char ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}
