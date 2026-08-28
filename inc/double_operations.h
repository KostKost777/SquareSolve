#ifndef DOUBLE_OPERATIONS
#define DOUBLE_OPERATIONS

///@file


/**
** @brief Permissible error constant
**/
const double EPS = 1E-7;

/**
 *
 * @brief Checks if two variables of type double are equal
* @param num1 first number
* @param num2 second number
**/

bool IsDoubleSame(double num1, double num2);


/**
 *
 * @brief Converts -0 to 0
* @param num number to check
**/

void RemovMinusZero(double* num);

/**
 *
 * @brief Compares two doubles
* @param num1 potentially larger double
* @param num2 potentially less double
**/

bool IsDoubleBigger(double num1, double num2);


#endif
