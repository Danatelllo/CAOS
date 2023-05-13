#include "sys/wait.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

enum { HOURS = 24, MINUTES = 60, LENGTH = 11 };

int main() {
    char date[LENGTH];
    int days;
    while (scanf("%d", &days) == 1) {
        time_t now = time(NULL);
        int tmp = 0;
        int copy_now = (int)now;
        if (__builtin_smul_overflow(HOURS * MINUTES * MINUTES, days, &tmp)) {
            printf("OVERFLOW\n");
            continue;
        }
        if (__builtin_sadd_overflow(copy_now, tmp, (int *)&now)) {
            printf("OVERFLOW\n");
            continue;
        }
        struct tm *result = localtime(&now);
        strftime(date, sizeof date, "%Y-%m-%d", result);
        printf("%s\n", date);
    }
    return 0;
}