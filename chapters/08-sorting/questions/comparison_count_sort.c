#include "comparison_count_sort.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* 功能：两两比较统计每个元素的秩并按秩填入结果（题目 cmpcountsort，PDF 第381页，书页第369页）。 */
DsStatus ch08_comparison_count_sort(const int *values, size_t length,
                                    int *output) {
    if (length > 0 && (values == NULL || output == NULL)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (length == 0) {
        return DS_STATUS_OK;
    }
    if (length > SIZE_MAX / sizeof(size_t) ||
        length > SIZE_MAX / sizeof(int)) {
        return DS_STATUS_OVERFLOW;
    }
    size_t *counts = (size_t *)calloc(length, sizeof(size_t));
    int *sorted = (int *)malloc(length * sizeof(int));
    if (counts == NULL || sorted == NULL) {
        free(counts);
        free(sorted);
        return DS_STATUS_NO_MEMORY;
    }
    for (size_t i = 0; i + 1 < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (values[i] < values[j]) {
                ++counts[j];
            } else {
                ++counts[i];
            }
        }
    }
    for (size_t i = 0; i < length; ++i) {
        sorted[counts[i]] = values[i];
    }
    memmove(output, sorted, length * sizeof(int));
    free(sorted);
    free(counts);
    return DS_STATUS_OK;
}
