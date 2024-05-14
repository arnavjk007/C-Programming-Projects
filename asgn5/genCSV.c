#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double Abs(double x) {
    return x < 0 ? x - 2 * x : x;
}

double Sin(double x) {
    double sum = x;
    int i = 3, a = 0;
    double term = x;
    while (1) {
        double fac = 1.0, pow = 1.0;
        for (int j = 1; j < i + 1; j++) {
            fac *= j;
            pow *= x;
        }
        term = (a % 2 ? 1.0 : -1.0) * pow / fac;
        if (Abs(term) < EPSILON)
            break;
        sum += term;
        i += 2, a += 1;
    }
    return sum;
}

double Cos(double x) {
    double sum = 1.0;
    int i = 2, a = 0;
    double term = x;
    while (1) {
        double fac = 1.0, pow = 1.0;
        for (int j = 1; j < i + 1; j++) {
            fac *= j;
            pow *= x;
        }
        term = (a % 2 ? 1.0 : -1.0) * pow / fac;
        if (Abs(term) < EPSILON)
            break;
        sum += term;
        i += 2, a += 1;
    }
    return sum;
}

double Tan(double x) {
    return Sin(x) / Cos(x);
}

int main(int argc, char **argv) {
    (void) argc, (void) argv;
    printf("VALUE       , mySIN       , libSIN     ,  myCOS       ,  libCOS      ,  myTAN       ,  "
           "libTAN      ,\n");
    for (double i = -40; i <= 40; i += 0.5) {
        printf("%.10f, %.10f, %.10f, %.10f, %.10f, %.10f, %.10f,\n", i, Sin(i), sin(i), Cos(i),
            cos(i), Tan(i), tan(i));
    }
    return 0;
}
