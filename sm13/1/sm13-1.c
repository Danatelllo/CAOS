#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;

void handler(int sig) {
    printf("%d\n", counter);
    fflush(stdout);
    ++counter;
    if (counter == 4) {
        exit(0);
    }
}

int main() {
    sigset_t sigint;
    sigemptyset(&sigint);
    sigaddset(&sigint, SIGINT);
    sigprocmask(SIG_BLOCK, &sigint, NULL);
    struct sigaction sa = {
            .sa_handler = handler,
    };
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &sigint, NULL);
    while (1) {
        pause();
    }
}