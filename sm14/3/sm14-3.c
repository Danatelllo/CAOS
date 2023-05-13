#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int create_listener(char *service) {
    struct addrinfo *res = NULL;
    int gai_err;
    struct addrinfo hint = {
            .ai_family = AF_UNSPEC,
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
        if (bind(sock, ai->ai_addr, ai->ai_addrlen) < 0) {
            perror("bind");
            close(sock);
            sock = -1;
            continue;
        }
        if (listen(sock, SOMAXCONN) < 0) {
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
    int sock = create_listener(argv[1]);
    if (sock < 0) {
        return 1;
    }
    int reuseaddr = 1;
    ssize_t result = 0;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
    int counter = 0;
    int cur_number = 1;
    while (cur_number != 0) {
        int connection = accept(sock, NULL, NULL);
        result = read(connection, &cur_number, sizeof(cur_number));
        close(connection);
        if (result < 0) {
            break;
        }
        cur_number = ntohl(cur_number);
        counter += cur_number;
    }
    printf("%d\n", counter);
    close(sock);
    return 0;
}