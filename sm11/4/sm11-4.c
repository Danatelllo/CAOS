#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { TEN = 10 };

void concat(const char *s1, const char *s2, char *ans) {
    size_t size_s1 = strlen(s1);
    size_t size_s2 = strlen(s2);
    for (size_t j = 0; j < size_s1; ++j) {
        ans[j] = s1[j];
    }
    ans[size_s1] = '/';
    for (size_t j = size_s1 + 1; j < size_s1 + size_s2 + 1; ++j) {
        ans[j] = s2[j - size_s1 - 1];
    }
    ans[size_s1 + size_s2 + 1] = '\0';
}

int main(int argc, char *argv[]) {
    char name[PATH_MAX];
    int pid = getpid();
    int k = 0;
    while (pid != 0) {
        name[k] = (char)(pid % TEN) + '0';
        pid /= TEN;
        ++k;
    }
    name[k] = '\0';
    const char *cur_path = getenv("XDG_RUNTIME_DIR");
    const char *cur_path2 = getenv("TMPDIR");
    char ans[PATH_MAX];
    ssize_t result;
    if (cur_path != NULL) {
        concat(cur_path, name, ans);
    } else if (cur_path2 != NULL) {
        concat(cur_path2, name, ans);
    } else {
        cur_path = "/tmp";
        concat(cur_path, name, ans);
    }
    int fd = open(ans, O_TRUNC | O_CREAT | O_RDWR, 0755);
    int j = 1;
    char *python_shebang = "#!/usr/bin/python3\n";
    char *print = "print";
    char *import = "import os\n";
    char *remove = "os.remove";
    result = write(fd, python_shebang, strlen(python_shebang));
    result = write(fd, import, strlen(import));
    result = write(fd, print, strlen(print));
    char b = '(';
    result = write(fd, &b, 1);
    while (j < argc) {
        int i = 0;
        while ((size_t)i < strlen(argv[j])) {
            b = argv[j][i];
            result = write(fd, &b, 1);
            ++i;
        }
        if (j != argc - 1) {
            b = '*';
            result = write(fd, &b, 1);
        }
        ++j;
    }
    b = ')';
    result = write(fd, &b, 1);
    b = '\n';
    result = write(fd, &b, 1);
    result = write(fd, remove, strlen(remove));
    b = '(';
    result = write(fd, &b, 1);
    b = '"';
    result = write(fd, &b, 1);
    result = write(fd, ans, strlen(ans));
    b = '"';
    result = write(fd, &b, 1);
    b = ')';

    result = write(fd, &b, 1);
    close(fd);
    (void)result;

    execl(ans, argv[0], NULL);
    perror("something_bad");
    return 0;
}
