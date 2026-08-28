#ifndef EQUATION_SOLVE
#define EQUATION_SOLVE

#define NUM_OF_COEFFS 3

typedef enum
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
} NumOfRoots;

typedef struct
{
    double x1;
    double x2;
    NumOfRoots ans_number_of_x;
} Roots;

typedef struct
{
    double a;
    double b;
    double c;
} Coeffs;

typedef struct
 {
    Roots roots;
    Coeffs coeff;
} Equation;

typedef enum 
{
    SUCCESS,
    ERROR
} ErrorStatus;

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

NumOfRoots ConvertNumOfRootsEnum(int num);

#endif