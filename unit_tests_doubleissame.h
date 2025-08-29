#ifndef unit_tests_doubleissame
#define unit_tests_doubleissame
///@file

/**
**    @brief Function for testing double_is_same function
**/

int test_double_is_same(void);

/**
    @brief Structure for testing double using unit tests
    @param num1 first double number
    @param num2 second double number
    @param verdict correct test result
**/

struct TestSuiteDoubleIsSame {
    double num1;
    double num2;
    bool verdict;
};

#endif
