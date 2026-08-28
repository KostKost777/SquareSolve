#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "double_operations.h"
#include "unit_tests_doubleissame.h"
#include "my_assert.h"
#include "print_many_stars.h"

/**
    @brief Structure for testing double using unit tests
    @param num1 first double number
    @param num2 second double number
    @param verdict correct test result
**/

struct TestSuiteDoubleIsSame 
{
    double num1;
    double num2;
    bool verdict;
};

int TestDoubleIsSame() 
{
    FILE *file_test = NULL;

    file_test = fopen("TestDoubleIsSame.txt", "r");
    DETAIL_ASSERT(file_test != NULL);
    
    int tests_failed = 0;

    while (true) 
    {
        int status      = 0;
        int verdict_int = 0;

        TestSuiteDoubleIsSame answer = {};

        status = fscanf(file_test, "n1 = %lf n2 = %lf ver = %d\n",
                                    &answer.num1, &answer.num2,
                                    &verdict_int);

        if (status == EOF) break;

        answer.verdict = verdict_int;

        if (!(IsDoubleSame(answer.num1, answer.num2) == answer.verdict)) 
        {
            printf("Error num1 = %lg, num2 = %lg, rez = %d\nCorrect: rez_c = %d\n",
                                            answer.num1, answer.num2,
                                            IsDoubleSame(answer.num1, answer.num2),
                                            answer.verdict);
            tests_failed++;
        }
    }

    fclose(file_test);

    return tests_failed;
}


