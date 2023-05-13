#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MIN_INT32_T = -2147483648,
    C_IN_DECIMAL = 12,
    B_IN_DECIMAL = 13,
    A_IN_DECIMAL = 10,
    MULTIPLAYER = 13
};

void please_compute_and_print_some_strange_values_from_some_other_strange_values(
    const char *val1, const char *val2) {
    char *end;
    long first_number = strtol(val1, &end, 13);
    long second_number = strtol(val2, &end, 13);
    int32_t add_result = 0;
    if (__builtin_add_overflow(first_number, second_number, &add_result)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
    if (second_number == 0 ||
        (first_number == MIN_INT32_T && second_number == -1)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
}
