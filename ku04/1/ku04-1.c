#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat buff2;
    struct stat buff;
    for (int j = 1; j < argc; ++j) {
        int result = lstat(argv[j], &buff);
        if (result == -1) {
            printf("%s%s%s\n", argv[j], " ", "(missing)");
            continue;
        }
        if (S_ISLNK(buff.st_mode)) {
            result = stat(argv[j], &buff2);
            if (result == -1) {
                printf("%s%s%s\n", argv[j], " ", "(broken symlink)");
                continue;
            }
        }
        printf("%s\n", argv[j]);
    }
    return 0;
}
