#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double Abs(double x) {
    return x < 0 ? x - 2 * x : x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
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
