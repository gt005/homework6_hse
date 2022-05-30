#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double f1(double x);
double f2(double x);
double f3(double x);
double f1_derivative(double x);
double f2_derivative(double x);
double f3_derivative(double x);


int main(int argc, char **argv) {
    double a = 12.0;
    printf("%lf\n", f3_derivative(a));


    return 0;
}

