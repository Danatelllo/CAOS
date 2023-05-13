#include <stdio.h>

enum {
    OFFSET_ONE_BITE = 7,
    BEGIN_KIRILL = 0x400,
    END_KIRILL = 0x4ff,
    OFFSET_FOR_BIT2 = 63,
    OFFSET_FOR_BIT = 127,
    PREFICS_FOR_UTF_TYPE_ONE = 14,
    PREFICS_FOR_UTF_TYPE_TWO = 30
};

int main() {
    unsigned char ch_read = 0;
    int bite1 = OFFSET_ONE_BITE;
    int bite2 = 5;
    int bite3 = 4;
    int bite4 = 3;
    int current_sum = 0;

    int counter_char = 0;
    int kirill_counter = 0;
    int kirill_start = BEGIN_KIRILL;
    int kirill_end = END_KIRILL;

    while (scanf("%c", &ch_read) == 1) {
        current_sum = 0;
        if ((ch_read >> bite1) == 0) {
            ++counter_char;
            if (kirill_start <= ch_read && ch_read <= kirill_end) {
                ++kirill_counter;
            }
        } else if ((ch_read >> bite2) == 6) {
            ch_read &= OFFSET_FOR_BIT2;
            int helper = ch_read;
            helper = (helper << 6);
            current_sum += helper;
            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }
            ch_read &= OFFSET_FOR_BIT;
            current_sum += ch_read;

            ++counter_char;
            if (kirill_start <= current_sum && current_sum <= kirill_end) {
                ++kirill_counter;
            }
        } else if ((ch_read >> bite3) == PREFICS_FOR_UTF_TYPE_ONE) {
            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }
            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }
            ++counter_char;
        } else if ((ch_read >> bite4) == PREFICS_FOR_UTF_TYPE_TWO) {
            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }
            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }

            if (scanf("%c", &ch_read) != 1) {
                return 1;
            }
            ++counter_char;
        }
    }
    printf("%d", counter_char);
    printf("%s", " ");
    printf("%d\n", kirill_counter);
}
