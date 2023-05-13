#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint64_t input;
    uint64_t counter = 1;
    while (scanf("%" SCNx64, &input) == 1) {
        if (counter != 1) {
            printf(" ");
        }
        if (input == 0) {
            int64_t answer = -1;
            ++counter;
            printf("%" PRIx64, answer);
            continue;
        }
        if (input == 1) {
            int64_t answer = 1;
            ++counter;
            printf("%" PRIx64, answer);
            continue;
        }
        if (input == 2) {
            int64_t answer = 2;
            ++counter;
            printf("%" PRIx64, answer);
            continue;
        }
        int64_t number = 2;
        uint64_t answer = 2;
        uint64_t current_value = 2;
        uint64_t previous_value = 1;
        while (answer < input) {
            ++number;
            answer = current_value + previous_value;
            previous_value = current_value;
            current_value = answer;
        }
        if (answer == input) {
            printf("%" PRIx64, number);
        } else {
            printf("%" PRIx64, number - 1);
        }
        ++counter;
    }
    printf("\n");
    return 0;
}
