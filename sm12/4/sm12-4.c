#include "sys/wait.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    int fd2[2];
    if (argc == 1) {
        return 0;
    }
    if (pipe(fd) < 0) {
        _exit(1);
    }
    pid_t child;
    pid_t *children = calloc(argc + 1, sizeof(child));
    if (children == NULL) {
        _exit(1);
    }
    int cur = 1;
    while (cur < argc) {
        close(fd[1]);
        if (pipe(fd2) < 0) {
            int counter = 1;
            while (counter < cur) {
                kill(children[counter], SIGKILL);
                ++counter;
            }
            counter = 1;
            while (counter < cur) {
                wait(NULL);
                ++counter;
            }
            _exit(1);
        }
        child = fork();
        if (child < 0) {
            int counter = 1;
            while (counter < cur) {
                kill(children[counter], SIGKILL);
                ++counter;
            }
            counter = 1;
            while (counter < cur) {
                wait(NULL);
                ++counter;
            }
            _exit(1);
        }
        children[cur] = child;
        if (child == 0) {
            if (cur != 1) {
                dup2(fd[0], STDIN_FILENO);
            }
            close(fd[0]);
            if (cur != argc - 1) {
                dup2(fd2[1], STDOUT_FILENO);
            }
            close(fd2[1]);
            close(fd2[0]);
            execlp(argv[cur], argv[cur], NULL);
            _exit(1);
        }
        close(fd[0]);
        fd[0] = fd2[0];
        fd[1] = fd2[1];
        ++cur;
    }
    close(fd[0]);
    close(fd[1]);
    if (children) {
        free(children);
    }
    int counter = 1;
    while (counter < argc) {
        wait(NULL);
        ++counter;
    }
    return 0;
}
