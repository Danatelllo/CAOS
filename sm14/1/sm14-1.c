#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

enum { SIZE_OF_BUF = 1024 };

int main(int argc, char *argv[]) {
    int error;
    char node[SIZE_OF_BUF];
    char service[SIZE_OF_BUF];
    char buf[SIZE_OF_BUF];
    uint32_t ans_ip = 0;
    uint32_t ans_port = 0;
    int was_mi = 0;
    struct in_addr ip_addr;
    struct addrinfo *info = NULL;
    struct addrinfo hint = {
            .ai_family = AF_INET,
    };
    while (scanf("%s%s", node, service) != EOF) {
        error = getaddrinfo(node, service, &hint, &info);
        if (error != 0) {
            fprintf(stdout, "%s\n", gai_strerror(error));
            continue;
        }
        for (struct addrinfo *j = info; j; j = j->ai_next) {
            struct sockaddr_in *inet;
            inet = (struct sockaddr_in *)j->ai_addr;
            uint32_t cur_port = ntohs(inet->sin_port);
            inet_aton(
                    inet_ntop(j->ai_family, &inet->sin_addr, buf, sizeof(buf)),
                    &ip_addr);
            uint32_t cur_ip = ntohl(ip_addr.s_addr);
            if (was_mi == 0) {
                ans_ip = cur_ip;
                was_mi = 1;
                ans_port = cur_port;
            }
            if (cur_ip < ans_ip) {
                ans_ip = cur_ip;
                ans_port = cur_port;
            }
        }
        ip_addr.s_addr = ntohl(ans_ip);
        printf("%s", inet_ntoa(ip_addr));
        printf("%s", ":");
        printf("%u\n", ans_port);
        ans_ip = 0;
        ans_port = 0;
        was_mi = 0;
        freeaddrinfo(info);
    }
}