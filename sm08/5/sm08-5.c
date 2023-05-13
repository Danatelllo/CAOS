#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *concat(char *s1, char *s2) {

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = calloc(len1 + len2 + 1, sizeof(char));

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}

char *make_new_string(char *s1, char *s2) {
    size_t len1 = strlen(s1);
    if (len1 && s1[len1 - 1] == '/') {
        return concat(s1, s2);
    }
    char *tmp = concat(s1, "/");
    char *result = concat(tmp, s2);
    if (tmp != NULL) {
        free(tmp);
    }
    return result;
}

void dfs(long size, int deep, char *cur_path, char *cur_name) {
    if (deep == 4) {
        return;
    }
    DIR *path = opendir(cur_path);
    if (path == NULL) {
        return;
    }
    struct dirent *dir;
    while ((dir = readdir(path)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            char *new_path = make_new_string(cur_path, dir->d_name);
            char *new_name = make_new_string(cur_name, dir->d_name);
            if (dir->d_type == DT_DIR) {
                if (deep == 0) {
                    dfs(size, deep + 1, new_path, dir->d_name);
                } else {
                    dfs(size, deep + 1, new_path, new_name);
                }
            } else if (dir->d_type == DT_REG) {
                struct stat buff;
                stat(new_path, &buff);
                if (buff.st_size <= size && access(new_path, R_OK) == 0) {
                    if (deep != 0) {
                        printf("%s\n", new_name);
                    } else {
                        printf("%s\n", dir->d_name);
                    }
                }
            }
            if (new_name) {
                free(new_name);
            }
            if (new_path) {
                free(new_path);
            }
        }
    }
    closedir(path);
}

int main(int argc, char *argv[]) {
    char *start = "";
    (void)argc;
    long size;
    char *dir_name;
    dir_name = argv[1];
    char *end;
    size = strtol(argv[2], &end, 10);
    dfs(size, 0, dir_name, start);
    return 0;
}
