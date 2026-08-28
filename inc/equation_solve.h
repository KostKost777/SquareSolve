#ifndef EQUATION_SOLVE
#define EQUATION_SOLVE

#define NUM_OF_COEFFS 3

enum NumOfRoots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};

struct Roots{
    double x1;
    double x2;
    NumOfRoots ans_number_of_x;
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

enum ErrorStatus
{
    SUCCESS,
    ERROR
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
void SolveSquare(Equation* quadratic);

/**
 *
 * @brief Solves a linear equation
* @param b coefficient before x
* @param c constant term
**/

void SolveLine(Equation *quadratic);

NumberOfRoots ConvertNumOfRootsEnum(int num);

#endif