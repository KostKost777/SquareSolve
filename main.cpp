#include <TXLib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>


/// @file


//********************UnitTests**********************
void TestSolveSquare();
void TestSolveLiner();



const double EPS = 1E-10;

int status_exit = 0;

enum Number_of_roots
{
    inf_roots = -1,
    zero_roots,
    one_roots,
    two_roots
};

//**********************STRUCTS*********************************
struct Ans_SolveSquare
{
    double a;
    double b;
    double c;
    Number_of_roots n_roots;
    double x1;
    double x2;
};
struct Ans_SolveLiner{
    double b;
    double c;
    Number_of_roots n_roots;
    double x1;

};
struct Roots{
    double x1 = 0;
    double x2 = 0;
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

int chek_EOF(int status);

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
    struct Equation quadratic;

    get_square_coeff(&quadratic);

    if (status_exit == 1) {
        printf("GG WP");
        return 0;
    }

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
            quadratic->roots.x1 =  -quadratic->coeff.b / 2 / quadratic->coeff.a;
            remove_minus_zero(&quadratic->roots.x1);
            quadratic->roots.ans_number_of_x = one_roots;
        }

        if (dis < 0)
            quadratic->roots.ans_number_of_x = zero_roots;

        if (dis > 0) {
            double sqrt_dis = sqrt(dis);
            quadratic->roots.x1 = (-quadratic->coeff.b + sqrt_dis) / (2 * quadratic->coeff.a);
            quadratic->roots.x2 = (-quadratic->coeff.b - sqrt_dis) / (2 * quadratic->coeff.a);
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

    if (double_is_same(quadratic->coeff.b, 0) && double_is_same(quadratic->coeff.c, 0))
        quadratic->roots.ans_number_of_x = inf_roots; // 0 = 0

    else if (double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0))
        quadratic->roots.ans_number_of_x = zero_roots;  // c = 0

    else if(!double_is_same(quadratic->coeff.b, 0) && !double_is_same(quadratic->coeff.c, 0)){
        quadratic->roots.x1 = -quadratic->coeff.c / quadratic->coeff.b;

        remove_minus_zero(&quadratic->roots.x1); // bx + c = 0

        quadratic->roots.ans_number_of_x = one_roots;
    }
    else {
        quadratic->roots.x1 = 0;                // bx = 0
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

    int status1 = 0, status2 = 0, status3 = 0;

    do{
        again:
        printf("Введите три действительных коэффицента ax^2 + bx + c через пробел:\n");
        printf("Введите коэффицент а: ");
        status1 = scanf("%lf", &quadratic->coeff.a);
        int da_ne_bombit_y_menya = chek_EOF(status1);
        if(da_ne_bombit_y_menya == -1) {
            break;
        }
        else if (da_ne_bombit_y_menya == 1) {
            goto again;
        }
        printf("Введите коэффицент b: ");
        status2 = scanf("%lf", &quadratic->coeff.b);
        da_ne_bombit_y_menya = chek_EOF(status2);
        if(da_ne_bombit_y_menya == -1)
            break;
        else if (da_ne_bombit_y_menya == 1) goto again;

        printf("Введите коэффицент c: ");
        status3 = scanf("%lf", &quadratic->coeff.c);
        da_ne_bombit_y_menya = chek_EOF(status3);
        if(da_ne_bombit_y_menya == -1)
            break;
        else if (da_ne_bombit_y_menya == 1) goto again;



    }while(!(status1 == 1 && status2 == 1 && status3 == 1));

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
            printf("У этого уравнения два действительных корня: \n1) %lg\n2) %lg",
                                                                quadratic->roots.x1,
                                                                quadratic->roots.x2);
            break;
        default:
            break;
     }
}

void remove_minus_zero(double* num){
    assert(num != NULL);

    if(*num == -0)
        *num = 0;
}

void skip_line(void)
{
    char ch = '\0';
    while ((ch = getchar()) != '\n')
        continue;
}

int chek_EOF(int status)
{
    assert(isfinite(status));
    if (status == -1){
        status_exit = 1;
        return -1;
    }
    char ch = '\0';

    if(status == 1 && (ch = getchar()) == '\n'){
        return 0;
    }
    if (status == 0){
        skip_line();
        return 1;
    }
    skip_line();
    return 1;
}







//***************************************************
//********************UnitTests**********************
//***************************************************

//********************TestSolveSquare****************
void TestSolveSquare()
{                         //      a   b   c     n_r     x1   x2
    Ans_SolveSquare answer[5] = {{1,  4,  4, one_roots, -2,  0},
                                 {1, -5,  6, two_roots,  2,  3},
                                 {1,  0,  0, one_roots,  0,  0},
                                 {0,  0,  0, inf_roots,  0,  0},
                                 {0,  1,  1, one_roots, -1,  0}};
    for (int i = 0; i < 4; ++i){
        Equation quadratic_test;
        quadratic_test.coeff.a = answer[i].a;
        quadratic_test.coeff.b = answer[i].b;
        quadratic_test.coeff.c = answer[i].c;
        solve_square(&quadratic_test);

        if(!(quadratic_test.roots.ans_number_of_x == answer[i].n_roots &&
          double_is_same(min(quadratic_test.roots.x1, quadratic_test.roots.x2),
                         min(answer[i].x1, answer[i].x2)) &&

          double_is_same(max(quadratic_test.roots.x1, quadratic_test.roots.x2),
                         max(answer[i].x1, answer[i].x2))))

         printf("Error a = %lg, b = %lg, c = %lg \nx1 = %lg, x2 = %lg\n Correct: x1_c = %lg, x2_c = %lg\n",
          answer[i].a, answer[i].b, answer[i].c,
          min(quadratic_test.roots.x1, quadratic_test.roots.x2),
          max(quadratic_test.roots.x1, quadratic_test.roots.x2),
          min(answer[i].x1, answer[i].x2),
          max(answer[i].x1, answer[i].x2));

    }

}

//**************************TestSolveLiner***************************

void TestSolveLiner()
{                          //     b   c     n_r     x1
    Ans_SolveLiner answer[5] = { {1,  0, one_roots,  0},
                                 {2,  4, one_roots, -2},
                                 {2,  3, one_roots, -1.5},
                                 {0,  0, inf_roots,  0},
                                 {4,  -12,one_roots, 3}};
    for (int i = 0; i < 4; ++i){
        Equation quadratic_test;
        quadratic_test.coeff.b = answer[i].b;
        quadratic_test.coeff.c = answer[i].c;
        solve_liner(&quadratic_test);

        if(!(quadratic_test.roots.ans_number_of_x == answer[i].n_roots &&
          double_is_same(quadratic_test.roots.x1, answer[i].x1)))

         printf("Error b = %lg, c = %lg \nx1 = %lg \n n_r = %d \n Correct: x1_c = %lg\n",
                answer[i].b, answer[i].c,
                quadratic_test.roots.x1,
                quadratic_test.roots.ans_number_of_x,
                answer[i].x1);

    }
}






