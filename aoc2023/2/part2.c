#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

int main() {
    FILE *file = fopen("input1", "r");

    char line[256];
    size_t game_num = 1;
    size_t sum_of_game_powers = 0;

    // Each game
    while (fgets(line, 256, file)) {
        long max_red = 0;
        long max_green  = 0;
        long max_blue = 0;
        // Each draw
        char* rest_of_line = line;
        char* token;
        while ((token = strsep(&rest_of_line, ";:")) != NULL) {
            // Each cube in a draw
            char* rest_of_token = token;
            char* sub_token;
            while ((sub_token = strsep(&rest_of_token, ",\n")) != NULL) {
                char* rest;
                long num = strtol(sub_token, &rest, 10);
                if (num != 0) {
                    if (strlen(rest) == 4) {
                        max_red = num > max_red ? num : max_red;
                    } else if (strlen(rest) == 6) {
                        max_green = num > max_green ? num : max_green;
                    } else if (strlen(rest) == 5) {
                        max_blue = num > max_blue ? num : max_blue;
                    }
                }

            }
        }
        long game_power = max_red * max_green * max_blue;
        printf("game num: %zu, r: %ld, g: %ld, b: %ld game power: %ld\n", game_num, max_red, max_green, max_blue, game_power);

        sum_of_game_powers += game_power;
        game_num++;
    }

    printf("sum of game powers: %zu\n", sum_of_game_powers);
}
