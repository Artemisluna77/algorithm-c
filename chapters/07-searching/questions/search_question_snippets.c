#include "search_question_snippets.h"

#include <stdint.h>

/* 功能：按固定步长跳跃定位有序数组区间，再回看本区间元素（试题22代码，PDF 第283页，书页第271页）。 */
Ch07Status ch07_stride_search(const int *sorted, size_t length, int key,
                              size_t step, size_t *index) {
    if ((length > 0 && sorted == NULL) || index == NULL || step == 0) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    size_t current = 0;
    while (current < length && sorted[current] < key) {
        if (step > length - 1 - current) {
            size_t candidate = length;
            while (candidate > current + 1) {
                --candidate;
                if (sorted[candidate] == key) {
                    *index = candidate;
                    return CH07_STATUS_OK;
                }
            }
            *index = SIZE_MAX;
            return CH07_STATUS_OK;
        }
        current += step;
    }
    if (current < length && sorted[current] == key) {
        *index = current;
        return CH07_STATUS_OK;
    }
    size_t maximum_offset = step - 1;
    if (maximum_offset > current) {
        maximum_offset = current;
    }
    for (size_t offset = 1; offset <= maximum_offset; ++offset) {
        const size_t candidate = current - offset;
        if (candidate < length && sorted[candidate] == key) {
            *index = candidate;
            return CH07_STATUS_OK;
        }
    }
    *index = SIZE_MAX;
    return CH07_STATUS_OK;
}
