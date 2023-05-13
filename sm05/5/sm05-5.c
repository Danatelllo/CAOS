#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_SIZE_OF_PRINT = 35,
    MINUS = 45,
    PLUS = 43,
    MULTIPLY = 42,
    DIVISION = 47,
    INTEREST = 37,
    HELPER_FOR_CONVERT = 48,
    GRID = 35,
    R = 114,
    W = 119,
    N = 110,
    SHIFT_BY_TEN = 10,
    SEMICOLON = 59,
    COPY_ELEM = 100,
    EXCHANGE_ELEM = 115,
    MIN_VALUE_OF_INT = -2147483648
};

enum {
    PE_OK,               // no error
    PE_STACK_UNDERFLOW,  // not enough elements on stack
    PE_INVALID_INDEX,    // s or d operations refer to invalid index
    PE_DIVISION_BY_ZERO,
    PE_INT_OVERFLOW,
    PE_READ_FAILED,  // read from stdin failed to convert integer for any reason
    PE_OUT_OF_MEMORY,
};

struct Node {
    int value;
    struct Node *previous;
};

struct PolizState {
    struct Node *stack;
    int last_error;
};

typedef int (*PolizFuncT)(struct PolizState *state, int iextra);

struct PolizItem {
    PolizFuncT handler;
    int iextra;
};

int add_node(struct PolizState *state, int iextra) {
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    struct Node *new_head = calloc(1, sizeof(*new_head));
    if (!new_head) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    new_head->previous = state->stack;
    new_head->value = iextra;
    state->stack = new_head;
    (void)iextra;
    return PE_OK;
}

