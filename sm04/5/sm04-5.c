#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int a = 0;
    int b = 0;
    int n = 0;
    int result = 0;
    result = scanf("%d%d%d", &a, &b, &n);
    if (result == 1) {
        return 1;
    }
    printf("%*s ", n, "");
    for (int j = a, i = 0; j < b; ++j, ++i) {
        if (j + 1 != b) {
            printf("%*d ", n, j);
        } else {
            printf("%*d\n", n, j);
        }
    }
    for (int j = a, i = 0; j < b; ++j, ++i) {
        printf("%*d ", n, j);
        for (int k = a; k < b; ++k) {
            long long result = (long long)j * (long long)k;
            if (k + 1 != b) {
                printf("%*lld ", n, result);
            } else {
                printf("%*lld\n", n, result);
            }
        }
    }
    return 0;
}
