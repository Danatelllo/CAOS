#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

enum { SIZE = 10, EXCEPTION = 13 };

jmp_buf buf[EXCEPTION];
int errors[SIZE];
int current = 0;

jmp_buf *try(int exception) {
    errors[current] = exception;
    ++current;
    return &buf[current - 1];
}

void endtry() {
    --current;
}

void throw(int exception) {
    while (current > 0) {
        if (errors[current - 1] == exception) {
            --current;

            longjmp(buf[current], 1);
        }
        --current;
    }
    exit(EXCEPTION);
}
