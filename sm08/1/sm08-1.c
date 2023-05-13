#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum {
    SIZE_OF_BUF = 63,
    DECEMICAL_BASE = 10,
    BAD_ASCII_TYPE1 = 31,
    BAD_ASCII_TYPE2 = 127
};

void check_buf(char *buf, int *counter, int *was_double, double *min_double,
               int *was_whole_number, int *max_int32, int *was_nan,
               int *was_plus_inf, int *was_minus_inf) {
    int is_whole_number = 1;
    int is_fractional_number = 1;
    int counter_of_dot = 0;
    for (int j = 0; j < *counter; ++j) {
        if (j == 0 && buf[j] != '-' && buf[j] != '+' && !isdigit(buf[j])) {
            is_fractional_number = 0;
            is_whole_number = 0;
            break;
        } else if (!isdigit(buf[j]) && buf[j] != '.' && j > 1) {
            is_whole_number = 0;
            is_fractional_number = 0;
            break;
        } else if (buf[j] == '.') {
            ++counter_of_dot;
            is_whole_number = 0;
            if (counter_of_dot > 1) {
                is_fractional_number = 0;
                break;
            }
        }
    }
    if (counter_of_dot == 0) {
        is_fractional_number = 0;
    }
    if (is_fractional_number == 1) {
        char *ptr;
        double current_fractional_number = strtod(buf, &ptr);
        (void)ptr;
        if (*was_double == 0) {
            *min_double = current_fractional_number;
            *was_double = 1;
        } else if (current_fractional_number < *min_double) {
            *min_double = current_fractional_number;
        }
    }
    if (is_whole_number == 1) {
        int current_number;
        char *ptr;
        long result = strtol(buf, &ptr, DECEMICAL_BASE);
        if (!(__builtin_add_overflow(result, 0, &current_number))) {
            if (*was_whole_number == 0) {
                *max_int32 = current_number;
                *was_whole_number = 1;
            } else if (*max_int32 < current_number) {
                *max_int32 = current_number;
            }
        }
    }
    char *ptr;
    double current_fractional_number = strtod(buf, &ptr);
    (void)ptr;
    if (isnan(current_fractional_number)) {
        *was_nan = 1;
    }
    if (isinf(current_fractional_number) && current_fractional_number < 0) {
        *was_minus_inf = 1;
    }
    if (isinf(current_fractional_number) && current_fractional_number > 0) {
        *was_plus_inf = 1;
    }
    *counter = 0;
    for (int j = 0; j < SIZE_OF_BUF; ++j) {
        buf[j] = 'h';
    }
}

int main(int argc, char *argv[]) {
    FILE *f;
    int is_stdin = 0;
    if (argc == 2) {
        f = fopen(argv[1], "r");
        if (f == NULL) {
            fprintf(stderr, "%s", "file wasn't open.\n");
            return 1;
        }
    } else if (argc == 1) {
        f = stdin;
        is_stdin = 1;
        if (f == NULL) {
            fprintf(stderr, "%s", "file wasn't open.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "%s", "file wasn't open.\n");
        return 1;
    }

    int sym;
    int counter = 0;
    double min_double = 0;
    int max_int32 = 0;
    int was_whole_number = 0;
    int was_double = 0;
    int was_nan = 0;
    int was_minus_inf = 0;
    int was_plus_inf = 0;
    char buf[SIZE_OF_BUF];
    for (int j = 0; j < SIZE_OF_BUF; ++j) {
        buf[j] = 'h';
    }
    while ((sym = getc_unlocked(f)) != EOF) {
        if (ferror(f) != 0) {
            fprintf(stderr, "%s", "error in opened file.\n");
            return 1;
        }
        if (((sym >= 0 && sym <= BAD_ASCII_TYPE1) || sym == BAD_ASCII_TYPE2) &&
            sym != '\n' && sym != '\t' && sym != '\r') {
            fprintf(stderr, "%s", "bad char in opened file.\n");
            return 1;
        }
        if (isspace(sym) && counter > 0) {
            check_buf(buf, &counter, &was_double, &min_double,
                      &was_whole_number, &max_int32, &was_nan, &was_plus_inf,
                      &was_minus_inf);
        } else {
            if (counter == SIZE_OF_BUF) {
                fprintf(stderr, "%s", "too long word.\n");
                return 1;
            }
            buf[counter] = sym;
            ++counter;
        }
    }
    if (sym == EOF && counter > 0) {
        check_buf(buf, &counter, &was_double, &min_double, &was_whole_number,
                  &max_int32, &was_nan, &was_plus_inf, &was_minus_inf);
    }
    if (is_stdin == 0) {
        fclose(f);
    }
    if ((was_double == 0 && was_nan == 0 && was_minus_inf == 0 &&
         was_plus_inf == 0) ||
        was_whole_number == 0) {
        fprintf(stderr, "%s", "answer isn't full.\n");
        return 1;
    }
    if (was_double == 0 && was_plus_inf == 1) {
        min_double = INFINITY;
    }
    if (was_minus_inf == 1) {
        min_double = -INFINITY;
    }
    if (was_nan == 1) {
        min_double = NAN;
    }
    printf("%d %.10g\n", max_int32, min_double);
}
