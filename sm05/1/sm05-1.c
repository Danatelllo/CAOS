#include <stdio.h>
#include <stdlib.h>

enum { A = 1103515245, C = 12345, M = 2147483648 };

struct RandomGenerator;

static void destroy_rg(struct RandomGenerator *rr) {
    if (rr) {
        free(rr);
    }
}

typedef unsigned int (*NextT)(struct RandomGenerator *rr);

typedef void (*DestroyT)(struct RandomGenerator *rr);

typedef struct RandomOperations {
    NextT next;
    DestroyT destroy;
} RandomOperations;

typedef struct RandomGenerator {
    RandomOperations *ops;
    unsigned current_step;

} RandomGenerator;

static unsigned int next_step(struct RandomGenerator *rr) {
    rr->current_step = (A * rr->current_step + C) % M;
    return rr->current_step;
}

struct RandomOperations my_ops = {next_step, destroy_rg};

struct RandomGenerator *random_create(int seed) {
    struct RandomGenerator *rr = calloc(1, sizeof(*rr));
    if (rr == NULL) {
        return NULL;
    }
    rr->ops = &my_ops;
    rr->current_step = seed;
    return rr;
}
