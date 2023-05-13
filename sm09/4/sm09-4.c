//#include <dlfcn.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char *argv[]) {
//    (void)argc;
//    void *handler;
//    double mean;
//    handler = dlopen("libm.so.6", RTLD_LAZY);
//    double (*ver)(double) = dlsym(handler, argv[1]);
//    while (scanf("%lg", &mean) == 1) {
//        printf("%.10g\n", ver(mean));
//    }
//    return 0;
//}