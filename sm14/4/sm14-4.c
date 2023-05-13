#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

enum { COUNTER = 7 };

volatile sig_atomic_t is_end = 0;

struct DynArray {
    size_t size;
    size_t capacity;
    int *ptr;
} array = {};

void append(struct DynArray *arr, int value) {
    if (arr->size + 1 > arr->capacity) {
        size_t newcap = 2 * (arr->capacity + 1);
        int *tmp = realloc(arr->ptr, newcap * sizeof(*tmp));
        arr->ptr = tmp;
        arr->capacity = newcap;
    }
    arr->ptr[arr->size++] = value;
}

void handler(int sig) {
    is_end = 1;
}

void shoot_zombie(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        ;
    }
}

enum { TRUE = 1, SIZE_BUF = 1025, SIZE_HOST = 1024 };

int get_sock(char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_INET6,
            .ai_socktype = SOCK_STREAM,
            .ai_flags = AI_PASSIVE,
    };
    gai_err = getaddrinfo(NULL, service, &hint, &res);
    if (gai_err != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        if (sock < 0) {
            perror("socket");
            continue;
        }
        int reuseaddr = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
                   sizeof(reuseaddr));
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        if (listen(sock, COUNTER) < 0) {
            perror("listen");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res);
    return sock;
}

int main(int argc, char *argv[]) {
    struct sigaction end_program = {
            .sa_handler = handler,
    };
    sigaction(SIGTERM, &end_program, NULL);
    struct sigaction kill_zombie = {
            .sa_handler = shoot_zombie,
            .sa_flags = SA_RESTART,
    };
    sigaction(SIGCHLD, &kill_zombie, NULL);
    int sock = get_sock(argv[1]);
    if (sock < 0) {
        return 1;
    }
    struct DynArray childs;
    childs.capacity = 0;
    childs.size = 0;
    childs.ptr = NULL;
    while (TRUE) {
        fflush(stdout);
        if (is_end == 1) {
            for (size_t j = 0; j < childs.size; ++j) {
                kill(childs.ptr[j], SIGTERM);
                printf("%d\n", childs.ptr[j]);
            }
            fflush(stdout);
            break;
        }
        int connection = accept(sock, NULL, NULL);
        if (is_end == 1) {
            for (size_t j = 0; j < childs.size; ++j) {
                kill(childs.ptr[j], SIGTERM);
            }
            close(connection);
            break;
        }
        while (waitpid(-1, NULL, WNOHANG) > 0) {
            ;
        }
        pid_t child = fork();
        if (child == 0) {
            dup2(connection, STDOUT_FILENO);
            dup2(connection, STDIN_FILENO);
            close(connection);
            close(sock);
            execvp(argv[2], &argv[2]);
            _exit(0);
        }
        fflush(stdout);
        append(&childs, child);
        close(connection);
    }
    close(sock);
    if (childs.ptr != NULL) {
        free(childs.ptr);
    }
    return 0;
}