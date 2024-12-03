#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define sizeof_array(a) sizeof(a) / sizeof(a[0])

bool is_num(char c) {
    return c > 47 && c < 58;
}

bool is_alpha(char c) {
    return c > 96 && c < 123;
}

int main() {
    FILE *file = fopen("input1", "r");

    char line[256];
    // seed[][0] = num
    // seed[][1] = flag
    uint64_t seed[32][2] = {0};

    (void)fgets(line, 256, file);
    char *rest = strchr(line, ':') + 1;
    size_t seed_size = 0;
    while (*rest != '\n') {
        int64_t num = strtoll(rest, &rest, 10);
        seed[seed_size++][0] = num;
    }

    for (size_t i = 0; i < seed_size; i++ ) {
        printf("seed: %lu\n", seed[i][0]);
    }
    printf("-----\n");


    while (fgets(line, 256, file)) {
        if (is_num(line[0])) {
            // extract range numbers of this line
            char *rest = line;
            uint64_t destination = strtoll(rest, &rest, 10);
            uint64_t source = strtoll(rest, &rest, 10);
            uint64_t range = strtoll(rest, &rest, 10);

            // check if any of the seed can convert on this line
            for (int i = 0; i < seed_size; ++i) {
                if (seed[i][0] >= source && seed[i][0] < source + range && seed[i][1] == 0) {
                    seed[i][0] = destination + (seed[i][0] - source);
                    seed[i][1] = 1;
                }
            }
        } else if (is_alpha(line[0])) {
            // reset the flags
            for (int i = 0; i < seed_size; ++i) {
                seed[i][1] = 0;
            }
        } else {
            // at the end of a map
            continue;
        }
    }

    uint64_t lowest = -1;
    for (int i = 0; i < seed_size; ++i) {
        lowest = seed[i][0] < lowest ? seed[i][0] : lowest;
        printf("seeds: %ld\n", seed[i][0]);
    }
    printf("-----\n");
    printf("lowest: %ld\n", lowest);

}
