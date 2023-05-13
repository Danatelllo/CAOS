#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    (void)argc;
    pid_t child = fork();
    if (child == 0) {
        int output = open(argv[3], O_TRUNC | O_CREAT | O_RDWR, 0666);
        int input = open(argv[2], O_RDONLY);
        dup2(output, STDOUT_FILENO);
        close(output);
        dup2(input, STDIN_FILENO);
        close(input);
        execlp(argv[1], argv[1], NULL);
    }
    int status;
    wait(&status);
    return 0;
}
