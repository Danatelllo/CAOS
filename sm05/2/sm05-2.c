#include <stdio.h>
#include <stdlib.h>

struct BSearchResult {
    size_t low;
    size_t high;
    int result;
};

struct BSearchResult
bsearch2(const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar)(const void *p1, const void *p2, void *user),
         void *user) {
    struct BSearchResult answer;
    if (nmemb == 0) {
        answer.result = 0;
        answer.low = 0;
        answer.high = 0;
        return answer;
    }

    if (compar(key, base, user) < 0) {
        answer.result = 0;
        answer.high = 0;
        answer.low = 0;
        return answer;
    }
    if (compar(key, base + (size * (nmemb - 1)), user) > 0) {
        answer.high = nmemb;
        answer.low = nmemb;
        answer.result = 0;
        return answer;
    }

    answer.result = 0;
    size_t start = 0;
    size_t end = nmemb - 1;
    size_t mid = (end + start) / 2;
    int compare_result;
    while (start <= end) {
        compare_result = compar(key, base + (mid * size), user);
        if (compare_result < 0) {
            end = mid - 1;
        } else if (compare_result == 0) {
            answer.result = 1;
            break;
        } else {
            start = mid + 1;
        }
        mid = (start + end) / 2;
    }
    if (answer.result == 1) {
        if (compar(key, base + (size * (nmemb - 1)), user) == 0) {
            answer.high = nmemb;
        } else {
            for (size_t current = 0; current < nmemb; ++current) {
                compare_result = compar(key, base + (current * size), user);
                if (compare_result < 0) {
                    answer.high = current;
                    break;
                }
            }
        }
        for (size_t current = 0; current < nmemb; ++current) {
            compare_result = compar(key, base + size * current, user);
            if (compare_result == 0) {
                answer.low = current;
                break;
            }
        }
    } else {
        for (size_t current = 0; current < nmemb; ++current) {
            compare_result = compar(key, base + current * size, user);
            if (compare_result < 0 || compare_result == 0) {
                answer.high = current;
                answer.low = current;
                break;
            }
        }
    }
    return answer;
}
