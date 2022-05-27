#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


typedef double afunc(double);


const char parameter_delimiter[2] = ":";  // Разделяющий значения входных параметров символ
unsigned iterations_amount;  // Счетчик для подсчета итераций при нахождении корней
bool should_find_iterations_amount = false;  // флаг, который устанавливается если нужно посчитать количество итераций при поиске корней

double f1(double x)
{
    return log(x);
}


double f2(double x)
{
    return -2 * x + 14;
}


double f3(double x)
{
    return 1 / (2 - x) + 6;
}


double f1_derivative(double x)
{
    return 1 / x;
}


double f2_derivative(double x)
{
    return -2;
}


double f3_derivative(double x)
{
    return 1 / (x*x - 4*x + 4);
}


double root(afunc *f,
            afunc *g,
            double a,
            double b,
            double eps1,
            afunc *f_derivative,
            afunc *g_derivative)
{
    double x_current_point;
    bool is_start_approximation_right_or_not;

    // Выбрали за начальное приближение правый конец (точку (b, F(b)))
    is_start_approximation_right_or_not = !((((*f)(a) - (*g)(a)) < 0) ^
                                            (((*f)((a + b) / 2) - (*g)((a + b) / 2)) < ((((*f)(a) - (*g)(a)) + ((*f)(b) - (*g)(b))) / 2)));
    /*
            Знаки выражений << или >> означают одинаковые знаки для первой и второй производной
            различные знаки означают различные знаки производных
    */

    if (is_start_approximation_right_or_not)
        x_current_point = b;
    else
        x_current_point = a;

    while ( fabs(((*f)(x_current_point) - (*g)(x_current_point)) / ((*f_derivative)(x_current_point) - (*g_derivative)(x_current_point))) >= eps1 )
    {
        x_current_point -= (((*f)(x_current_point) - (*g)(x_current_point)) / ((*f_derivative)(x_current_point) - (*g_derivative)(x_current_point)));
        iterations_amount++;
    }

    return x_current_point;
}


double integral(afunc *f, double a, double b, double eps2)
{
    double p_runge = 1.0 / 3;
    long n = 1;
    double h = (b - a) / n;

    double calculated_integral;
    double new_calculated_integral = (*f)(a + 0.5 * h) * h;

    do
    {
        n *= 2;
        calculated_integral = new_calculated_integral;
        new_calculated_integral = 0;
        h = (b - a) / n;
        for (int i = 0; i < n; ++i)
        {
            new_calculated_integral += (*f)(a + (i + 0.5) * h);
        }
        new_calculated_integral *= h;
    }
    while ((p_runge * fabs(calculated_integral - new_calculated_integral)) >= eps2);

    return new_calculated_integral;
}


char possible_options[] = "--help и -h, которые выводят на печать все допустимые ключи командной строки.\n\n"
                          "--root и -r, которые печатают абсциссы точек пересечения кривых.\n\n"
                          "--iterations и -i, которые печатают число итераций, потребовавшихся на приближенное решение уравнений при поиске точек пересечения.\n\n"
                          "--test-root и -R, которые позволяют протестировать функцию root. Фактические параметры вызова root задаются единственным параметром этой опции в виде F1:F2:A:B:E:R, где F1, F2 — номера используемых функций, A, B, E — значения параметров a, b, eps1 функции root, R — правильный ответ (вычисленный аналитически). Программа должна вызывать функцию root с указанными параметрами, сравнивать результат с правильным ответом и выводить на экран полученный результат, абсолютную и относительную ошибку.\n\n"
                          "--test-integral и -I, которые позволяют протестировать функцию integral. Фактические параметры вызова integral задаются единственным параметром этой опции в виде F:A:B:E:R, где F—номера используемой функций, A, B, E — значения параметров a, b, eps2 функции integral, R — правильный ответ (вычисленный аналитически). Программа должна вызывать функцию integral с указанными параметрами, сравнивать результат с правильным ответом и выводить на экран полученный результат, абсолютную и относительную ошибку.\n";


static struct option long_opt[] = {
        {"help", 0, 0, 'h'},
        {"root", 0, 0, 'r'},
        {"iterations", 0, 0, 'i'},
        {"test-root", 1, 0, 'R'},
        {"test-integral", 1, 0, 'I'},
        {0,0,0,0}
};


