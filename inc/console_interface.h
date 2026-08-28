#ifndef CONSOLE_INTERFACE
#define CONSOLE_INTERFACE

#include "equation_solve.h"

#define MAX_SIZE_FILE_NAME 256
#define NUM_OF_FLAGS       3

enum FlagType
{
    HELP_FLAG,
    TEST_TEST,
    RUN_FROM_FILE_FLAG
};

///@file

/**
    @brief Function for normal launch from console
**/

int RunInretactiveDefault(void);

ErrorStatus CustomRunWithFlags(const int argc, const char const* argv[]);

void RunAllTest(const char const * argv[], const int arg_pos, 
                const int argc, Flags flags_arr[]);

#endif

