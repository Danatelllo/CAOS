#include "sys/wait.h"
#include <bits/stdint-intn.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    (void)argc;
    ssize_t result;
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }
    pid_t child = fork();
    if (child < 0) {
        perror("bad fork");
        return 1;
    }
    if (child == 0) {
        int32_t sum1 = 0;
        int32_t num = 0;
        int child1_fd = open(argv[1], R_OK);
        while (read(child1_fd, &num, sizeof(num)) > 0) {
            sum1 += num;
        }
        result = write(fd[1], &sum1, sizeof(sum1));
        (void)result;
        return 0;
    }
    int fd2[2];
    (void)argc;
    if (pipe(fd2) < 0) {
        perror("pipe");
        return 1;
    }
    pid_t child2 = fork();
    if (child2 < 0) {
        perror("bad fork");
        return 1;
    }
    if (child2 == 0) {
        int32_t sum2 = 0;
        int32_t num;
        int child2_fd = open(argv[2], R_OK);
        while (read(child2_fd, &num, sizeof(num)) > 0) {
            sum2 += num;
        }
        result = write(fd2[1], &sum2, sizeof(sum2));
        (void)result;
        return 0;
    }
    wait(NULL);
    wait(NULL);
    int32_t sum = 0;
    int32_t num;
    result = read(fd2[0], &num, sizeof(num));
    (void)result;
    printf("%" PRIi32 "\n", num);
    sum += num;
    result = read(fd[0], &num, sizeof(num));
    printf("%" PRIi32 "\n", num);
    sum += num;
    printf("%" PRIi32 "\n", sum);
    (void)result;
    return 0;
}
