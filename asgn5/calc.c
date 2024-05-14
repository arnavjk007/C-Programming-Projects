#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool isValid(const char *t, int len) {
    int validTrigCount = 0;
    for (int i = 0; i < len; i++) {
        if (!((t[i] > 44 && t[i] < 58) || t[i] == 97 || t[i] == 99 || t[i] == 37 || t[i] == 43
                || t[i] == 42 || (t[i] > 113 && t[i] < 117)))
            return false;
        if (t[i] == 97 || t[i] == 99 || (t[i] > 113 && t[i] < 117))
            validTrigCount++;
    }
    return validTrigCount < 2 ? true : false;
}

int main(int argc, char **argv) {
    while (1) {
        int opt = getopt(argc, argv, "hm");
        if ((opt != -1 && opt != 109) || opt == 104) {
            fprintf(stdout, USAGE, argv[0]);
            return 0;
        }
        fprintf(stderr, "> ");
        char expr[1024] = { 0 };
        fgets(expr, 1024, stdin);
        expr[strlen(expr) - 1] = 0;
        char *saveptr;
        bool error = false, useLib = false;
        //token has the entire number/word
        const char *token = strtok_r(expr, " ", &saveptr);
        switch (opt) {
        case 104: break;
        case 109: useLib = true; break;
        default: break;
        }

        while (token != NULL && !error) {
            if (!isValid(token, (int) strlen(token))) {
                fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                error = true;
                break;
            }
            unsigned char c = token[0];
            double number = strtod(token, NULL);
            if (number < 0 || (strlen(token) > 1 && c == '+'))
                c = token[1];
            switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                if (!(apply_binary_operator(binary_operators[c])))
                    error = true;
                break;
            case 's':
            case 'c':
            case 't':
            case 'a':
            case 'r':
                if (!(apply_unary_operator(
                        useLib ? libm_unary_operators[c] : my_unary_operators[c])))
                    error = true;
                break;
            default:
                if (c >= 48 && c <= 57) {
                    if (!stack_push(number)) {
                        error = true;
                    }
                } else
                    fprintf(stderr, ERROR_BAD_CHAR, c), error = true;
                break;
            }
            //points to next number/word
            token = strtok_r(NULL, " ", &saveptr);
        }
        if (!error) {
            stack_print();
            if (feof(stdin))
                break;
            printf("\n");
        }
        stack_clear();
    }
    return 0;
}
