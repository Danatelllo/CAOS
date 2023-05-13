#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

enum { ALWAYS_TRUE = 1 };

int create_connection(char *node, char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_UNSPEC,
            .ai_socktype = SOCK_STREAM,
    };
    gai_err = getaddrinfo(node, service, &hint, &res);
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
        if (connect(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("connect");
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
    int sock = create_connection(argv[1], argv[2]);
    if (sock < 0) {
        return 1;
    }
    int copy_sock = 0;
    dup2(sock, copy_sock);
    FILE *channel_write = fdopen(sock, "w");
    FILE *channel_read = fdopen(copy_sock, "r");
    fprintf(channel_write, "%s\n", argv[3]);
    fflush(channel_write);
    unsigned long long answer = 0;
    int result = fscanf(channel_read, "%llu", &answer);
    if (result < 0) {
        _exit(0);
    }
    unsigned long long counter = 0;
    while (counter <= answer) {
        fprintf(channel_write, "%llu\n", counter);
        ++counter;
    }
    fflush(channel_write);
    result = fscanf(channel_read, "%llu", &answer);
    if (result < 0) {
        _exit(0);
    }
    printf("%llu\n", answer);
    fflush(stdout);
    close(sock);
    close(copy_sock);
    return 0;
}