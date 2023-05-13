#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void strip_spaces(char *buf) {
    char *str = buf;
    char *str_for_letters = buf;
    int was_space = 0;
    int was_letter = 0;
    while (*str != '\0') {
        if (isspace(*str) && was_space == 0) {
            if (was_letter == 1) {
                *str_for_letters = ' ';
                was_space = 1;
                ++str_for_letters;
            }
        } else if (!isspace(*str)) {
            was_letter = 1;
            *str_for_letters = *str;
            ++str_for_letters;
            was_space = 0;
        }
        ++str;
    }
    if (str_for_letters != buf && *(str_for_letters - 1) == ' ') {
        --str_for_letters;
    }
    *str_for_letters = '\0';
}


size_t next_word(char *str) {
    size_t size = 0;
    while (!isspace(*str) && *str != '\0') {
        ++size;
        ++str;
    }
    if (*str != '\0') {
        *str = '\0';
    }
    return size + 1;
}

size_t counter_of_gap(const char *str) {
    size_t size = 0;
    size_t j = 0;
    while (str[j] != '\0') {
        ++j;
        if (str[j]  == ' ') {
            ++size;
        }
    }
    return size;
}

int mysystem(const char *cmd) {
    size_t sz = snprintf(NULL, 0, "%s", cmd);
    char *buf = calloc(sz + 1, 1);
    snprintf(buf, sz + 1, "%s", cmd);
    strip_spaces(buf);
    if (!strlen(buf)) {
        return -1;
    }
    size_t counter_of_words = counter_of_gap(buf) + 1;
    char **list = calloc(counter_of_words + 1, sizeof(char*));
    char *tmp = buf;
    size_t cur_pointer = 0;
    for (size_t j = 0; j < counter_of_words; ++j) {
        list[j] = calloc(1, sizeof(char*));
        if (j == 0) {
            list[j] = &buf[0];
        } else {
            cur_pointer += next_word(tmp + cur_pointer);
            list[j] = &buf[cur_pointer];
        }
    }
    for (size_t j = 0; j < counter_of_words; ++j) {
        printf("%s\n", list[j]);
    }

//    pid_t child = fork();
//    if (child < 0) {
//        return -1;
//    }
//    if (child > 0) {
//
//    }
//    printf("%s", buf);




//    for (size_t j = 0; j < counter_of_words; ++j) {
//        free(list[j]);
//    }
//    free(list);/*/
//    free(buf);
//    free(buf);
    if (buf != NULL) {
        free(buf);
    }
//    for (size_t j = 0; j < counter_of_words; ++j) {
//        if (list[j] != NULL) {
//            free(list[j]);
//        }
//    }
    if (list != NULL) {
        printf("%s\n", "adil hui");
        free(list);
    }
    return 1;

//    execv(buf[0], buf + );
}



int main() {
    char *s = "a            b     22     ac         ca          asdfasfsd \tsdf ";
    mysystem(s);
}
