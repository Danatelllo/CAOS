#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t sig1 = 0;
volatile sig_atomic_t sig2 = 0;
volatile sig_atomic_t print = 0;
volatile sig_atomic_t end = 0;

void handler_sig1(int sig) {
    print = 1;
    ++sig1;
}

void handler_sig2(int sig) {
    ++sig2;
}

void handler_sigterm(int sig) {
    end = 1;
}

int main() {
    sigset_t sig, old;
    sigemptyset(&sig);
    sigaddset(&sig, SIGUSR1);
    sigaddset(&sig, SIGUSR2);
    sigaddset(&sig, SIGTERM);
    sigprocmask(SIG_BLOCK, &sig, &old);
    sigdelset(&old, SIGUSR1);
    sigdelset(&old, SIGUSR2);
    sigdelset(&old, SIGTERM);
    struct sigaction sigusr1 = {
            .sa_handler = handler_sig1,
            .sa_flags = SA_RESTART,
    };
    struct sigaction sigusr2 = {
            .sa_handler = handler_sig2,
            .sa_flags = SA_RESTART,
    };
    struct sigaction sigterm = {
            .sa_handler = handler_sigterm,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &sigusr1, NULL);
    sigaction(SIGUSR2, &sigusr2, NULL);
    sigaction(SIGTERM, &sigterm, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        if (print == 1) {
            print = 0;
            printf("%d\n", sig1 - 1);
            fflush(stdout);
            printf("%d\n", sig2);
            fflush(stdout);
        }
        if (end == 1) {
            exit(0);
        }
        sigsuspend(&old);
    }
    return 0;
}