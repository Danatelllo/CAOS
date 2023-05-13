//#include <dlfcn.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char *argv[]) {
////    (void)argc;
////    void *handler;
////    double mean;
////    int i_value;
////    char *s_value;
////    double d_value;
////    handler = dlopen(argv[1], RTLD_LAZY);
////    double (*ver)(double) = dlsym(handler, argv[2]);
////    char *signature = argv[3];
////
////    for (int i = 4; i < argc; ++i) {
////        if (*signature == 'i') {
////            sscanf(argv[i], "%d", &i_value);
////            __asm__("push %%eax\n\t"
////                    : "a"(i_value));
////        }
////    }
//    for (int i = 1; i < argc; ++i) {
//        printf("%s\n", argv[i]);
//    }
//    return 0;
//}
