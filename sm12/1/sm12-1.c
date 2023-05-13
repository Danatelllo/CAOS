#include "sys/wait.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    (void)argc;
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }
    pid_t child = fork();
    if (child == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
    } else if (child > 0) {
        pid_t child2 = fork();
        close(fd[1]);
        if (child2 == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execlp(argv[2], argv[2], NULL);
        }
        close(fd[0]);
        wait(NULL);
        wait(NULL);
        return 0;
    }
}
