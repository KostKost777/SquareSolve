#ifndef console_interface
#define console_interface

///@file


/**
    @brief Structure for console startup flags
    @param short_flag just short version of the flag
    @param long_flag just long version of the flag
    @param func pointer to flag function
**/

struct Flags {
    const char* short_flag;
    const char* long_flag;
    void (*func)(const char* argv[], int pos, int argc);
};

/**
    @brief Function to initialize all startup flags
    @param arr_with_flags array of Flags structures
**/

void initialization_flags(Flags arr_with_flags[]);

/**
    @brief Function for console input from file
    @param arr_with_flags array of Flags structures
**/

void input_coeff_by_file(const char* argv[], int pos, int argc);

/**
    @brief Function for normal launch from console
    @param arr_with_flags array of Flags structures
**/

void run_from_cli_default(const char* argv[]);

/**
    @brief Function for outputting documentation on flags
**/

void print_documentation(const char* argv[], int pos, int argc);

/**
    @brief Function to run all tests
**/

void all_tests_runner(const char* argv[], int pos, int argc);

/**
    @brief Function for normal launch from console
**/

void run_interactive_default(void);

/**
    @brief Function for custom input with flags from console
    @param argc number of flags entered
    @param argv array of flag names
    @param arr_with_flags array of structure containing all flag definitions
    @param NumberOfFlags constant containing the number of defined flags
**/

void custom_run_with_flags(int argc, const char* argv[],
                            Flags arr_with_flags[], const int NumberOfFlags);

#endif

