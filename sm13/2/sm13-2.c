#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t counter = 1;

void handler_neg(int sig) {
    counter = 1;
}

void handler_square(int sig) {
    counter = 2;
}

int main() {
    sigset_t sigint;
    sigemptyset(&sigint);
    sigaddset(&sigint, SIGUSR1);
    sigaddset(&sigint, SIGUSR2);

    struct sigaction neg = {
            .sa_handler = handler_neg,
            .sa_flags = SA_RESTART,
    };
    struct sigaction square = {
            .sa_handler = handler_square,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &neg, NULL);
    sigaction(SIGUSR2, &square, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    long long num;
    while (scanf("%lld", &num) != EOF) {
        if (counter == 1) {
            printf("%lld\n", -num);
            fflush(stdout);
        } else {
            printf("%lld\n", num * num);
            fflush(stdout);
        }
    }
    return 0;
}