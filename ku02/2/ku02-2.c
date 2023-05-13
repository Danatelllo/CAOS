#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *prev;
    struct Node *next;
    int value;
} Node;

Node *push(Node *place, int value) {
    if (place == NULL) {
        struct Node *new_head = calloc(1, sizeof(*new_head));
        if (new_head == NULL) {
            return NULL;
        }
        new_head->value = value;
        new_head->next = NULL;
        new_head->prev = NULL;
        return new_head;
    }
    struct Node *new_head = calloc(1, sizeof(*new_head));
    if (new_head == NULL) {
        return NULL;
    }
    new_head->next = NULL;
    new_head->prev = NULL;
    new_head->next = place;
    new_head->value = value;

    if (place->prev == NULL) {
        place->prev = new_head;
    } else {
        new_head->prev = place->prev;
        place->prev->next = new_head;
        place->prev = new_head;
    }
    return new_head;
}

int pop(Node *node) {
    if (node->prev != NULL) {
        if (node->next != NULL) {
            node->prev->next = node->next;
        } else {
            node->prev->next = NULL;
        }
    }
    if (node->next != NULL) {
        if (node->prev != NULL) {
            node->next->prev = node->prev;
        } else {
            node->next->prev = NULL;
        }
    }
    int answer = node->value;
    if (node != NULL) {
        free(node);
    }
    return answer;
}