int main(int argc, char **argv) {
    int rez;

    while ( (rez = getopt_long(argc, argv, "hriR:I:", long_opt, NULL)) != -1)
    {
        char *tmp_param_from_run_option;  // Временно записываютсь считываемые аргументы опций если есть

        switch (rez)
        {
            case 'h':  // --help
                printf("%s", possible_options); return 0;
            case 'r':  // --root
                printf("found argument \"r\".\n"); break;
            case 'i':  // --iterations
                iterations_amount = 0;
                should_find_iterations_amount = true;
                break;
            case 'R':  // --test-root
                tmp_param_from_run_option = strtok(optarg, parameter_delimiter);
                double (*first_func_test_root)(double);
                double (*second_func_test_root)(double);
                double (*first_func_derivative_test_root)(double);
                double (*second_func_derivative_test_root)(double);

                switch (tmp_param_from_run_option[0]) {
                    case '1': first_func_test_root = &f1; first_func_derivative_test_root = &f1_derivative; break;
                    case '2': first_func_test_root = &f2; first_func_derivative_test_root = &f2_derivative; break;
                    case '3': first_func_test_root = &f3; first_func_derivative_test_root = &f3_derivative; break;
                }

                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                switch (tmp_param_from_run_option[0]) {
                    case '1': second_func_test_root = &f1; second_func_derivative_test_root = &f1_derivative; break;
                    case '2': second_func_test_root = &f2; second_func_derivative_test_root = &f2_derivative; break;
                    case '3': second_func_test_root = &f3; second_func_derivative_test_root = &f3_derivative; break;
                }

                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double a_to_test_test_root = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double b_to_test_test_root = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double eps1_to_test_test_root = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double right_answer_to_test_test_root = strtod(tmp_param_from_run_option, (char **)NULL);

                double result_of_test_test_root = root(first_func_test_root, second_func_test_root, a_to_test_test_root, b_to_test_test_root,
                                             eps1_to_test_test_root, first_func_derivative_test_root, second_func_derivative_test_root);

                printf("%lf %lf %lf\n", result_of_test_test_root, result_of_test_test_root - right_answer_to_test_test_root,
                       result_of_test_test_root / right_answer_to_test_test_root - 1);
                return 0;
            case 'I':  // --test-integral
                tmp_param_from_run_option = strtok(optarg, parameter_delimiter);
                double (*first_func_test_integral)(double);

                switch (tmp_param_from_run_option[0]) {
                    case '1': first_func_test_integral = &f1; break;
                    case '2': first_func_test_integral = &f2; break;
                    case '3': first_func_test_integral = &f3; break;
                }

                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double a_to_test_test_integral = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double b_to_test_test_integral = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double eps1_to_test_test_integral = strtod(tmp_param_from_run_option, (char **)NULL);
                tmp_param_from_run_option = strtok(NULL, parameter_delimiter);
                double right_answer_to_test_test_integral = strtod(tmp_param_from_run_option, (char **)NULL);

                double result_of_test_test_integral = integral(first_func_test_integral, a_to_test_test_integral,
                                                               b_to_test_test_integral, eps1_to_test_test_integral);

                printf("%lf %lf %lf\n", result_of_test_test_integral, result_of_test_test_integral - right_answer_to_test_test_integral,
                       result_of_test_test_integral / right_answer_to_test_test_integral - 1);
                return 0;
            case '?': printf("Error found !\n"); break;
            default: break;
        }
    }

//    double result_1_2 = root(&f1, &f2, 3, 8,
//                             0.0001, &f1_derivative, &f2_derivative);  // ans: 6.09616967415785
//    double result_1_3 = root(&f1, &f3, 2.01, 2.5,
//                             0.0001, &f1_derivative, &f3_derivative);  // ans: 2.19174342502218
//    double result_2_3 = root(&f2, &f3, 4.0, 4.5,
//                             0.0001, &f2_derivative, &f3_derivative);  // ans: 4.22474487139159
//
//    printf("f1 f2:\t%lf\nf1 f3:\t%lf\nf2 f3:\t%lf\n", result_1_2, result_1_3, result_2_3);

    printf("\n%lf\n", integral(&f1, 2, 6, 0.00001));

    if (should_find_iterations_amount)
        printf("Количество итераций при подсчете трех корней: %u\n", iterations_amount);

    return 0;
}

//  --test-root 3:2:3.0:4.5:0.001:4.224744871391589
//  --test-integral 1:2:6:0.00001:5.36426245424844