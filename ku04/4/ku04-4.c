#include <alloca.h>
#include <dlfcn.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    SIGN = 2147483648,
    EXP = 255,
    FRAC = 8388607,
    OFFSET_FOR_SIGN = 31,
    OFFSET_FOR_EXP = 23,
    MAX_NOT_NAN_EXP = 254,
    OFFSET = 3
};

void sat_mul8(float *f) {
    union {
        float fv;
        unsigned int uv;
    } ptr;

    ptr.fv = *f;
    unsigned int frac = (ptr.uv) & FRAC;

    unsigned int is_normalazid = (EXP << OFFSET_FOR_EXP) & ptr.uv;
    if ((is_normalazid >> OFFSET_FOR_EXP) == EXP && frac == 0) {
        return;
    }
    if ((is_normalazid >> OFFSET_FOR_EXP) == EXP) {
        return;
    }
    if ((is_normalazid >> OFFSET_FOR_EXP)) {
        unsigned int cur_exp = (is_normalazid >> OFFSET_FOR_EXP);
        if ((cur_exp + OFFSET) < EXP) {
            ptr.uv += (OFFSET << OFFSET_FOR_EXP);
            *f = ptr.fv;
            return;
        } else {
            unsigned int sign = SIGN & (ptr.uv);
            unsigned int answer = FRAC;
            answer += (MAX_NOT_NAN_EXP << OFFSET_FOR_EXP);
            answer += sign;
            ptr.uv = answer;
            *f = ptr.fv;
            return;
        }
    } else {
        unsigned int check = (1 << OFFSET_FOR_EXP);
        int j = 0;
        while ((check & frac) == 0 && j < OFFSET) {
            frac = frac << 1;
            ++j;
        }
        unsigned int answer = frac;
        answer += (OFFSET - j) << OFFSET_FOR_EXP;
        unsigned int sign = SIGN & (ptr.uv);
        if (sign >> OFFSET_FOR_SIGN) {
            answer += SIGN;
        }
        ptr.uv = answer;
        *f = ptr.fv;
        return;
    }
}
