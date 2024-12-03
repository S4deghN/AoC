#include <stdio.h>
#include <string.h>
#include <stdint.h>

// one
// two
// three
// four
// five
// six
// seven
// eight
// nine

int main() {
    FILE *file = fopen("input2", "r");

    char line[256];
    uint32_t accumulator = 0;

    while (fgets(line, 256, file)) {
        char *c = line;
        unsigned char first = 0;
        unsigned char last;
        while (*c) {
            if (*c > 47 && *c < 58) {
                first = first == 0 ? *c : first;
                last = *c;
            } else if (strncmp(c, "one", 3) == 0) {
                first = first == 0 ? '1' : first;
                last = '1';
            } else if (strncmp(c, "two", 3) == 0) {
                first = first == 0 ? '2' : first;
                last = '2';
            } else if (strncmp(c, "three", 4) == 0) {
                first = first == 0 ? '3' : first;
                last = '3';
            } else if (strncmp(c, "four", 4) == 0) {
                first = first == 0 ? '4' : first;
                last = '4';
            } else if (strncmp(c, "five", 4) == 0) {
                first = first == 0 ? '5' : first;
                last = '5';
            } else if (strncmp(c, "six", 3) == 0) {
                first = first == 0 ? '6' : first;
                last = '6';
            } else if (strncmp(c, "seven", 5) == 0) {
                first = first == 0 ? '7' : first;
                last = '7';
            } else if (strncmp(c, "eight", 5) == 0) {
                first = first == 0 ? '8' : first;
                last = '8';
            } else if (strncmp(c, "nine", 4) == 0) {
                first = first == 0 ? '9' : first;
                last = '9';
            }

            ++c;
        }
        uint32_t number = (first - 48) * 10 + (last - 48);
        accumulator += number;
        printf("%d\n", number);
    }
    printf("accumulator: %d\n", accumulator);
}
