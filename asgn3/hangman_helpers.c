#include "hangman_helpers.h"

int getStrLength(const char *s) {
    int i = 0;
    while (true) {
        if (s[i] == '\0') {
            return i;
        }
        i += 1;
    }
}

bool is_lowercase_letter(char c) {
    return c >= 97 && c <= 122;
}

int checkWinner(const char *secret, char s[]) {
    int length = getStrLength(secret);
    for (int i = 0; i < length; i++) {
        if (secret[i] != s[i]) {
            return 1;
        }
    }
    return 0;
}

bool is_valid_secret(const char *secret) {
    int length = getStrLength(secret);

    for (int i = 0; i < length; i++) {
        if (is_lowercase_letter(secret[i]) == false
            && string_contains_character(punctuation, secret[i]) == false) {
            printf("invalid character: '%c'\n", secret[i]);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        } else if (length > 256) {
            printf("the secret phrase is over 256 characters\n");
            return false;
        } else {
            continue;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {

    int length = getStrLength(s);

    for (int i = 0; i < length; i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

char read_letter(void) {
    // char temp[2];
    char guess = '\n';
    printf("Guess a letter: ");
    while (guess == '\n') {
        scanf("%c", &guess);
    }
    //guess = temp[0];
    // printf("#%d# is returned\n", guess);
    return guess;
}

void convertString(char s[], int length, char *secret) {

    for (int i = 0; i < length; i++) {
        if (string_contains_character(punctuation, secret[i]) == false) {
            s[i] = '_';
        } else {
            s[i] = secret[i];
        }
    }
}

void printPhrase(char s[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", s[i]);
    }
}

int getArrayLength(char s[]) {
    int count = 0;
    while (s[count] != '\0') {
        count += 1;
    }
    return count + 1;
}

void sort(char s[], int index) {
    int length = index + 1;
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (s[j] > s[j + 1]) {
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

bool contains(char s[], char c) {
    int length = getArrayLength(s);
    for (int i = 0; i < length; i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}
