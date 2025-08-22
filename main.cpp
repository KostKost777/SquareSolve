#include <stdio.h>
#include <math.h>
#include <TXLib.h>
#include <assert.h>

//
//
//

/// @file ....

const double EPS = 1E-10;
enum Number_of_roots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};
/**
    @brief Function to skip characters
**/
void skip_chars(void)
{
    char ch = 0;
    while ((ch = getchar()) != '\n')
        continue;
}

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
Number_of_roots solve_square(double a, double b, double c, double* x1, double* x2);

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

Number_of_roots solve_liner(double b, double c, double* x1);

/**
 *
 * @brief Takes as input the coefficients of a quadratic equation
* @param a coefficient before x^2
* @param b coefficient before x
* @param c constant term
**/


void get_square_coeff(double* a, double* b, double* c);

/**
 *
 * @brief Output number of roots
* @param ans_number_of_x number of roots
* @param x1 first root
* @param x2 second root

**/


void print_roots(int ans_number_of_x, double x1, double x2);

/**
 *
 * @brief Converts -0 to 0
* @param num number to check
**/

void remove_minus_zero(double* num);


int main(void)
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    get_square_coeff(&a, &b, &c);

    Number_of_roots ans_number_of_x = solve_square(a, b, c, &x1, &x2);

    print_roots(ans_number_of_x, x1, x2);


}

Number_of_roots solve_square(double a, double b, double c,
                             double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    if (double_is_same(a, 0))
        return solve_liner(b, c, x1);

    double dis = b * b - 4 * a * c;

    if (double_is_same(dis, 0)) {
        *x1 =  -b / 2 / a;
        remove_minus_zero(x1);
        return one_roots;
    }

    if (dis < 0)
        return zero_roots;

    if (dis > 0) {
        double sqrt_dis = sqrt(dis);
        *x1 = (- b + sqrt_dis) / (2 * a);
        *x2 = (- b - sqrt_dis) / (2 * a);
        remove_minus_zero(x1);
        remove_minus_zero(x2);
        return two_roots;
    }
}

Number_of_roots solve_liner(double b, double c,
                            double* x1)
{
    assert(x1 != NULL);

    assert(isfinite(b) && isfinite(c));

    if(double_is_same(b, 0) && double_is_same(c, 0))
        return inf_roots; // 0 = 0

    if(double_is_same(b, 0) && !double_is_same(c, 0))
        return zero_roots;  // c = 0

    *x1 = -c / b;

    remove_minus_zero(x1); // bx + c = 0

    return one_roots;
}

bool double_is_same(double num1, double num2)
{
    assert(isfinite(num1));
    assert(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

void get_square_coeff(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    int status = 0;
    printf("Введите три действительных коэффицента ax^2 + bx + c через пробел:\n");
    status = scanf("%lf %lf %lf", a, b, c);
    while (status != 3)
    {

        printf("Введите действительные числа, такие как 0, 1.545, -1.2E12:\n");
        status = scanf("%lf %lf %lf", a, b, c);
    }

}


void print_roots(int ans_number_of_x,
                 double x1, double x2)
{
    assert(isfinite(ans_number_of_x));
    assert(isfinite(x1));
    assert(isfinite(x2));

    switch(ans_number_of_x){
        case inf_roots:
            printf("Количество корней бесконечно\n");
            break;

        case zero_roots:
            printf("У этого уравнения нет действительных корней\n");
            break;

        case one_roots:
            printf("У этого уравнения один действительный корень: %g\n", x1);
            break;

        case two_roots:
            printf("У этого уравнения два действительных корня: \n1) %g\n2) %g", x1, x2);
            break;
     }
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if(*num == -0)
        *num = 0;
}







