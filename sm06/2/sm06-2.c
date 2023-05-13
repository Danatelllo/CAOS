#include <stdio.h>

int main()
{
    int infotype, a, b, c, d;
    int model = 240;
    int family = 256 + 512 + 1024 + 2048;
    int model_id = 1048575;

    infotype = 1;
        __asm__("cpuid"
                : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
                : "0" (infotype));
        printf("%s", "family=");
        int family_id = ((a & family) >> 8);
        printf("%d ", family_id);
        printf("%s", "model=");

        if (family_id == 6 || family_id == 15) {
            printf("%d ", ((a & model) >> 4) + (((a & model_id) >> 12)));
        } else {
            printf("%d ", ((a & model) >> 4));
        }
        printf("ecx=0x%x edx=0x%x", c, d);
        printf("\n");

    return 0;
}
