int mystrcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        unsigned char first;
        unsigned char second;
        first = (unsigned char)*str1;
        second = (unsigned char)*str2;
        if (first < second) {
            return -1;
        }
        if (second < first) {
            return 1;
        }
        ++str1;
        ++str2;
    }
    if (*str1 == '\0' && *str2 != '\0') {
        return -1;
    }
    if (*str1 != '\0' && *str2 == '\0') {
        return 1;
    }
    return 0;
}
