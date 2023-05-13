#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    pid_t result = fork();
    if (result == 0) {
        result = fork();
        if (result) {
            printf("%d%s", 3, " ");
        } else {
            waitpid(result, &status, 0);
            printf("%d%s", 2, " ");
        }
    } else {
        waitpid(result, &status, 0);
        printf("%d\n", 1);
    }
    return 0;
}
