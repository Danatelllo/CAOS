#include <alloca.h>
#include <dlfcn.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_MANTISSA = 16777215 };

int main() {
    unsigned int number;
    while (scanf("%ui", &number) > 0) {
        if (number <= MAX_MANTISSA) {
            printf("%d\n", 1);
            continue;
        }
        while (number % 2 == 0 && number > 0) {
            number /= 2;
        }
        if (number <= MAX_MANTISSA) {
            printf("%d\n", 1);
        } else {
            printf("%d\n", 0);
        }
    }
}
