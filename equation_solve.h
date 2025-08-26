#ifndef equation_solve
#define equation_solve

///@file

enum NumberOfRoots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};




struct Roots {
    double x1;
    double x2;
    NumberOfRoots ans_number_of_x;
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
 * @brief Solves a linear equation
* @param b coefficient before x
* @param c constant term
**/

void solve_line(Equation *quadratic);

#endif
