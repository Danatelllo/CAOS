#include <alloca.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#pragma GCC optimize("O0")

enum {
    SIZE_OF_INT = 4,
    SIZE_OF_POINTER = 4,
    SIZE_OF_DOUBLE = 8,
    PLACE_FOR_SIGNATURE = 3,
    PLACE_FOR_LIBRARY = 1,
    PLACE_FOR_NAME_OF_FUNCTION = 2,
    TYPE_OF_RETURN = 0,
    OFFSET_FOR_SIGNATURE = 3,
    DECIMAL = 10,
    START_ARGS = 4
};

double d_value;

void helper(char *signature, int argc, char *argv[]) {
    void *handler = dlopen(argv[PLACE_FOR_LIBRARY], RTLD_LAZY);
    void *ver = dlsym(handler, argv[PLACE_FOR_NAME_OF_FUNCTION]);
    int i_value;
    char *s_value;
    char *signature_for_counter = signature;
    ++signature_for_counter;
    int all_size = 0;
    for (char *i = signature_for_counter; *i != '\0'; ++i) {
        if (*i == 'i') {
            all_size += SIZE_OF_INT;
        } else if (*i == 'd') {
            all_size += SIZE_OF_DOUBLE;
        } else if (*i == 's') {
            all_size += SIZE_OF_POINTER;
        }
    }
    void *ptr = alloca(all_size);
    for (int i = START_ARGS; i < argc; ++i) {
        if (signature[i - OFFSET_FOR_SIGNATURE] == 'i') {
            i_value = strtol(argv[i], NULL, DECIMAL);
            *((int *)ptr) = i_value;
            ptr += SIZE_OF_INT;
        }
        if (signature[i - OFFSET_FOR_SIGNATURE] == 's') {
            *((char **)ptr) = argv[i];
            ptr += SIZE_OF_POINTER;
        }
        if (signature[i - OFFSET_FOR_SIGNATURE] == 'd') {
            d_value = strtod(argv[i], NULL);
            *((double *)ptr) = d_value;
            ptr += SIZE_OF_DOUBLE;
        }
    }

    if (signature[TYPE_OF_RETURN] == 'i') {
        __asm__("call %%ecx\n\t" : "=a"(i_value) : "c"(ver));
        printf("%d\n", i_value);
    }
    if (signature[TYPE_OF_RETURN] == 's') {
        __asm("call %%ecx\n\t" : "=a"(s_value) : "c"(ver));
        printf("%s\n", s_value);
    }
    if (signature[TYPE_OF_RETURN] == 'd') {
        __asm__("call %%ecx\n\t"
                "fstl d_value" ::"c"(ver));
    }
    if (signature[TYPE_OF_RETURN] == 'v') {
        __asm__("call %%ecx" ::"c"(ver));
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    char *signature = argv[PLACE_FOR_SIGNATURE];
    helper(signature, argc, argv);
    if (signature[TYPE_OF_RETURN] == 'd') {
        printf("%.10g\n", d_value);
    }
    return 0;
}
