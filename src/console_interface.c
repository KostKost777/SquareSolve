#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "equation_solve.h"
#include "double_operations.h"
#include "unit_tests_solvesquare.h"
#include "unit_tests_solveline.h"
#include "unit_tests_doubleissame.h"
#include "console_interface.h"
#include "user_interface.h"
#include "my_assert.h"
#include "print_many_stars.h"

static int IsHelpFlag(const int argc, const char* argv[], struct Flags flags_arr[]);

static FILE* get_exist_filename(char inp_file_name[]);

void InputFromFile(const char* argv[], const int argc, struct Flags flags_arr[]) 
{
    (void)flags_arr;

    assert(argv != NULL);

    FILE* input_file = NULL;
    const int MAX_SIZE_FILE_NAME = 260;
    char inp_file_name[MAX_SIZE_FILE_NAME] = "";

    if (pos + 1 > argc - 1)  //˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
        input_file = get_exist_filename(inp_file_name);

     else {
        strncpy(inp_file_name, argv[pos + 1], MAX_SIZE_FILE_NAME);
        input_file = get_exist_filename(inp_file_name);
    }

    assert(input_file != NULL);
    int status = 0;

    while (true) {
        Equation quadratic_input = {};
        status = fscanf(input_file, "a = %lf b = %lf c = %lf\n",
                                    &quadratic_input.coeff.a,
                                    &quadratic_input.coeff.b,
                                    &quadratic_input.coeff.c);
        if (status == -1)
            break;

        solve_square(&quadratic_input);
        print_stars_func();
        printf("a = %lg b = %lg c = %lg\n",
                quadratic_input.coeff.a,
                quadratic_input.coeff.b,
                quadratic_input.coeff.c);

        print_roots(&quadratic_input);
    }
    print_stars_func();
    fclose(input_file);
}

void run_from_cli_default(const char* argv[]) {
    assert(argv != NULL);
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
        printf("˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜, ˜˜˜˜˜ -h(--help)\n");

}

void all_tests_runner(const char* argv[], const int pos, const int argc,
                      Flags flags_arr[], const int NumberOfFlags){
    (void)argv;
    (void)pos;
    (void)argc;
    (void)flags_arr;
    (void)NumberOfFlags;

    int tests_failed = 0;
    tests_failed += test_solve_square();
    tests_failed += test_solve_line();
    tests_failed += test_double_is_same();
    printf("%d ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜\n", tests_failed);
}

void PrintFlagsDocumentation(const char* argv[], const int argc, struct Flags flags_arr[]) {
    (void)argv;
    (void)argc;
    print_stars_func();

    for(int i = 0; i < NUM_OF_FLAGS; ++i){
        printf("%s\n", flags_arr[i].info);
    }

    printf("˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜\n");
    print_stars_func();

}

int run_interactive_default() {
    Equation quadratic = {};
    int status_EOF = 0;

    status_EOF = get_square_coeff(&quadratic);
    if (status_EOF)
        return 1;

    solve_square(&quadratic);
    print_roots(&quadratic);

    return 0;
}

int CustomRunWithFlags(const int argc, const char* argv[], struct Flags flags_arr[]) 
{

    const int DefaultInputNumbers = 4;

    if(IsUserUseHelpFlag(argc, argv, flags_arr))
        return 1;

    if (argc == DefaultInputNumbers){
            run_from_cli_default(argv);
            return 0;
    }
    for (int pos = 1; pos < argc; ++pos) {
        for (int fl_pos = 0; fl_pos < NumberOfFlags; fl_pos++) {
            if ((strcmp(argv[pos], flags_arr[fl_pos].short_flag) == 0) ||
                (strcmp(argv[pos], flags_arr[fl_pos].long_flag)  == 0)){
                flags_arr[fl_pos].func(argv, pos, argc,
                                            flags_arr, NumberOfFlags);
            }
        }
    }
    return 0;
}

static bool IsUserUseHelpFlag(const int argc, const char* argv[], struct Flags flags_arr[])
{
    DETAIL_ASSERT(flags_arr);
    DETAIL_ASSERT(argv);

    for (int i = 1; i < argc; ++i) 
    {
        if (IsHelpFlag(argv[i]))
        {
            flags_arr[HELP_FLAG].func(argv, argc, flags_arr);
            return true;
        }
    }
    return false;
}

static bool IsHelpFlag(const char* flag_name)
{
    return strcmp(flag_name, "-h") == 0 || strcmp(flag_name, "--help") == 0;
}

static FILE* get_exist_filename(char inp_file_name[]){
    assert(inp_file_name != NULL);
    FILE* input_file = fopen(inp_file_name, "r");
    while(input_file == NULL){
        printf("˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜:  ");
        scanf("%260s", inp_file_name);
        input_file = fopen(inp_file_name, "r");
    }
    return input_file;
}
