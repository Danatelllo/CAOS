#include <alloca.h>
#include <dlfcn.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef union {
    float number;

    struct {
        unsigned int frac : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } float_state;
} HelperFloat;

int main() {
    float number;
    HelperFloat fl;
    while (scanf("%fl", &number) > 0) {
        fl.number = number;
        printf("%d", fl.float_state.sign);
        printf(" ");
        printf("%d", fl.float_state.exponent);
        printf(" ");
        printf("%0x", fl.float_state.frac);
        printf("\n");
    }
    return 0;
}
