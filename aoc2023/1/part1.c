#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main() {
    FILE *file = fopen("input1", "r");

    char line[256];
    uint32_t accumulator = 0;

    while (fgets(line, 256, file)) {
        // printf("%s", line);

        char *c = line;
        char first = 0;
        char last;
        while (*c) {
            if (*c > 47 && *c < 58) {
                if (first == 0) {
                    first = *c;
                }
                last = *c;
            }
            ++c;
        }
        uint32_t number = (first - 48) * 10 + (last - 48);
        accumulator += number;
        printf("%d\n", number);
    }
    printf("accumulator: %d\n", accumulator);
}
