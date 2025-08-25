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

int check_flags(int argc, char* argv[]);
void input_coeff_by_file(char* argv);
bool char_is_num(int num);





//*********************************MAIN**************************************

// -h
// ./main -h (--help)
int main(int argc, char* argv[]) // argc argv
{

    if(!(check_flags(argc, argv))){
        Equation quadratic = {};

        get_square_coeff(&quadratic);

        solve_square(&quadratic);

        print_roots(&quadratic);
    }


}

// -f, --file
//  ./main -f file_name
// ./main -f
// please enter file name:
// file_name
// ./main
// ./main 1 2 3
int check_flags(int argc, char* argv[]){
    if(argc > 1){
        if(argc == 4){
            int a = *argv[1];
            int b = *argv[2];
            int c = *argv[3];
            char* endptr;
            if(char_is_num(a) && char_is_num(b) && char_is_num(c)){
                    Equation quadratic_once;
                    quadratic_once.coeff.a = strtod(argv[1], &endptr);
                    quadratic_once.coeff.b = strtod(argv[2], &endptr);
                    quadratic_once.coeff.c = strtod(argv[3], &endptr);
                    solve_square(&quadratic_once);
                    print_roots(&quadratic_once);
                    return 1;
                }


        }
        else{
            for(int i = 1; i < argc; ++i){
                if(!(strcmp(argv[i], "-h")) || !(strcmp(argv[i], "--help"))){
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


                else if(!(strcmp(argv[i], "-t")) || !(strcmp(argv[i], "--tests"))){
                    TestSolveSquare();
                    TestSolveLiner();
                    TestDoubleIsSame();
                    return 0;
                }
                else if(!(strcmp(argv[i], "-f")) || !(strcmp(argv[i], "--file"))){
                    if(i + 1 > argc - 1){ //проверка выхода за границы массива
                        bool fl = 0;
                        char inp[100];
                        do{
                            printf("Введите файл разрешения .txt:  ");
                            scanf("%s", inp);
                            if(!strstr(inp, ".txt")) continue;
                            else fl = 1;

                        }while(fl != 1);

                        input_coeff_by_file(inp);
                    }else
                        input_coeff_by_file(argv[i + 1]);
                    return 1;
                }

            }
        }
    }
    return 0;
}


void input_coeff_by_file(char* argv){
    assert(argv != NULL);
    FILE *input_file;
    input_file = fopen(argv, "r");
    assert(input_file != NULL);
    int status = 0;

    do {
        Equation quadratic_input;
        Ans_SolveSquare inp;
        status = fscanf(input_file, "a = %lf b = %lf c = %lf\n",
                                    &inp.a, &inp.b, &inp.c);

        if(status == -1) break;

        quadratic_input.coeff.a = inp.a;
        quadratic_input.coeff.b = inp.b;
        quadratic_input.coeff.c = inp.c;
        solve_square(&quadratic_input);
        printf("\n**************************************************\n");
        printf("a = %lg b = %lg c = %lg\n", inp.a, inp.b, inp.c);
        print_roots(&quadratic_input);

    } while (status != -1);
    printf("\n**************************************************\n");
    fclose(input_file);
}

bool char_is_num(int num){
    if((num > 47 && num < 58) || num == 45) return 1;
    return 0;
}


