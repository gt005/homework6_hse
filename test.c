#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

double f2(double x);
double f3(double x);

int main(int argc, char **argv) {
    double a = 3.0;
    printf("%lf\n", f2(a));
    printf("%lf\n", f3(a));
    printf("%lf\n", f3(a));

    return 0;
}

