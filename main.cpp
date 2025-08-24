#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>


/// @file


//********************UnitTests**********************
void TestSolveSquare();
void TestSolveLiner();
void TestDoubleIsSame();



const double EPS = 1E-10;



enum Number_of_roots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};

//**********************STRUCTS*********************************

struct Ans_DoubleIsSame{
    double num1;
    double num2;
    bool verdict;
};


struct Ans_SolveSquare
{
    double a;
    double b;
    double c;
    Number_of_roots n_roots;
    double x1;
    double x2;
};


struct Roots{
    double x1;
    double x2;
    Number_of_roots ans_number_of_x;
};

struct Coeffs {
    double a;
    double b;
    double c;
};

struct Equation {
    Roots roots;
    Coeffs coeff;
};

//**********************STRUCTS*********************************

/**

    @brief End of file check function
**/

bool chek_correct_input(double* input);

/**

    @brief Function to skip characters
**/
void skip_line(void);


/**
 *
 * @brief Solves quadratic equation
* @param a coefficient of x^2
* @param b coefficient of x
* @param c constant term
* @param x1 first root
* @param x2 second root
 *
**/
void solve_square(Equation* quadratic);

/**
 *
 * @brief Checks if two variables of type double are equal
* @param num1 first number
* @param num2 second number
**/

bool double_is_same(double num1, double num2);

/**
 *
 * @brief Solves a linear equation
* @param b coefficient before x
* @param c constant term
**/

void solve_liner(Equation *quadratic);

/**
 *
 * @brief Takes as input the coefficients of a quadratic equation
* @param a coefficient before x^2
* @param b coefficient before x
* @param c constant term
**/


void get_square_coeff(Equation* quadratic);

/**
 *
 * @brief Output number of roots
* @param ans_number_of_x number of roots
* @param x1 first root
* @param x2 second root

**/


void print_roots(const Equation* quadratic);

/**
 *
 * @brief Converts -0 to 0
* @param num number to check
**/

void remove_minus_zero(double* num);

//*********************************MAIN**************************************
int main(void)
{
    TestSolveSquare();
    TestSolveLiner();
    TestDoubleIsSame();
    struct Equation quadratic;

    get_square_coeff(&quadratic);


    solve_square(&quadratic);

    print_roots(&quadratic);

}
//***************************************************************************

void solve_square(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));




    if (double_is_same(quadratic->coeff.a, 0))
        solve_liner(quadratic);
    else{

        double dis = quadratic->coeff.b * quadratic->coeff.b -
                            4 * quadratic->coeff.a * quadratic->coeff.c;

        if (double_is_same(dis, 0)) {

            quadratic->roots.x1 = -quadratic->coeff.b / 2 / quadratic->coeff.a;
            quadratic->roots.x2 = -quadratic->coeff.b / 2 / quadratic->coeff.a;
            //printf("\n--%lg\n", quadratic->roots.x2);
            remove_minus_zero(&quadratic->roots.x1);
            remove_minus_zero(&quadratic->roots.x2);
            quadratic->roots.ans_number_of_x = one_roots;
        }

        else if (dis < 0){
            quadratic->roots.ans_number_of_x = zero_roots;
            quadratic->roots.x1 = 0;
            quadratic->roots.x2 = 0;
        }
        else if (dis > 0) {
            double sqrt_dis = sqrt(dis);
            quadratic->roots.x1 = max((-quadratic->coeff.b + sqrt_dis) / (2 * quadratic->coeff.a),
                                      (-quadratic->coeff.b - sqrt_dis) / (2 * quadratic->coeff.a));

            quadratic->roots.x2 = min((-quadratic->coeff.b + sqrt_dis) / (2 * quadratic->coeff.a),
                                      (-quadratic->coeff.b - sqrt_dis) / (2 * quadratic->coeff.a));
            remove_minus_zero(&quadratic->roots.x1);
            remove_minus_zero(&quadratic->roots.x2);
            quadratic->roots.ans_number_of_x = two_roots;
        }
    }
}

void solve_liner(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));

    if (double_is_same(quadratic->coeff.b, 0) && double_is_same(quadratic->coeff.c, 0)){
        quadratic->roots.ans_number_of_x = inf_roots; // 0 = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }
    else if (double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0)){
        quadratic->roots.ans_number_of_x = zero_roots;  // c = 0
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;
    }
    else if(!double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0)){
        quadratic->roots.x1 = -quadratic->coeff.c / quadratic->coeff.b;
        quadratic->roots.x2 = -quadratic->coeff.c / quadratic->coeff.b; // bx + c = 0

        quadratic->roots.ans_number_of_x = one_roots;
        remove_minus_zero(&quadratic->roots.x1);
        remove_minus_zero(&quadratic->roots.x2);
    }
    else {
        quadratic->roots.x1 = 0;
        quadratic->roots.x2 = 0;                // bx = 0
        quadratic->roots.ans_number_of_x = one_roots;
    }

}

bool double_is_same(double num1, double num2)
{
    assert(isfinite(num1));
    assert(isfinite(num2));

    return fabs(num1 - num2) < EPS;
}

