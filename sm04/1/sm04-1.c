#include <stdio.h>

int main(void) {
    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int answer = 0;
    int result = scanf("%u", &a);
    if (result != 1) {
        return 1;
    }
    result = scanf("%u", &b);
    if (result != 1) {
        return 1;
    }
    if (a % 2 == 1 && b % 2 == 0) {
        a -= 1;
        answer = (a / 2) + (b / 2);
    } else if (b % 2 == 1 && a % 2 == 0) {
        b -= 1;
        answer = (a / 2) + (b / 2);
    } else if (b % 2 == 1 && a % 2 == 1) {
        answer = 1 + ((a - 1) / 2 + (b - 1) / 2);
    } else {
        answer = (a / 2) + (b / 2);
    }
    printf("%u\n", answer);
    return 0;
}
