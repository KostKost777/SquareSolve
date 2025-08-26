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



struct Flags {
    const char* short_flag;
    const char* long_flag;
    void (*func)(const char* argv[], int i, int argc);
};
void initialization_flags(Flags arr_with_flags[]);

int check_flags(int argc, const char* argv[]);

void input_coeff_by_file(const char* argv[], int i, int argc);

void run_from_cli_default(const char* argv[]);

void print_documentation(const char* argv[], int i, int argc);

void all_tests_runner(const char* argv[], int i, int argc);

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
    const int NumberOfFlags = 3;
    Flags arr_with_flags[3];

    initialization_flags(arr_with_flags);

    if (argc > 1) {
        if (argc == 4) {
            run_from_cli_default(argv);
            return 1;
        }
        else {
            // size_t
            for (int i = 1; i < argc; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if ((strcmp(argv[i], arr_with_flags[j].short_flag) == 0)
                        || (strcmp(argv[i], arr_with_flags[j].long_flag) == 0)){
                        arr_with_flags[j].func(argv, i, argc);
                            return 0;
                    }
                }
            }
        }
    }
    return 0;
}


void input_coeff_by_file(const char* argv[], int i, int argc) {
    assert(argv == NULL);

    FILE *input_file = NULL;
    char inp_file_name[260] = "";

    if (i + 1 > argc - 1) { //проверка выхода за границы массива
        do {

            scanf("%260s", inp_file_name);
            input_file = fopen(inp_file_name, "r");
            if (input_file == NULL){
                printf("Введите существующий файл:  \n");
                continue;
            }

            else
                break;

        } while(true);

    } else
        strncpy(inp_file_name, argv[i + 1], 260);

    assert(input_file != NULL);
    int status = 0;

    do {
        Equation quadratic_input;
        status = fscanf(input_file_name, "a = %lf b = %lf c = %lf\n",
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

void all_tests_runner(const char* argv[], int i, int argc){
    test_solve_square();
    test_solve_line();
    test_double_is_same();
}

void print_documentation(const char* argv[], int i, int argc) {
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
}

void initialization_flags(Flags arr_with_flags[]){

    arr_with_flags[0].short_flag = "-h";
    arr_with_flags[0].long_flag = "--help";
    arr_with_flags[0].func = print_documentation;

    arr_with_flags[1].short_flag = "-f";
    arr_with_flags[1].long_flag = "--file";
    arr_with_flags[1].func = input_coeff_by_file;

    arr_with_flags[2].short_flag = "-t";
    arr_with_flags[2].long_flag = "--tests";
    arr_with_flags[2].func = all_tests_runner;
}
