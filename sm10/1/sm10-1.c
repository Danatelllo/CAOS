#include <alloca.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    SIGN = 2147483648,
    EXP = 255,
    FRAC = 8388607,
    OFFSET_FOR_SIGN = 31,
    OFFSET_FOR_EXP = 23
};

FPClass fpclassf(float value, int *psign) {
    union {
        float fv;
        unsigned int uv;
    } ptr;

    ptr.fv = value;
    unsigned int sign = SIGN & (ptr.uv);
    unsigned int frac = (ptr.uv) & FRAC;
    if (sign >> OFFSET_FOR_SIGN) {
        *psign = -1;
    } else {
        *psign = 0;
    }
    unsigned int is_normalazid = (EXP << OFFSET_FOR_EXP) & ptr.uv;
    if ((is_normalazid >> OFFSET_FOR_EXP) == 0) {
        if (frac == 0) {
            return FFP_ZERO;
        }
        return FFP_DENORMALIZED;
    }
    if ((is_normalazid >> OFFSET_FOR_EXP) && frac == 0) {
        return FFP_INF;
    }
    if ((is_normalazid >> OFFSET_FOR_EXP) == EXP) {
        *psign = 0;
        return FFP_NAN;
    }
    return FFP_NORMALIZED;
}
