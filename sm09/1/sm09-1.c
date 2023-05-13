#include <stdio.h>

enum {
    BIT_MASK_FOR_NUMBERS = 4095,
    EIGHT = 8,
    ELEVEN = 11,
    TEN = 10,
    NINE = 9,
    FOUR = 4,
    SEVEN = 7,
    SIX = 6,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FIVE = 5
};

int get_octal_number(int number) {
    int answer = 0;
    int ten = 1;
    while (number != 0) {
        answer += (number % EIGHT) * ten;
        number /= EIGHT;
        ten *= TEN;
    }
    return answer;
}

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    }
    if (size == 1) {
        buf[0] = '\0';
        return buf;
    }
    size_t min = size;
    if (size > NINE) {
        min = TEN;
    }
    buf[min - 1] = '\0';
    int mask = perms & BIT_MASK_FOR_NUMBERS;
    int numbers[FOUR];
    int octal_number = get_octal_number(mask);
    for (int i = 0; i < FOUR; ++i) {
        numbers[THREE - i] = octal_number % TEN;
        octal_number /= TEN;
    }
    char str_perms[NINE] = "---------";
    int pointer = 0;
    for (int i = 1; i < FOUR; ++i) {
        if (numbers[i] == SEVEN) {
            str_perms[pointer++] = 'r';
            str_perms[pointer++] = 'w';
            str_perms[pointer++] = 'x';
        } else if (numbers[i] == ONE) {
            pointer += TWO;
            str_perms[pointer++] = 'x';
        } else if (numbers[i] == TWO) {
            ++pointer;
            str_perms[pointer++] = 'w';
            ++pointer;
        } else if (numbers[i] == THREE) {
            ++pointer;
            str_perms[pointer++] = 'w';
            str_perms[pointer++] = 'x';
        } else if (numbers[i] == FOUR) {
            str_perms[pointer++] = 'r';
            pointer += TWO;
        } else if (numbers[i] == FIVE) {
            str_perms[pointer++] = 'r';
            ++pointer;
            str_perms[pointer++] = 'x';
        } else if (numbers[i] == SIX) {
            str_perms[pointer++] = 'r';
            str_perms[pointer++] = 'w';
            ++pointer;
        } else if (numbers[i] == 0) {
            pointer += THREE;
        }
    }

    if (mask & (1 << ELEVEN)) {
        if (str_perms[FIVE] != '-' || str_perms[EIGHT] != '-') {
            str_perms[TWO] = 's';
        }
    }

    if (mask & (1 << TEN)) {
        if (str_perms[EIGHT] != '-') {
            str_perms[FIVE] = 's';
        }
    }
    if (mask & (1 << NINE)) {
        if (str_perms[EIGHT] != '-' && str_perms[SEVEN] != '-') {
            str_perms[EIGHT] = 't';
        }
    }
    for (size_t j = 0; j + 1 < min; ++j) {
        buf[j] = str_perms[j];
    }
    return buf;
}