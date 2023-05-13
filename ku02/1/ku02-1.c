#include <ctype.h>
#include <stdio.h>

void strip_spaces(char *buf) {
    char *str = buf;
    char *str_for_letters = buf;
    int was_space = 0;
    int was_letter = 0;
    while (*str != '\0') {
        if (isspace(*str) && was_space == 0) {
            if (was_letter == 1) {
                *str_for_letters = ' ';
                was_space = 1;
                ++str_for_letters;
            }
        } else if (!isspace(*str)) {
            was_letter = 1;
            *str_for_letters = *str;
            ++str_for_letters;
            was_space = 0;
        }
        ++str;
    }
    if (str_for_letters != buf && *(str_for_letters - 1) == ' ') {
        --str_for_letters;
    }
    *str_for_letters = '\0';
}