int get_values_and_remove(int *v1, int *v2, struct PolizState *state) {
    if (!state->stack) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    if (!state->stack->previous) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    if (state->stack->previous != NULL) {
        *v1 = state->stack->value;
    } else {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    if (state->stack->previous->previous != NULL) {
        *v2 = state->stack->previous->value;
    } else {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    struct Node *head = state->stack->previous->previous;
    if (state->stack->previous) {
        free(state->stack->previous);
    }
    if (state->stack) {
        free(state->stack);
    }
    state->stack = head;

    return PE_OK;
}

int multiply(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int value1 = 0;
    int value2 = 0;
    int result = get_values_and_remove(&value1, &value2, state);
    if (result == -PE_STACK_UNDERFLOW) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    int mul_result = 0;
    if (__builtin_mul_overflow(value1, value2, &mul_result)) {
        state->last_error = PE_INT_OVERFLOW;
        return -PE_INT_OVERFLOW;
    }

    result = add_node(state, mul_result);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int division(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int value1 = 0;
    int value2 = 0;
    int result = get_values_and_remove(&value1, &value2, state);
    if (result == -PE_STACK_UNDERFLOW) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    if (value1 == 0) {
        state->last_error = PE_DIVISION_BY_ZERO;
        return -PE_DIVISION_BY_ZERO;
    }
    if (value1 == -1 && value2 == MIN_VALUE_OF_INT) {
        state->last_error = PE_INT_OVERFLOW;
        return -PE_INT_OVERFLOW;
    }
    int result_of_division = 0;
    if (value2 % value1 == 0) {
        result_of_division = value2 / value1;
    } else {
        int additional = 0;
        if (value2 / value1 < 0) {
            additional = 1;
        } else {
            additional = -1;
        }
        if (value2 > 0) {
            result_of_division = value2 / value1;
        } else {
            result_of_division = value2 / value1 - additional;
        }
    }

    result = add_node(state, result_of_division);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int plus(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int value1 = 0;
    int value2 = 0;
    int result = get_values_and_remove(&value1, &value2, state);
    if (result == -PE_STACK_UNDERFLOW) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }

    int add_result = 0;
    if (__builtin_add_overflow(value1, value2, &add_result)) {
        state->last_error = PE_INT_OVERFLOW;
        return -PE_INT_OVERFLOW;
    }

    result = add_node(state, add_result);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int minus(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int value1 = 0;
    int value2 = 0;
    int result = get_values_and_remove(&value1, &value2, state);
    if (result == -PE_STACK_UNDERFLOW) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    int minus_result = 0;
    if (__builtin_sub_overflow(value2, value1, &minus_result)) {
        state->last_error = PE_INT_OVERFLOW;
        return -PE_INT_OVERFLOW;
    }
    result = add_node(state, minus_result);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int interest(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int value1 = 0;
    int value2 = 0;
    int result = get_values_and_remove(&value1, &value2, state);
    if (result == -PE_STACK_UNDERFLOW) {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    if (value1 == 0) {
        state->last_error = PE_DIVISION_BY_ZERO;
        return -PE_DIVISION_BY_ZERO;
    }
    int interest = value2 % value1;
    if (interest < 0) {
        interest += abs(value1);
    }
    result = add_node(state, interest);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int grid(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    if (state->stack->previous != NULL) {
        if (state->stack->value == MIN_VALUE_OF_INT) {
            state->last_error = PE_INT_OVERFLOW;
            return -PE_INT_OVERFLOW;
        }
        state->stack->value *= -1;
    } else {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    return PE_OK;
}

int read(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    int meaning;
    int result = scanf("%d", &meaning);
    if (result != 1) {
        state->last_error = PE_READ_FAILED;
        return -PE_READ_FAILED;
    }
    result = add_node(state, meaning);
    if (result == -PE_OUT_OF_MEMORY) {
        state->last_error = PE_OUT_OF_MEMORY;
        return -PE_OUT_OF_MEMORY;
    }
    return PE_OK;
}

int write(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    if (state->stack->previous != NULL) {
        printf("%d", state->stack->value);
        struct Node *head = state->stack->previous;
        if (state->stack) {
            free(state->stack);
        }
        state->stack = head;
    } else {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    return PE_OK;
}

int new_line(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    printf("\n");
    return PE_OK;
}

int semicolon(struct PolizState *state, int iextra) {
    (void)iextra;
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    if (state->stack->previous != NULL) {
        struct Node *head = state->stack->previous;
        if (state->stack) {
            free(state->stack);
        }
        state->stack = head;
    } else {
        state->last_error = PE_STACK_UNDERFLOW;
        return -PE_STACK_UNDERFLOW;
    }
    return PE_OK;
}

int copy_elem(struct PolizState *state, int iextra) {
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }
    struct Node *head = state->stack;
    for (int j = 0; j < iextra; ++j) {
        if (head->previous != NULL) {
            head = head->previous;
        } else {
            state->last_error = PE_INVALID_INDEX;
            return -PE_INVALID_INDEX;
        }
    }
    if (head->previous != NULL) {
        int result = add_node(state, head->value);
        if (result == -PE_OUT_OF_MEMORY) {
            state->last_error = PE_OUT_OF_MEMORY;
            return -PE_OUT_OF_MEMORY;
        }
    } else {
        state->last_error = PE_INVALID_INDEX;
        return -PE_INVALID_INDEX;
    }
    return PE_OK;
}

int exchange_elem(struct PolizState *state, int iextra) {
    if (state->last_error != PE_OK) {
        return -state->last_error;
    }

    struct Node *head = state->stack;
    for (int j = 0; j < iextra; ++j) {
        if (head->previous != NULL) {
            head = head->previous;
        } else {
            state->last_error = PE_INVALID_INDEX;
            return -PE_INVALID_INDEX;
        }
    }
    if (head->previous != NULL) {
        int tmp = head->value;
        head->value = state->stack->value;
        state->stack->value = tmp;
    } else {
        state->last_error = PE_INVALID_INDEX;
        return -PE_INVALID_INDEX;
    }
    return PE_OK;
}

// opaque structure for poliz calculation state

// poliz operation handler

// runtime errors

int get_num(const char s[MAX_SIZE_OF_PRINT], int start, int number) {
    int i = start;
    int sign = number / abs(number);
    while (s[i] != '\0') {
        if (i == start) {
            number = sign * (s[i] - HELPER_FOR_CONVERT);
        } else {
            number *= SHIFT_BY_TEN;
            number += sign * (s[i] - HELPER_FOR_CONVERT);
        }
        ++i;
    }
    return number;
}

int find_end_of_string(const char s[MAX_SIZE_OF_PRINT]) {
    int answer = 0;
    for (int j = 0; j < MAX_SIZE_OF_PRINT; ++j) {
        if (s[j] == '\0') {
            answer = j;
            break;
        }
    }
    return answer;
}

struct DynArray {
    size_t size;
    size_t capacity;
    struct PolizItem *ptr;
} array = {};

void append(struct DynArray *arr, struct PolizItem item) {
    if (arr->size + 1 > arr->capacity) {
        size_t newcap = 2 * (arr->capacity + 1);
        struct PolizItem *tmp = realloc(arr->ptr, newcap * sizeof(*tmp));
        if (!tmp) {
            // Handle allocation error
        }
        arr->ptr = tmp;
        arr->capacity = newcap;
    }
    arr->ptr[arr->size++] = item;
}

struct PolizItem *poliz_compile(const char *str) {
    struct DynArray arr;
    arr.capacity = 0;
    arr.size = 0;
    arr.ptr = NULL;
    char s[MAX_SIZE_OF_PRINT];
    struct PolizItem item;
    while (sscanf(str, "%s", s) != EOF) {
        if (s[0] == DIVISION) {
            item.handler = division;
            append(&arr, item);
        } else if (s[0] == MULTIPLY) {
            item.handler = multiply;
            append(&arr, item);
        } else if (s[0] == INTEREST) {
            item.handler = interest;
            append(&arr, item);
        } else if (s[0] == MINUS) {
            if (s[1] == '\0') {
                item.handler = minus;
                append(&arr, item);
            } else {
                int number = get_num(s, 1, -1);
                item.handler = add_node;
                item.iextra = number;
                append(&arr, item);
            }
        } else if (s[0] == PLUS) {
            if (s[1] == '\0') {
                item.handler = plus;
                append(&arr, item);
            } else {
                int number = get_num(s, 1, 1);
                item.handler = add_node;
                item.iextra = number;
                append(&arr, item);
            }
        } else if (s[0] == GRID) {
            item.handler = grid;
            append(&arr, item);
        } else if (s[0] == R) {
            item.handler = read;
            append(&arr, item);
        } else if (s[0] == W) {
            item.handler = write;
            append(&arr, item);
        } else if (s[0] == N) {
            item.handler = new_line;
            append(&arr, item);
        } else if (s[0] == SEMICOLON) {
            item.handler = semicolon;
            append(&arr, item);
        } else if (s[0] == COPY_ELEM) {
            if (s[1] == '\0') {
                item.iextra = 0;
            } else {
                item.iextra = get_num(s, 1, 1);
            }
            item.handler = copy_elem;
            append(&arr, item);
        } else if (s[0] == EXCHANGE_ELEM) {
            if (s[1] == '\0') {
                item.iextra = 1;
            } else {
                item.iextra = get_num(s, 1, 1);
            }
            item.handler = exchange_elem;
            append(&arr, item);
        } else if (isdigit(s[0])) {
            int number = get_num(s, 0, 1);
            item.handler = add_node;
            item.iextra = number;
            append(&arr, item);
        }

        str += find_end_of_string(s);
        if (*str == ' ') {
            ++str;
        }
    }
    item.handler = NULL;
    append(&arr, item);
    return arr.ptr;
}

struct PolizState *poliz_new_state(void) {
    struct PolizState *new_state = calloc(1, sizeof(*new_state));
    new_state->stack = calloc(1, sizeof(*new_state->stack));
    new_state->stack->previous = NULL;
    new_state->last_error = PE_OK;
    return new_state;
}

void poliz_free_state(struct PolizState *state) {
    if (state) {
        if (state->stack) {
            struct Node *head;
            while (state->stack) {
                head = state->stack->previous;
                free(state->stack);
                state->stack = head;
            }
        }
        free(state);
    }
}

int poliz_last_error(struct PolizState *state) {
    return state->last_error;
}
