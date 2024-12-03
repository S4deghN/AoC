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

    while (line[1][0] != '\0') {
        char *cursor = line[1];
        while (*cursor) {
            if (is_num(*cursor)) {
                char *start = cursor;
                while (is_num(*++cursor));
                char *end = cursor - 1;

                long num = strtol(start, NULL, 10);
                bool num_is_valid = false;

                for (ptrdiff_t i = -1; i <= 1; ++i) {
                    for (char *j = start + (i*256) - 1; j <= end + (i*256) + 1; ++j) {
                        if (is_symbol(*j)) {
                            num_is_valid = true;
                            break;
                        }
                    }
                }

                if (num_is_valid) {
                    sum += num;
                    printf("valid num: %ld\n", num);
                }
            }
            ++cursor;
        }

        printf("%s", line[1]);

        memcpy(line[0], line[1], 256);
        memcpy(line[1], line[2], 256);
        char *ret = fgets(line[2], 256, file);
        if (ret == NULL) {
            memset(line[2], 0, 256);
        }
    }

    printf("sum: %d\n", sum);
}
