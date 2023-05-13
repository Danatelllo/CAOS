#include <ctype.h>
#include <stdio.h>

enum { ZERO_IN_ASCII = 48 };

int main(void) {
    int c;
    int answer = 0;
    while ((c = getchar()) != EOF) {
        if (isdigit(c)) {
            answer += c - (int)ZERO_IN_ASCII;
        }
    }
    printf("%d\n", answer);
    return 0;
}
