#include "cse13s_random.h"
#include "names.h"

#include <stdio.h>

int checkWinner(int num_players, int player_chips[]) {

    int non_zero_values = 0;
    int winnerIndex = -1;

    for (int i = 0; i < num_players; i++) {
        if (player_chips[i] > 0) {
            non_zero_values += 1;
            winnerIndex = i;
        }
    }

    if (non_zero_values == 1) {

        //		printf("%s won!\n", player_name[winnerIndex]);
        printf("%s won!\n", player_name[winnerIndex]);
        return 0;
    }
    return 1;
}

void printStatus(int num_players, int player_chips[]) {
    for (int i = 0; i < num_players; i++) {
        printf("%s ends her turn with %d.\n", player_name[i], player_chips[i]);
    }
}

int main() {

    typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

    const Position die[6] = {
        DOT,
        DOT,
        DOT,
        LEFT,
        CENTER,
        RIGHT,
    };

    int num_players = 3;
    printf("Number of players (3 to 11)? ");
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    unsigned seed = 4823;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    //check if seed number is valid
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        cse13s_random_seed(4823);
    } else {
        cse13s_random_seed(seed);
    }
    //generates array with 3 chips per player
    int player_chips[num_players];
    int original_chips[num_players];
    for (int i = 0; i < num_players; i++) {
        player_chips[i] = 3;
        original_chips[i] = 3;
    }
    int index = 0;
    int condition = 1;
    int max = num_players;
    while (condition != 0) {
        if (player_chips[index] < 1) {

            if (index + 1 == max) {
                index = 0;
            } else {
                index += 1;
            }
            continue;
        }

        //	int chipsLost = 0;
        if (original_chips[index] > 3) {
            original_chips[index] = 3;
        }

        for (int i = 0; i < original_chips[index]; i++) {

            int random_number = cse13s_random() % 6;
            //		printf("The random number is %d\n", random_number);
            //		printf("%d is rolled", random_number%6);

            Position roll_result = die[random_number];

            //		printf("Number before roll: %d \n", player_chips[index]);

            if (roll_result == DOT) {
                player_chips[index] += 0;
                //				printf("DOT, %d\n", random_number);
            } else if (roll_result == LEFT) {
                //				printf("RIGHT, %d\n", random_number);
                if (index + 1 == max) {
                    player_chips[index] -= 1;
                    player_chips[0] += 1;
                    original_chips[0] += 1;
                } else {
                    player_chips[index] -= 1;
                    player_chips[index + 1] += 1;
                    original_chips[index + 1] += 1;
                }
                //			chipsLost += 1;
            } else if (roll_result == CENTER) {
                //				printf("CENTER, %d\n", random_number);
                player_chips[index] -= 1;
                //			chipsLost += 1;
            } else {
                //				printf("LEFT, %d\n", random_number);
                if (index == 0) {
                    player_chips[index] -= 1;
                    player_chips[max - 1] += 1;
                    original_chips[max - 1] += 1;
                } else {
                    player_chips[index] -= 1;
                    player_chips[index - 1] += 1;
                    original_chips[index - 1] += 1;
                }
                //			chipsLost += 1;
            }

            //		printf("Number after roll: %d\n", player_chips[index]);
        }

        //	original_chips[index] -= chipsLost;

        //	printf("%d times rolled \n", original_chips[index]);
        if (player_chips[index] > 3) {
            original_chips[index] = 3;
        } else {
            original_chips[index] = player_chips[index];
        }
        //	printf("%d is og chips after", original_chips[index]);

        printf("%s: ends her turn with %d\n", player_name[index], player_chips[index]);

        //	printStatus(num_players, player_chips);
        if (index + 1 == max) {
            index = 0;
        } else {
            index += 1;
        }

        condition = checkWinner(num_players, player_chips);
    }
    return 0;
}
