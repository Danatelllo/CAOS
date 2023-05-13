#include <bits/stdint-intn.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void find_keys(int32_t *root_node, int fh) {
    if (root_node[2] != 0) {
        int32_t current_node[3];
        lseek(fh, root_node[2] * sizeof(current_node), SEEK_SET);
        ssize_t result = read(fh, current_node, sizeof(current_node));
        if (result < 0) {
            printf("\n");
            exit(1);
        }
        if (current_node[1] != 0 || current_node[2] != 0) {
            find_keys(current_node, fh);
        } else {
            printf("%" PRIi32 "\n", current_node[0]);
        }
    }
    if (root_node[1] != 0 || root_node[2] != 0) {
        printf("%" PRIi32 "\n", root_node[0]);
    }
    if (root_node[1] != 0) {
        int32_t current_node[3];
        lseek(fh, root_node[1] * sizeof(current_node), SEEK_SET);
        ssize_t result = read(fh, current_node, sizeof(current_node));
        if (result < 0) {
            printf("\n");
            exit(1);
        }
        if (current_node[1] != 0 || current_node[2] != 0) {
            find_keys(current_node, fh);
        } else {
            printf("%" PRIi32 "\n", current_node[0]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\n");
        exit(1);
    }
    int32_t current_node[3];
    ssize_t result;
    int fh = open(argv[1], O_RDONLY);
    if (fh == -1) {
        printf("\n");
        exit(1);
    }
    result = read(fh, current_node, sizeof(current_node));
    if (result < 0) {
        printf("\n");
        exit(1);
    }

    find_keys(current_node, fh);
}
