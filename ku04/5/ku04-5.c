#include <stdio.h>
#include <sys/stat.h>

void computation(float *first, int second, float *third) {
    float buf[4] = {0, 0, 0, 0};
    float res[4];
    if (second == 0) {
        float answer = 0;
        for (int j = 0; j < 4; ++j) {
            answer += buf[j];
        }
        *third = answer;
        return;
    }

    for (int j = 0; j < 4; ++j) {
        buf[j] = *first;
        ++first;
    }
    second -= 4;
    if (second == 0) {
        float answer = 0;
        for (int j = 0; j < 4; ++j) {
            answer += buf[j];
        }
        *third = answer;
        return;
    }
    while (second != 0) {
        for (int j = 0; j < 4; ++j) {
            res[j] = *first;
            ++first;
        }
        for (int j = 0; j < 4; ++j) {
            buf[j] *= res[j];
        }
        second -= 4;
    }
    float answer = 0;
    for (int j = 0; j < 4; ++j) {
        answer += buf[j];
    }
    *third = answer;
}
