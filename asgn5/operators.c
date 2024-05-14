#include "operators.h"

#include "messages.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

bool apply_binary_operator(binary_operator_fn op) {
    double first = 0;
    double second = 0;
    if (stack_size < 2 || !(stack_pop(&first)) || !(stack_pop(&second))) {
        fprintf(stderr, ERROR_BINARY_OPERATOR);
        return false;
    }
    stack_push(op(second, first));
    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    double value = 0;
    if (stack_size < 1 || !(stack_pop(&value))) {
        fprintf(stderr, ERROR_UNARY_OPERATOR);
        return false;
    }
    stack_push(op(value));
    return true;
}

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}

double operator_div(double lhs, double rhs) {
    return lhs / rhs;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    }
    return false;
}
