#ifndef UI
#define UI

#define NUM_OF_FLAGS 3

/// @file
/**
 *
 * @brief Takes as input the coefficients of a quadratic equation
* @param a coefficient before x^2
* @param b coefficient before x
* @param c constant term
**/


int GetCoeffFromUser(Equation* quadratic);

/**
 *
 * @brief Output number of roots
* @param ans_number_of_x number of roots
* @param x1 first root
* @param x2 second root

**/


void PrintRoots(const Equation* quadratic);

#endif
