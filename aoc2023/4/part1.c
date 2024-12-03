#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define sizeof_array(a) sizeof(a) / sizeof(a[0])

#define CAPACITY (1 << 4)
typedef struct {
    uint64_t buff[CAPACITY];
    uint32_t indexer;
} Ring;

uint32_t mask(uint32_t val) {
    return val & (CAPACITY - 1);
}

uint64_t* ring_at(Ring *r, size_t index) {
    return &(r->buff[mask(r->indexer + index)]);
}

int main() {
    FILE *file = fopen("input1", "r");

    char line[256];
    long winning_numbers[10] = {0};
    Ring r;
    for (size_t i = 0; i < CAPACITY; ++i) {
        r.buff[i] = 1;
    }

    uint64_t sum = 0;

    while (fgets(line, 256, file)) {
        char *devider = strchr(line, '|');
        *devider = '\0';

        // strip the beginning
        char *winning_str = strchr(line, ':') + 1;
        char *input_str = devider + 1;

        long *i = winning_numbers;
        while (1) {
            long num = strtol(winning_str, &winning_str, 10);
            if (num == 0) {
                break;
            }

            *i++ = num;
            // printf("win: %ld\n", num);
        }

        long score = 0;
        uint64_t multiplier = *ring_at(&r, 0);
        *ring_at(&r, 0) = 1;
        r.indexer++;

        while (1) {
            long num = strtol(input_str, &input_str, 10);
            if (num == 0) {
                break;
            }

            for (size_t i = 0; i < sizeof_array(winning_numbers); ++i) {
                if (num == winning_numbers[i]) {
                    score++;
                }
            }
            // printf("input: %ld\n", num);
        }
        printf("multiplier: %lu\n", multiplier);

        sum += multiplier;

        for (size_t i = 0; i < score; ++i) {
            (*ring_at(&r, i)) += 1 * multiplier;
        }
    }

    printf("sum: %lu\n", sum);
}
