#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

void normalize_path(char *buf) {
    int was_slash = 0;
    char *str = buf;
    while (*str != '\0') {
        if (*str == '/' && !was_slash) {
            *buf = *str;
            ++buf;
            was_slash = 1;
        }
        if (*str != '/') {
            *buf = *str;
            was_slash = 0;
            ++buf;
        }
        ++str;
    }
    *buf = '\0';
}
