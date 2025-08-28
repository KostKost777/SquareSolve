#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "equation_solve.h"
#include "double_operations.h"
#include "unit_tests_solvesquare.h"
#include "unit_tests_solveline.h"
#include "unit_tests_doubleissame.h"
#include "console_interface.h"
#include "UI.h"

void input_coeff_by_file(const char* argv[], int pos, int argc) {

    assert(argv != NULL);

    FILE *input_file = NULL;
    const int MAX_SIZE_FILE_NAME = 260;
    char inp_file_name[MAX_SIZE_FILE_NAME] = "";

    if (pos + 1 > argc - 1) { //проверка выхода за границы массива
        printf("Введите имя файла:  ");
        while(true){

            scanf("%260s", inp_file_name);
            input_file = fopen(inp_file_name, "r");
            if (input_file == NULL){
                printf("Введите существующий файл:  ");
                continue;
            }

            else
                break;
        }

    } else{
        strncpy(inp_file_name, argv[pos + 1], MAX_SIZE_FILE_NAME);
        input_file = fopen(inp_file_name, "r");
        if(input_file == NULL){
            while(input_file == NULL){
                printf("Введите существующий файл:");
                scanf("%260s", inp_file_name);
                input_file = fopen(inp_file_name, "r");
            }
        }
    }

    assert(input_file != NULL);
    int status = 0;

    while(true){
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

    }
    printf("\n**************************************************\n");
    fclose(input_file);
}
// file, line, func, assert(condition)
// #define
// __FILE__, __LINE__, __func__

void run_from_cli_default(const char* argv[]) {
    Equation quadratic_once = {};

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

void all_tests_runner(const char* argv[], int pos, int argc){
    (void)argv;
    (void)pos;
    (void)argc;

    test_solve_square();
    test_solve_line();
    test_double_is_same();
}

void print_documentation(const char* argv[], int pos, int argc) {
    (void)argv;
    (void)pos;
    (void)argc;

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

void run_interactive_default() {
    Equation quadratic = {};

    get_square_coeff(&quadratic);

    solve_square(&quadratic);

    print_roots(&quadratic);

}

void custom_run_with_flags(int argc, const char* argv[],
                                Flags arr_with_flags[], const int NumberOfFlags) {

    for (int h_i = 0; h_i < argc; ++h_i) { //проверка наличия флага -h, высший приоритет
        if((strcmp(argv[h_i], "-h") == 0 ||
            strcmp(argv[h_i], "--help") == 0) && (h_i != 0)){
            arr_with_flags[0].func(argv, 0, argc);
            exit(0);
        }
    }

    if (argc == 4) {
            run_from_cli_default(argv);
    }

    else {
        for (int pos = 1; pos < argc; ++pos) {
            for (int fl_pos = 0; fl_pos < NumberOfFlags; ++fl_pos) {
                if ((strcmp(argv[pos], arr_with_flags[fl_pos].short_flag) == 0) ||
                    (strcmp(argv[pos], arr_with_flags[fl_pos].long_flag)  == 0))
                    arr_with_flags[fl_pos].func(argv, pos, argc);
            }
        }
    }
}

void initialization_flags(Flags arr_with_flags[]){
    /**arr_with_flags = {{"-h", "--help", print_documentation},
                      {"-f", "--help", input_coeff_by_file},
                      {"-t", "--tests", all_tests_runner}}
    **/

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
