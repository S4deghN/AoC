#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

bool is_num(char c) {
    return (c > 47 && c < 58);
}

bool is_symbol(char c) {
    return (c > 32 && c < 46) || (c > 57 && c < 65) || c == '/';
}

int main() {
    FILE *file = fopen("input1", "r");

    char line[3][256];

    memset(line[0], 0, 256);
    fgets(line[1], 256, file);
    fgets(line[2], 256, file);
    uint32_t sum = 0;

    do {
        char *cursor = line[1];
        do {
            int numbers_found = 0;
            uint32_t numbers_product = 1;
            if (*cursor == '*') {
                for (ptrdiff_t i = -1; i <= 1; ++i) {
                    for (char *j = cursor + (i*256) - 1; j <= cursor + (i*256) + 1; ++j) {
                        if (is_num(*j)) {
                            while (is_num(*--j));
                            char *end;
                            long num = strtol(j+1, &end, 10);
                            j = end;
                            numbers_found++;
                            numbers_product *= num;
                        }
                    }
                }
            }
            if (numbers_found == 2) {
                sum += numbers_product;
            }
        } while (*++cursor);

        printf("%s", line[1]);

        memcpy(line[0], line[1], 256);
        memcpy(line[1], line[2], 256);
        char *ret = fgets(line[2], 256, file);
        if (ret == NULL) {
            memset(line[2], 0, 256);
        }

    } while (line[1][0] != '\0');

    printf("sum: %d\n", sum);
}
