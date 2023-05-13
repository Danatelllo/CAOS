#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

volatile sig_atomic_t is_end = 0;

void handler(int sig) {
    is_end = 1;
}

enum { TRUE = 1, SIZE_BUF = 1025, SIZE_HOST = 1024 };

int main(int argc, char *argv[]) {
    struct sigaction end_program = {
            .sa_handler = handler,
    };
    sigaction(SIGTERM, &end_program, NULL);
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_INET6,
            .ai_socktype = SOCK_DGRAM,
    };
    gai_err = getaddrinfo(NULL, argv[1], &hint, &res);
    if (gai_err != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(gai_err));
        return -1;
    }
    int sock = -1;
    struct addrinfo *host;
    struct sockaddr_in6 *inet6;
    for (struct addrinfo *ai = res; ai; ai = ai->ai_next) {
        sock = socket(ai->ai_family, ai->ai_socktype, 0);
        host = ai;
        inet6 = (struct sockaddr_in6 *)ai->ai_addr;
        if (sock < 0) {
            perror("socket");
            continue;
        }
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    if (sock < 0) {
        return 1;
    }
    char buf_for_host[SIZE_HOST];
    char buffer[SIZE_BUF];
    struct sockaddr_in6 data;
    socklen_t length = sizeof(data);
    ssize_t result = 0;
    while (TRUE) {
        result = recvfrom(sock, buffer, sizeof(buffer), 0,
                          (struct sockaddr *)&data, &length);
        if (is_end == 1) {
            break;
        }
        if (res > 0) {
            printf("%c%s%c%d", '[',
                   inet_ntop(host->ai_family, &inet6->sin6_addr, buf_for_host,
                             sizeof(buf_for_host)),
                   ':', ntohs(data.sin6_port));
            printf("%s", "] ");
            for (size_t j = 0; j < result; ++j) {
                printf("%c", buffer[j]);
            }
            printf("\n");
            fflush(stdout);
        }
    }
    close(sock);
    freeaddrinfo(res);
    return 0;
}