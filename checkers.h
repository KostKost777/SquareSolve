const double EPS = 1E-10;
/// @file

/**
 *
 * @brief Checks if two variables of type double are equal
* @param num1 first number
* @param num2 second number
**/

bool double_is_same(double num1, double num2);
/**

    @brief Function to skip characters
**/
void skip_line(void);

/**
 *
 * @brief Converts -0 to 0
* @param num number to check
**/

void remove_minus_zero(double* num);


/**

    @brief End of file check function
**/

bool chek_correct_input(double* input);



