#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "equation_solve.h"
#include "line_operations.h"
#include "double_operations.h"
#include "unit_tests.h"
#include "UI.h"

int check_flags(int argc, const char* argv[]);
void input_coeff_by_file(const char* argv[], int i, int argc);
bool char_is_num(int num);
void run_from_cli_default(const char* argv[]);

///@file



//*********************************MAIN**************************************

// -h
// ./main -h (--help)


int main(int argc, const char* argv[]) // argc argv
{
    printf("biba\n");
    if (!(check_flags(argc, argv))) {
        Equation quadratic = {};

        get_square_coeff(&quadratic);

        solve_square(&quadratic);

        print_roots(&quadratic);
    }
    printf("\nboba");
}

// -f, --file
//  ./main -f file_name
// ./main -f
// please enter file name:
// file_name
// ./main
// ./main 1 2 3
// sabc123
// 123dsfjhsdjhk
// 123\0
// if (*endptr != '\0')


int check_flags(int argc, const char* argv[]) {
    // for loop: if (strcmp(name, flag_name)) {do_flag();}
    if (argc > 1) {
        if (argc == 4) {
            run_from_cli_default(argv);
            return 1;

        }
        else {
            for (int i = 1; i < argc; ++i) {
                if (!(strcmp(argv[i], "-h")) || !(strcmp(argv[i], "--help"))) {
                    printf("\n\n\n******************************************\n"
                           "Программа для решения квадратного уравнения.\n"
                           "Дополнительные флаги запуска:\n"
                           "-h (--help): информация о программе.\n"
                           "-t (--tests): запуск с тестами.\n"
                           "-f (--file) file_name.txt: поиск корней по коэффицентам из файла.\n"
                           "Также сразу после .exe файла можно ввести три\n"
                           "последовательных действительных числа и программа выдаст их корни.\n"
                           "Для обычного запуска введите .exe файл.\n"
                           "******************************************\n\n\n");
                    return 1;
                }
                else if (!(strcmp(argv[i], "-t")) || !(strcmp(argv[i], "--tests"))) {
                    test_solve_square();
                    test_solve_line();
                    test_double_is_same();
                    return 0;
                }
                else if (!(strcmp(argv[i], "-f")) || !(strcmp(argv[i], "--file"))) {
                    // argv, argc, i
                    input_coeff_by_file(argv, i, argc);
                    return 1;
                }
            }
        }
    }
    return 0;
}


void input_coeff_by_file(const char* argv[], int i, int argc) {
    assert(argv != NULL);
    assert(isfinite(i));
    assert(isfinite(argc));

    FILE *input_file = NULL;
    char inp_file_name[260] = "";
    printf("Вы забыли ввести имя файла\n");

    if (i + 1 > argc - 1) { //проверка выхода за границы массива
        do {
            printf("Введите существующий файл:  ");
            scanf("%260s", inp_file_name);
            input_file = fopen(inp_file_name, "r");
            if (input_file == NULL)
                continue;
            else
                break;

        } while(true);

    } else
        strncpy(inp_file_name, argv[i + 1], 260);

    assert(input_file != NULL);
    int status = 0;

    do {
        Equation quadratic_input;
        status = fscanf(input_file, "a = %lf b = %lf c = %lf\n",
                                    &quadratic_input.coeff.a,
                                    &quadratic_input.coeff.b,
                                    &quadratic_input.coeff.c);
        if (status == -1)
            break;

        solve_square(&quadratic_input);
        printf("\n**************************************************\n");
        printf("a = %lg b = %lg c = %lg\n",
                quadratic_input.coeff.a,
                quadratic_input.coeff.b,
                quadratic_input.coeff.c);

        print_roots(&quadratic_input);

    } while (true);
    printf("\n**************************************************\n");
    fclose(input_file);
}

void run_from_cli_default(const char* argv[]) {
    Equation quadratic_once;

    char* endptr_a = NULL;
    char* endptr_b = NULL;
    char* endptr_c = NULL;
    quadratic_once.coeff.a = strtod(argv[1], &endptr_a);
    quadratic_once.coeff.b = strtod(argv[2], &endptr_b);
    quadratic_once.coeff.c = strtod(argv[3], &endptr_c);

    if ((*endptr_a == '\0') &&
        (*endptr_b == '\0') &&
        (*endptr_c == '\0')) {
            solve_square(&quadratic_once);
            print_roots(&quadratic_once);
        }
    else
        printf("Не корректный ввод, читай -h(--help)\n");

}


