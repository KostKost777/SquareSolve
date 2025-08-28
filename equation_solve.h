#ifndef equation_solve
#define equation_solve

///@file





/**
 * @brief Enum for easy entry of roots
* @param inf_roots constant for an infinite number of roots
* @param zero_roots constant to denote one solution
* @param one_roots constant to denote two solution
* @param two_roots constant to denote three solution
**/

enum NumberOfRoots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};

/**
 * @brief Structure for convenient storage of roots of an equation
* @param x1 first root of equation
* @param x2 second root of equation
* @param ans_number_of_x number of roots of the equation
**/

struct Roots {
    double x1;
    double x2;
    NumberOfRoots ans_number_of_x;
};

/**
* @brief Structure for convenient storage of coefficients of a quadratic equation
* @param a coefficient before x^2
* @param b coefficient before x
* @param c free coefficient
**/

struct Coeffs {
    double a;
    double b;
    double c;
};

/**
* @brief Structure of structure equations
* @param Roots - root structure
* @param Coeffs - structure of co-officers
**/

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
