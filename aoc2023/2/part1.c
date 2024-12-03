#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    FILE *file = fopen("input1", "r");

    char line[256];
    uint32_t accumulator = 0;
    size_t game_num = 1;
    size_t sum_of_possible_games = 0;
    bool possible_game = true;
    // only 12 red cubes, 13 green cubes, and 14 blue cubes

    while (fgets(line, 256, file)) {

        //
        // Tokenize each game
        //
        char* rest_of_line = line;
        char* token;
        while ((token = strsep(&rest_of_line, ";:")) != NULL) {
            // printf("++++++++++++\n");

            int red = 0;
            int green  = 0;
            int blue = 0;

            //
            // Tokenize each draw
            //
            char* rest_of_token = token;
            char* sub_token;
            while ((sub_token = strsep(&rest_of_token, ",\n")) != NULL) {
                char* rest;
                long num = strtol(sub_token, &rest, 10);
                // printf("num: %ld: ,%s\n", num, rest);

                if (num != 0) {
                    if (strlen(rest) == 4) {
                        red = num;
                    } else if (strlen(rest) == 6) {
                        green = num;
                    } else if (strlen(rest) == 5) {
                        blue = num;
                    }
                }

            }
            if (red > 12 || green > 13 || blue > 14 || game_num == 4) {
                possible_game = false;
                printf("game num: %ld, r: %d, g: %d, b: %d\n", game_num, red, green, blue);
            }
        }
        if (possible_game) {
            sum_of_possible_games += game_num;
        }

        possible_game = true;
        game_num++;
    }

    printf("sum of possible games: %zu\n", sum_of_possible_games);
}
