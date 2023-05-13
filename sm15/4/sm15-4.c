#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

volatile unsigned int last_value = 0;
volatile unsigned int counter = 0;
volatile unsigned int prev_value = 0;

enum { MIL_SEK = 100000, END_PROCEDURE = 8 };

int is_prime(unsigned int n) {
    if (n <= 1) {
        return 0;
    }
    for (unsigned int i = 2; i <= ((unsigned int)sqrt(n)) + 1; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void print_number(int signum) {
    ++counter;
    printf("%u\n", last_value);
    fflush(stdout);
}

int main() {
    unsigned int start = 0;
    unsigned int end = 0;
    int res = scanf("%u", &start);
    (void)res;
    res = scanf("%u", &end);
    (void)res;
    struct sigaction handler = {
            .sa_handler = &print_number,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGALRM, &handler, NULL);
    struct itimerval timer;
    timer.it_value.tv_usec = MIL_SEK;
    timer.it_interval.tv_usec = MIL_SEK;
    setitimer(ITIMER_REAL, &timer, NULL);
    for (unsigned int i = start; i < end; i++) {
        if (is_prime(i) == 1) {
            prev_value = last_value;
            last_value = i;
        }
        if (counter >= END_PROCEDURE) {
            return 0;
        }
    }
    if (counter < END_PROCEDURE) {
        printf("%d\n", -1);
        return 0;
    }
    if (prev_value == 0) {
        printf("%d\n", -1);
        return 0;
    }
    return 0;
}