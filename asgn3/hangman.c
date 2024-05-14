#include "hangman_helpers.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int num_guesses = 0;
    (void) argc;
    char *secret = argv[1];
    if (is_valid_secret(secret) == false) {
        return 1;
    }
    int length = getStrLength(secret);

    char converted_secret[length];
    convertString(converted_secret, length, secret);

    char eliminated_guesses[7] = { 0 };
    int eliminated_guesses_index = 0;

    char previous_guesses[26] = { 0 };
    int index = 0;

    while (num_guesses < 6) {

        //checks if the user has won
        if (checkWinner(secret, converted_secret) == 0) {
            printf("%s\n", arts[num_guesses]);
            printf("    Phrase: %s\n", secret);
            printf("Eliminated: %s\n", eliminated_guesses);
            printf("\n");
            printf("You win! The secret phrase was: %s\n", secret);
            return 0;
        }

        //print setup
        //print art
        printf("%s\n", arts[num_guesses]);

        //print phrase line
        printf("    Phrase: ");
        printPhrase(converted_secret, length);
        printf("\n");

        //print eliminated characters line
        printf("Eliminated: %s\n", eliminated_guesses);
        printf("\n");

        //read guess and store in char guess

        char guess = '\0';
        while (true) {
            guess = read_letter();
            if ((contains(previous_guesses, guess) == false
                    && is_lowercase_letter(guess) == true)) {
                break;
            }
            //        printf("\r");
        }

        previous_guesses[index] = guess;
        index += 1;
        //printf("Previous guesses has; %s\n", previous_guesses);
        //updates phrase if guess appears in it
        if (string_contains_character(secret, guess)) {
            for (int i = 0; i < length; i++) {
                if (secret[i] == guess) {
                    converted_secret[i] = guess;
                }
            }
            continue;
        }
        //updates eliminated if guess doesn't appear in it
        else {
            eliminated_guesses[eliminated_guesses_index] = guess;
            // sort the eliminated line
            sort(eliminated_guesses, eliminated_guesses_index);
            eliminated_guesses_index += 1;
        }
        num_guesses += 1;
    }

    //print if user loses

    //print setup
    //print art
    printf("%s\n", arts[num_guesses]);

    //print phrase line
    printf("    Phrase: ");
    printPhrase(converted_secret, length);
    printf("\n");

    //print eliminated characters line
    printf("Eliminated: %s", eliminated_guesses);
    printf("\n");

    //print correct phrase
    printf("\nYou lose! The secret phrase was: %s\n", secret);

    return 0;
}
