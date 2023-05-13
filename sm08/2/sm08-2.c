#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <read_file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

enum { START_SIZE_OF_BUF = 4096 };

struct FileContent read_file(int fd) {
    struct FileContent content;
    char ch;
    char *buf = calloc(START_SIZE_OF_BUF, sizeof(ch));
    if (buf == NULL) {
        content.data = NULL;
        content.size = -1;
        return content;
    }
    content.data = calloc(1, sizeof(ch));
    if (content.data == NULL) {
        free(buf);
        content.data = NULL;
        content.size = -1;
        return content;
    }
    ssize_t result;
    content.size = 0;
    while ((result = read(fd, buf, START_SIZE_OF_BUF)) > 0) {

        char *tmp = realloc(content.data, result + content.size + 1);
        if (tmp == NULL) {
            free(buf);
            free(content.data);
            content.data = NULL;
            content.size = -1;
            return content;
        }
        content.data = tmp;
        for (size_t j = 0; j < result; ++j) {
            content.data[content.size + j] = buf[j];
        }
        content.size += result;
    }
    if (result < 0) {
        free(content.data);
        free(buf);
        content.data = NULL;
        content.size = -1;
        return content;
    }
    content.data[content.size] = '\0';
    if (buf) {
        free(buf);
    }
    return content;
}
