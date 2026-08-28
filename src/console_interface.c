///@file

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

#define STR(to_string) #to_string

/**
    @brief Structure for console startup flags
    @param short_flag just short version of the flag
    @param long_flag just long version of the flag
    @param func pointer to flag function
**/

struct Flags 
{
    const char* short_name;
    const char* long_name;
    const char* info;

    void (*func)(const char* argv[], const int argc, struct Flags arr_with_flags[]);
};

static void InputCoeffFromFile(const char const * argv[], const int argc, 
                        const int arg_pos, Flags flags_arr[]);

static bool IsFileNameInArgs(const int arg_pos, const int argc);

static void RunWithCoeffFromConsole(const char* argv[]);

static void PrintFlagsDocumentation(const char* argv[], const int argc, 
                                    const int arg_pos, Flags flags_arr[]);

static bool IsGetCoeffFromConsole (int argc, const char const * argv[], Flags flags_arr[]);

static bool IsHelpFlag(const char* flag_name);

static FILE* GetFilePtrFromArgs(char inp_file_name[]);

void InputCoeffFromFile(const char const * argv[], const int argc, 
                        const int arg_pos, Flags flags_arr[]) 
{
    DETAIL_ASSERT(argv);
    DETAIL_ASSERT(flags_arr);

    (void)flags_arr;

    FILE* input_file = NULL;

    char file_name[MAX_SIZE_FILE_NAME] = {};

    if (IsFileNameInArgs(arg_pos, argc))
        input_file = GetFilePtrByName(file_name);

    else 
    {
        strncpy(file_name, argv[arg_pos + 1], MAX_SIZE_FILE_NAME);
        input_file = GetFilePtrByName(file_name);
    }

    DETAIL_ASSERT(input_file);

    int status = 0;

    while (true) 
    {
        Equation quadratic = {};

        status = fscanf(input_file, "a = %lf b = %lf c = %lf\n",
                                    &quadratic.coeff.a,
                                    &quadratic.coeff.b,
                                    &quadratic.coeff.c);
        if (status == EOF) break;

        SolveSquare(&quadratic);

        PrintLineWithStars();

        printf("a = %lg b = %lg c = %lg\n",
                quadratic.coeff.a,
                quadratic.coeff.b,
                quadratic.coeff.c);

        PrintRoots(&quadratic);
    }

    PrintLineWithStars();
    fclose(input_file);
}

bool IsFileNameInArgs(const int arg_pos, const int argc)
{
    return (arg_pos + 1 > argc - 1) ? true : false; 
}

static void RunWithCoeffFromConsole(const char* argv[]) 
{
    DETAIL_ASSERT(argv);

    Equation quadratic = {};

    char* endptr_a = NULL;
    char* endptr_b = NULL;
    char* endptr_c = NULL;

    quadratic.coeff.a = strtod(argv[1], &endptr_a);
    quadratic.coeff.b = strtod(argv[2], &endptr_b);
    quadratic.coeff.c = strtod(argv[3], &endptr_c);

    if ((*endptr_a == '\0') &&
        (*endptr_b == '\0') &&
        (*endptr_c == '\0')) 
    {
        SolveSquare(&quadratic);
        PrintRoots(&quadratic);
    }

    else
        printf("Error run with coeffs, use -h(--help)\n");

}

void RunAllTest(const char const * argv[], const int arg_pos, 
                const int argc, Flags flags_arr[]){
    (void)argv;
    (void)arg_pos;
    (void)argc;
    (void)flags_arr;

    int tests_failed = 0;

    tests_failed += TestSolveSquare();
    tests_failed += TestSolveLine();
    tests_failed += TestDoubleIsSame();

    printf("%d tests faild\n", tests_failed);
}

static void PrintFlagsDocumentation(const char* argv[], const int argc, 
                                    const int arg_pos, Flags flags_arr[]) 
{
    (void)argv;
    (void)argc;
    (void)arg_pos;

    PrintLineWithStars();

    for(int i = 0; i < NUM_OF_FLAGS; ++i)
    {
        printf("%s\n", flags_arr[i].info);
    }

    PrintLineWithStars();
}

int RunInretactiveDefault() 
{
    Equation quadratic = {};
    int status_EOF = 0;

    status_EOF = get_square_coeff(&quadratic);
    if (status_EOF)
        return 1;

    SolveSquare(&quadratic);
    PrintRoots(&quadratic);

    return 0;
}

static bool IsGetCoeffFromConsole (int argc, const char const * argv[], Flags flags_arr[])
{
    if (argc != 4) return false;
    
    for (int i = 0; i < NUM_OF_FLAGS; ++i)
    {
        if ((strcmp(argv[arg_pos], flags_arr[fl_pos].short_flag) == 0) ||
            (strcmp(argv[arg_pos], flags_arr[fl_pos].long_flag)  == 0))
        {
            return false;
        }
    }

    return true;
}

ErrorStatus CustomRunWithFlags(const int argc, const char const* argv[]) 
{
    DETAIL_ASSERT(argv);

    const char* H_DOC = "-h (--help):               посмотреть документацию по флагам.\n";
    const char* F_DOC = "-t (--tests):              запустить тесты.                  \n";
    const char* T_DOC = "-f (--file) file_name.txt: запустить программу из файла.     \n";

    Flags flags_arr[] = 
    { 
        { "-h", "--help",       H_DOC, PrintFlagsDocumentation  },
        { "-f", "--from_file",  F_DOC, InputCoeffFromFile       },
        { "-t", "--tests",      T_DOC, RunAllTest               }
    };

    if (IsGetCoeffFromConsole(argc, argv, flags_arr))
    {
        RunWithCoeffFromConsole(argv);
        return SUCCESS;
    }

    for (int arg_pos = 1; arg_pos < argc; arg_pos++) 
    {
        for (int fl_pos = 0; fl_pos < NUM_OF_FLAGS; fl_pos++) 
        {
            if ((strcmp(argv[arg_pos], flags_arr[fl_pos].short_flag) == 0) ||
                (strcmp(argv[arg_pos], flags_arr[fl_pos].long_flag)  == 0)){
                flags_arr[fl_pos].func(argv, argc, arg_pos, flags_arr);
            }
        }
    }
    return 0;
}

static bool IsHelpFlag(const char* flag_name)
{
    return strcmp(flag_name, "-h") == 0 || strcmp(flag_name, "--help") == 0;
}

static FILE* GetFilePtrFromArgs(char inp_file_name[])
{
    DETAIL_ASSERT(inp_file_name != NULL);
    FILE* input_file = fopen(inp_file_name, "r");

    while(input_file == NULL)
    {
        printf("Input exist file name:  ");
        scanf("%" STR(MAX_SIZE_FILE_NAME) "s", inp_file_name);

        input_file = fopen(inp_file_name, "r");
    }

    return input_file;
}
