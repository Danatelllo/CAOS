#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int separate(int fd_in, int fd_out_even, int fd_out_odd) {
    if (fd_in < 0 || fd_out_even < 0 || fd_out_odd < 0) {
        return -1;
    }
    off_t filesize = lseek(fd_in, 0, SEEK_END);
    lseek(fd_in, 0, SEEK_SET);
    int *file = calloc(filesize, 1);
    if (!file) {
        return -1;
    }
    ssize_t ans = read(fd_in, file, filesize);
    if (ans < 0) {
        free(file);
        return -1;
    }
    int j_even = 0;
    int k_odd = 0;
    for (int i = 0; i < (int)filesize / (int)sizeof(int); ++i) {
        if (file[i] % 2 == 0) {
            ++j_even;
        } else {
            ++k_odd;
        }
    }
    int b1 = 2;
    for (int i = 0; i < (int)filesize / (int)sizeof(int); ++i) {
        if (file[i] % 2 == 0) {
            b1 = file[i];
            if (write(fd_out_even, &b1, sizeof(b1)) < 0) {
                free(file);
                return -1;
            }
            ++j_even;
        } else {
            b1 = file[i];
            if (write(fd_out_odd, &b1, sizeof(b1)) < 0) {
                free(file);
                return -1;
            }
        }
    }
    if (file) {
        free(file);
    }
    return 0;
}
