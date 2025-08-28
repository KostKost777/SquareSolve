#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#include "double_operations.h"
#include "unit_tests_doubleissame.h"
#include "my_assert.h"
#include "print_many_stars.h"


void test_double_is_same() {

    FILE *file_test = NULL;
    file_test = fopen("TestDoubleIsSame.txt", "r");
    assert(file_test != NULL);
    while (true) {
    int status = 0;
        TestSuiteDoubleIsSame answer = {};
        int verdict_int = 0;
        status = fscanf(file_test, "n1 = %lf n2 = %lf ver = %d\n",
                                    &answer.num1, &answer.num2,
                                    &verdict_int);
        if (status == -1) break;
        answer.verdict = verdict_int;

        if (!(double_is_same(answer.num1, answer.num2) == answer.verdict)) {
            printf("Error num1 = %lg, num2 = %lg, rez = %d\nCorrect: rez_c = %d\n",
                            answer.num1, answer.num2,
                            double_is_same(answer.num1, answer.num2),
                            answer.verdict);
        }
    }
    fclose(file_test);
}


