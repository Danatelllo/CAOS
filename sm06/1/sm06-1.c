#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int is_int32(long number) {
    return number == (int32_t)number;
}

int is_int16(long number) {
    return number == (int16_t)number;
}

int is_int8(long number) {
    return number == (int8_t)number;
}

int is_number(const char *string) {
    if (*string == '\0') {
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    long number = 0;
    char *end;
    for (int j = 1; j < argc; ++j) {
        errno = 0;
        number = strtol(argv[j], &end, 10);
        if (errno != 0) {
            printf("%d\n", -1);
        } else if (!is_number(end)) {
            printf("%d\n", -1);
        } else if (argv[j][0] == '\0') {
            printf("%d\n", -1);
        } else if (is_int8(number)) {
            printf("%d\n", 1);
        } else if (is_int16(number)) {
            printf("%d\n", 2);
        } else if (is_int32(number)) {
            printf("%d\n", 4);
        } else {
            printf("%d\n", -1);
        }
    }
}
