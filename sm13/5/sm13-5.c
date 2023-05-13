#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <unistd.h>
#include <wait.h>

void make(int order, int number, FILE *r, FILE *w, int sfd, int neigh,
          int end) {
    ssize_t s;
    struct signalfd_siginfo info_sig;
    for (;;) {
        s = read(sfd, &info_sig, sizeof(info_sig));
        if (info_sig.ssi_signo == SIGUSR1 && order == number && order == 1) {
            s = fscanf(r, "%d", &neigh);
            (void)s;
            printf("%d%s%d\n", order, " ", number);
            fflush(stdout);
            ++number;
            fprintf(w, "%d\n", number);
            fflush(w);
            kill(neigh, SIGUSR1);
            if (number >= end) {
                _exit(0);
            }
        } else if (info_sig.ssi_signo == SIGUSR1) {
            s = fscanf(r, "%d", &number);
            (void)s;
            printf("%d%s%d\n", order, " ", number);
            fflush(stdout);
            ++number;
            fprintf(w, "%d\n", number);
            fflush(w);
            kill(neigh, SIGUSR1);
            if (number >= end) {
                _exit(0);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }
    int end = atoi(argv[1]);
    if (end == 1) {
        printf("%d%s%d\n", 1, " ", 1);
        fflush(stdout);
        return 0;
    }
    sigset_t mask;
    int sfd;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    sfd = signalfd(-1, &mask, 0);

    pid_t child = fork();
    if (child == 0) {
        int counter = 1;
        FILE *r = fdopen(fd[0], "r");
        FILE *w = fdopen(fd[1], "w");
        pid_t neigh = child;
        make(1, counter, r, w, sfd, neigh, end);
        return 0;
    }
    pid_t child2 = fork();
    if (child2 == 0) {
        int counter = 2;
        FILE *r = fdopen(fd[0], "r");
        FILE *w = fdopen(fd[1], "w");
        pid_t neigh = child;
        make(2, counter, r, w, sfd, neigh, end);
        return 0;
    }
    FILE *w = fdopen(fd[1], "w");
    fprintf(w, "%d\n", child2);
    fflush(w);
    close(fd[0]);
    close(fd[1]);
    kill(child, SIGUSR1);
    wait(NULL);
    wait(NULL);
    return 0;
}