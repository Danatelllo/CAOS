#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>

enum { SIZE = 1000 };

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    char buf[SIZE];
    char *data = "2011/09/01";
    int size_data = strlen(data);
    int flag = 0;
    time_t first = 0;
    time_t second = 0;
    while (fscanf(f, "%s", buf) == 1 &&
           fscanf(f, "%s", buf + strlen(data) + 1) == 1) {
        buf[size_data] = ' ';
        struct tm tmp;
        tmp.tm_isdst = -1;
        strptime(buf, "%Y/%m/%d %H:%M:%S", &tmp);
        first = mktime(&tmp);
        if (flag == 1) {
            printf("%ld\n", first - second);
        }
        flag = 1;
        second = first;
    }
    return 0;
}