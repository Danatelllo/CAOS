#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

enum { CLOSE = 1, NOT_OPEN = 0, OPEN = 2, READ_BUFF_SIZE = 16, TRUE = 1 };

volatile sig_atomic_t cur_file = 0;
volatile sig_atomic_t begin_of_end = 0;
volatile sig_atomic_t must_read = 0;

int get_offset_for_info() {
    return 2 * cur_file + 1;
}

int get_offset_for_file() {
    return 2 * cur_file;
}

void handler_read(int sig) {
    cur_file = sig - SIGRTMIN;
    must_read = 1;
}

void handler_end(int sig) {
    begin_of_end = 1;
}

int main(int argc, char *argv[]) {
    sigset_t sig_block, old;
    sigemptyset(&sig_block);
    sigaddset(&sig_block, SIGTERM);
    char buf[READ_BUFF_SIZE];
    int64_t tmp;
    int64_t *sums = calloc(argc, sizeof(tmp));
    int *descriptors = calloc(2 * argc, sizeof(argc));
    if (sums == NULL || descriptors == NULL) {
        return 1;
    }
    struct sigaction read_action = {
            .sa_handler = handler_read,
            .sa_flags = 0,
    };
    struct sigaction end_action = {
            .sa_handler = handler_end,
            .sa_flags = 0,
    };
    sigaction(SIGTERM, &end_action, NULL);
    for (int j = 0; j < argc; ++j) {
        sigaction(SIGRTMIN + j, &read_action, NULL);
        sigaddset(&sig_block, SIGRTMIN + j);
    }
    sigprocmask(SIG_BLOCK, &sig_block, &old);
    sigdelset(&old, SIGTERM);
    for (int j = 0; j < argc; ++j) {
        sigdelset(&old, SIGRTMIN + j);
    }
    printf("%d\n", getpid());
    fflush(stdout);
    while (TRUE) {
        if (begin_of_end != 1 && must_read != 1) {
            sigsuspend(&old);
        }
        if (begin_of_end == 1) {
            for (int j = 0; j < argc - 1; ++j) {
                printf("%" SCNd64 "\n", sums[j]);
                fflush(stdout);
            }
            break;
        }
        if (must_read == 1) {
            must_read = 0;
            ssize_t res = 1;
            if (descriptors[get_offset_for_info()] == NOT_OPEN) {
                descriptors[get_offset_for_file()] =
                        open(argv[cur_file + 1], O_RDONLY);
                descriptors[get_offset_for_info()] = OPEN;
            }
            if (descriptors[get_offset_for_info()] == OPEN) {
                while (res > 0) {
                    sigprocmask(SIG_UNBLOCK, &sig_block, NULL);
                    res = read(descriptors[get_offset_for_file()], buf,
                               READ_BUFF_SIZE);
                    sigprocmask(SIG_BLOCK, &sig_block, NULL);
                    if (begin_of_end == 1 || must_read == 1) {
                        break;
                    }
                    if (res == READ_BUFF_SIZE) {
                        int64_t var;
                        sscanf(buf, "%" SCNd64, &var);
                        sums[cur_file] += var;
                    }
                }
            }
        }
    }
    free(sums);
    free(descriptors);
    return 0;
}