void get_square_coeff(Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->coeff.a));
    assert(isfinite(quadratic->coeff.b));
    assert(isfinite(quadratic->coeff.c));


    bool da_ne_bombit_y_menya;
    char arr_char_coeff[3] = {'a', 'b', 'c'};
    double* arr_coeff[3] = {&quadratic->coeff.a, &quadratic->coeff.b, &quadratic->coeff.c};

    int counter = 0;
    do {
        if(counter == 0)
            printf("Введите три действительных коэффицента ax^2 + bx + c через пробел:\n");

        printf("Введите коэффицент %c: ", arr_char_coeff[counter]);

        da_ne_bombit_y_menya = chek_correct_input(arr_coeff[counter]);


        if (da_ne_bombit_y_menya){
            counter = 0;
            continue;
        }
        counter++;


    }while(counter !=  3);

}


void print_roots(const Equation* quadratic)
{
    assert(quadratic != NULL);
    assert(isfinite(quadratic->roots.ans_number_of_x));
    assert(isfinite(quadratic->roots.x1));
    assert(isfinite(quadratic->roots.x2));

    switch(quadratic->roots.ans_number_of_x){
        case inf_roots:
            printf("Количество корней бесконечно\n");
            break;

        case zero_roots:
            printf("У этого уравнения нет действительных корней\n");
            break;

        case one_roots:
            printf("У этого уравнения один действительный корень: %lg\n", quadratic->roots.x1);
            break;

        case two_roots:
            printf("У этого уравнения два действительных корня: \n"
                   "1) %lg\n2) %lg",
                                                                quadratic->roots.x1,
                                                                quadratic->roots.x2);
            break;
        default:
            break;
     }
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if(double_is_same(*num, -0))
        *num = 0;
}

void skip_line(void)
{
    char ch = '\0';
    while ((ch = getchar()) != '\n')
        continue;
}

bool chek_correct_input(double* input)
{
    assert(input != NULL);

    int status = scanf("%lf", input);


    if (status == -1) {
        printf("GG WP");
        exit(0);
    }

    char ch = '\0';

    if ( status && ((ch = getchar()) == '\n')) {
        return false;
    }

    skip_line();
    return true;
}







//***************************************************
//********************UnitTests**********************
//***************************************************

//********************TestSolveSquare****************

void TestSolveSquare()
{

    FILE *file_test;
    file_test = fopen("TestSolveSquare.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Equation quadratic_test;
        Ans_SolveSquare answer;

        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
        &answer.a, &answer.b, &answer.c,
        &answer.n_roots,
        &answer.x1,
        &answer.x2);

        quadratic_test.coeff.a = answer.a;
        quadratic_test.coeff.b = answer.b;
        quadratic_test.coeff.c = answer.c;
        solve_square(&quadratic_test);

        if (!((quadratic_test.roots.ans_number_of_x == answer.n_roots) &&
          double_is_same(quadratic_test.roots.x2, answer.x2) &&

          double_is_same(quadratic_test.roots.x1, answer.x1))) {

         printf("Error a = %lg, b = %lg, c = %lg \n"
                "\nx1 = %lg, x2 = %lg\n"
                "\nn_r = %d\n"
                " Correct: x1_c = %lg, x2_c = %lg, c_n_r = %d\n",
                  answer.a, answer.b, answer.c,
                  quadratic_test.roots.x1,
                  quadratic_test.roots.x2,
                  quadratic_test.roots.ans_number_of_x,
                  answer.x1,
                  answer.x2,
                  answer.n_roots);
          }

    } while(status != -1);
    fclose(file_test);

}

//**************************TestSolveLiner***************************

void TestSolveLiner()
{
    FILE *file_test;
    file_test = fopen("TestSolveSquare.txt", "r");
    assert(file_test != NULL);
    int status = 0;


    do {
        Equation quadratic_test;
        Ans_SolveSquare answer;

        status = fscanf(file_test, "a: %lf b: %lf c: %lf n_r: %d x1 = %lf x2 = %lf\n",
                                    &answer.a, &answer.b, &answer.c,
                                    &answer.n_roots,
                                    &answer.x1,
                                    &answer.x2);
        if (!double_is_same(answer.a, 0)) continue;

        quadratic_test.coeff.b = answer.b;
        quadratic_test.coeff.c = answer.c;
        solve_liner(&quadratic_test);

        if (!(quadratic_test.roots.ans_number_of_x == answer.n_roots &&
                double_is_same(quadratic_test.roots.x1, answer.x1) &&
                double_is_same(quadratic_test.roots.x2, answer.x2))) {

         printf("Error b = %lg, c = %lg \nx1 = %lg \n n_r = %d \n Correct: x1_c = %lg\n",
                answer.b, answer.c,
                quadratic_test.roots.x1,
                quadratic_test.roots.ans_number_of_x,
                answer.x1);
        }

    } while (status != -1);
    fclose(file_test);
}

void TestDoubleIsSame() {

    FILE *file_test;
    file_test = fopen("TestDoubleIsSame.txt", "r");
    assert(file_test != NULL);
    int status = 0;

    do {
        Ans_DoubleIsSame answer;

        status = fscanf(file_test, "n1 = %lf n2 = %lf ver = %d\n",
                                    &answer.num1, &answer.num2,
                                    &answer.verdict);

        if(!(double_is_same(answer.num1, answer.num2) == answer.verdict)){
            printf("Error num1 = %lg, num2 = %lg, rez = %d\nCorrect: rez_c = %d\n",
                            answer.num1, answer.num2,
                            double_is_same(answer.num1, answer.num2),
                            answer.verdict);
        }
    } while(status != -1);
    fclose(file_test);
}

