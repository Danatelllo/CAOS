#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    int number;
    pid_t result = fork();
    if (result == 0) {
        while (scanf("%d", &number) == 1) {
            result = fork();
            if (result > 0) {
                waitpid(result, &status, 0);
                if (WEXITSTATUS(status) != 1) {
                    printf("%d\n", number);
                    return 0;
                } else {
                    return 1;
                }
            } else if (result < 0) {
                printf("%d\n", -1);
                return 1;
            }
        }
    } else if (result > 0) {
        waitpid(result, &status, 0);
    }
    return 0;
}
