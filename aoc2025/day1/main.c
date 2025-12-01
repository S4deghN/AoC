#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long ulong;

int main()
{
    FILE *f = fopen("input2", "r");
    char line[32];

    int count = 0;
    long dial = 50;

    while(fgets(line, sizeof(line), f)) {
        long step = strtol(line + 1, NULL, 10);
        count += (step/100);
        step %= 100;
        step *= line[0] == 'L' ? -1 : 1;
        if (dial%100) {
            if (dial > 0) {
                if ((step > 0 && step >= (100 - (dial%100))) ||
                    (step < 0 && -step >= ((dial%100)))) {
                    ++count;
                }
            } else {
                if ((step > 0 && step >= (abs(dial%100))) ||
                    (step < 0 && -step >= (100 + (dial%100)))) {
                    ++count;
                }
            }
        }
        dial += step;
        printf("%.*s: step = %d, dial = %d, count = %d\n", strlen(line) - 1, line, step, dial, count);
    }
}
