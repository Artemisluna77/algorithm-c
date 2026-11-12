#include "sorting_exploration.h"

#include <stdint.h>
#include <stdlib.h>

/* 功能：用频数数组计数后按值域顺序回写，负数通过减去最小值映射到非负下标（思维拓展伪代码的 C17 实现，PDF 第403页，书页第391页）。 */
DsStatus ch08_frequency_sort_signed(int *values, size_t length) {
    if (length > 0 && values == NULL) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (length < 2) {
        return DS_STATUS_OK;
    }

    int minimum = values[0];
    int maximum = values[0];
    for (size_t i = 1; i < length; ++i) {
        if (values[i] < minimum) minimum = values[i];
        if (values[i] > maximum) maximum = values[i];
    }

    const uint64_t range_u64 = (uint64_t)((int64_t)maximum - (int64_t)minimum) + 1U;
    if (range_u64 > UINT64_C(65536)) {
        return DS_STATUS_INVALID_VALUE;
    }
    if (range_u64 > SIZE_MAX / sizeof(size_t)) {
        return DS_STATUS_OVERFLOW;
    }
    const size_t range = (size_t)range_u64;
    size_t *counts = (size_t *)calloc(range, sizeof(size_t));
    if (counts == NULL) {
        return DS_STATUS_NO_MEMORY;
    }

    for (size_t i = 0; i < length; ++i) {
        const size_t offset = (size_t)((int64_t)values[i] - (int64_t)minimum);
        ++counts[offset];
    }
    size_t output = 0;
    for (size_t offset = 0; offset < range; ++offset) {
        const int64_t value = (int64_t)minimum + (int64_t)offset;
        while (counts[offset] > 0) {
            values[output++] = (int)value;
            --counts[offset];
        }
    }
    free(counts);
    return DS_STATUS_OK;
}
