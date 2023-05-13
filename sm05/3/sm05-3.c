#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *previous;
} Node;

int main() {
    struct Node *head = NULL;
    struct Node *prev = NULL;
    int mean = 0;
    int is_first_number = 1;
    while (scanf("%d", &mean) == 1) {
        if (is_first_number) {
            is_first_number = 0;
            head = calloc(1, sizeof(*head));
            head->value = mean;
        } else {
            prev = head;
            head = calloc(1, sizeof(*head));
            head->value = mean;
            head->previous = prev;
        }
    }
    while (head != NULL) {
        printf("%d\n", head->value);
        prev = head;
        head = head->previous;
        if (prev != NULL) {
            free(prev);
        }
    }
    return 0;
}
