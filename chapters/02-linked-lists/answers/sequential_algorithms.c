#include "sequential_algorithms.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

// 功能：查找顺序表最小元素，以末元素填补被删除位置并返回最小值。
// 来源：《2027数据结构》第2章 2.2.4；PDF第34-35页；书页第22-23页。
int delete_minimum(SeqList *list, int *minimum) {
    size_t position = 0;
    size_t i;
    if (list == NULL || minimum == NULL || list->length == 0) return 0;
    *minimum = list->data[0];
    for (i = 1; i < list->length; ++i) {
        if (list->data[i] < *minimum) {
            *minimum = list->data[i];
            position = i;
        }
    }
    list->data[position] = list->data[list->length - 1];
    --list->length;
    return 1;
}

// 功能：原地逆置顺序表元素。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void reverse_sequential_list(SeqList *list) {
    size_t i;
    if (list == NULL) return;
    for (i = 0; i < list->length / 2; ++i) {
        int temporary = list->data[i];
        list->data[i] = list->data[list->length - i - 1];
        list->data[list->length - i - 1] = temporary;
    }
}

// 功能：通过压缩保留元素，删除顺序表中所有等于给定值的元素（解法一）。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void erase_value_by_compaction(SeqList *list, int value) {
    size_t kept = 0;
    size_t i;
    if (list == NULL) return;
    for (i = 0; i < list->length; ++i) {
        if (list->data[i] != value) list->data[kept++] = list->data[i];
    }
    list->length = kept;
}

// 功能：统计已删除元素数量并前移后续元素，删除顺序表中所有等于给定值的元素（解法二）。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void erase_value_by_counting(SeqList *list, int value) {
    size_t removed = 0;
    size_t i;
    if (list == NULL) return;
    for (i = 0; i < list->length; ++i) {
        if (list->data[i] == value) ++removed;
        else if (removed > 0) list->data[i - removed] = list->data[i];
    }
    list->length -= removed;
}

// 功能：在非递减顺序表中原地删除重复元素，每个值只保留一个。
// 来源：《2027数据结构》第2章习题答案 Delete_Same；PDF第36页；书页第24页。
int erase_sorted_duplicates(SeqList *list) {
    size_t last_unique;
    size_t current;
    if (list == NULL || list->length == 0) return 0;
    last_unique = 0;
    for (current = 1; current < list->length; ++current) {
        if (list->data[current] != list->data[last_unique]) {
            list->data[++last_unique] = list->data[current];
        }
    }
    list->length = last_unique + 1;
    return 1;
}

// 功能：删除顺序表中值位于闭区间 [lower, upper] 的元素。
// 来源：《2027数据结构》第2章 2.2.4；PDF第36页；书页第24页。
int erase_closed_value_range(SeqList *list, int lower, int upper) {
    size_t kept = 0;
    size_t i;
    if (list == NULL || list->length == 0 || lower > upper) return 0;
    for (i = 0; i < list->length; ++i) {
        if (list->data[i] < lower || list->data[i] > upper) {
            list->data[kept++] = list->data[i];
        }
    }
    list->length = kept;
    return 1;
}

// 功能：将两个递增顺序表归并到有容量上限的第三个顺序表。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37页；书页第25页。
int merge_sorted_lists(const SeqList *left, const SeqList *right, SeqList *output) {
    size_t i = 0, j = 0, k = 0;
    if (left == NULL || right == NULL || output == NULL ||
        left->length > SEQ_LIST_MAX_SIZE || right->length > SEQ_LIST_MAX_SIZE ||
        left->length + right->length > SEQ_LIST_MAX_SIZE) return 0;
    while (i < left->length && j < right->length) {
        output->data[k++] = left->data[i] <= right->data[j] ? left->data[i++] : right->data[j++];
    }
    while (i < left->length) output->data[k++] = left->data[i++];
    while (j < right->length) output->data[k++] = right->data[j++];
    output->length = k;
    return 1;
}

// 功能：逆置数组指定闭区间，为三次逆置的循环左移算法提供基础操作。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37-39页；书页第25-27页。
void reverse_segment(int *values, size_t length, size_t left, size_t right) {
    if (values == NULL || left > right || right >= length) return;
    while (left < right) {
        int temporary = values[left++];
        values[left - 1] = values[right];
        values[right--] = temporary;
    }
}

// 功能：通过逆置前段、后段和整体，交换数组中相邻的两个数据块。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37页；书页第25页。
void exchange_adjacent_blocks(int *values, size_t length, size_t first_block_size) {
    if (values == NULL || length == 0 || first_block_size == 0 || first_block_size >= length) return;
    reverse_segment(values, length, 0, length - 1);
    reverse_segment(values, length, 0, length - first_block_size - 1);
    reverse_segment(values, length, length - first_block_size, length - 1);
}

// 功能：在递增数组中二分查找目标值；命中时与后继交换，未命中时插入到有序位置。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37-38页；书页第25-26页。
int search_exchange_insert(int *sorted_values, size_t *length, size_t capacity, int value) {
    size_t low = 0, high, middle, i;
    if (length == NULL || *length > capacity || (sorted_values == NULL && capacity != 0)) return -1;
    high = *length;
    while (low < high) {
        middle = low + (high - low) / 2;
        if (sorted_values[middle] == value) {
            if (middle + 1 < *length) {
                int temporary = sorted_values[middle];
                sorted_values[middle] = sorted_values[middle + 1];
                sorted_values[middle + 1] = temporary;
            }
            return 1;
        }
        if (sorted_values[middle] < value) low = middle + 1;
        else high = middle;
    }
    if (*length == capacity) return -1;
    for (i = *length; i > low; --i) sorted_values[i] = sorted_values[i - 1];
    sorted_values[low] = value;
    ++*length;
    return 0;
}

// 功能：用三个下标同步扫描递增数组，返回三者共有的不同值。
// 来源：《2027数据结构》第2章 2.2.4；PDF第38页；书页第26页。
int common_values_in_three_sorted_arrays(const int *a, size_t a_length,
                                         const int *b, size_t b_length,
                                         const int *c, size_t c_length,
                                         int *common, size_t capacity,
                                         size_t *common_length) {
    size_t i = 0, j = 0, k = 0;
    if (common_length == NULL || (a == NULL && a_length != 0) ||
        (b == NULL && b_length != 0) || (c == NULL && c_length != 0)) return 0;
    *common_length = 0;
    while (i < a_length && j < b_length && k < c_length) {
        if (a[i] == b[j] && b[j] == c[k]) {
            if (*common_length == 0 || common[*common_length - 1] != a[i]) {
                if (*common_length == capacity || common == NULL) return 0;
                common[(*common_length)++] = a[i];
            }
            ++i;
            ++j;
            ++k;
        } else {
            int maximum = a[i] > b[j] ? a[i] : b[j];
            if (c[k] > maximum) maximum = c[k];
            if (a[i] < maximum) ++i;
            if (b[j] < maximum) ++j;
            if (c[k] < maximum) ++k;
        }
    }
    return 1;
}

// 功能：通过三次逆置将数组循环左移 distance 个位置。
// 来源：《2027数据结构》第2章 2.2.4；PDF第38-39页；书页第26-27页。
void rotate_left_by_reversal(int *values, size_t length, size_t distance) {
    if (values == NULL || length == 0) return;
    distance %= length;
    if (distance > 0) reverse_segment(values, length, 0, distance - 1);
    reverse_segment(values, length, distance, length - 1);
    reverse_segment(values, length, 0, length - 1);
}

// 功能：对两个等长递增数组使用二分划分，求合并后第 n 小的元素。
// 来源：《2027数据结构》第2章 2.2.4；PDF第39-40页；书页第27-28页。
int median_of_two_equal_sorted_arrays(const int *a, size_t a_length,
                                      const int *b, size_t b_length, int *median) {
    size_t low = 0, high, n;
    if (a == NULL || b == NULL || median == NULL || a_length == 0 || a_length != b_length) return 0;
    n = a_length;
    high = n;
    while (low <= high) {
        size_t take_a = low + (high - low) / 2;
        size_t take_b = n - take_a;
        int a_left = take_a == 0 ? INT_MIN : a[take_a - 1];
        int a_right = take_a == n ? INT_MAX : a[take_a];
        int b_left = take_b == 0 ? INT_MIN : b[take_b - 1];
        int b_right = take_b == n ? INT_MAX : b[take_b];
        if (a_left <= b_right && b_left <= a_right) {
            *median = a_left > b_left ? a_left : b_left;
            return 1;
        }
        if (a_left > b_right) {
            if (take_a == 0) return 0;
            high = take_a - 1;
        } else {
            low = take_a + 1;
        }
    }
    return 0;
}

// 功能：用候选值抵消法查找主元素，并再次计数确认其出现次数超过一半。
// 来源：《2027数据结构》第2章 2.2.4；PDF第40页；书页第28页。
int majority_element(const int *values, size_t length, int *majority) {
    size_t count = 0, i, occurrences = 0;
    int candidate = 0;
    if (values == NULL || length == 0 || majority == NULL) return 0;
    for (i = 0; i < length; ++i) {
        if (count == 0) candidate = values[i];
        if (values[i] == candidate) ++count;
        else --count;
    }
    for (i = 0; i < length; ++i) if (values[i] == candidate) ++occurrences;
    if (occurrences <= length / 2) return 0;
    *majority = candidate;
    return 1;
}

// 功能：使用长度为 n 的标记数组找出数组中未出现的最小正整数。
// 来源：《2027数据结构》第2章 2.2.4；PDF第41页；书页第29页。
int smallest_missing_positive(const int *values, size_t length) {
    unsigned char *present;
    size_t i;
    int missing = 0;
    if ((values == NULL && length != 0) || length >= (size_t)INT_MAX || length == SIZE_MAX) return 0;
    present = (unsigned char *)calloc(length + 1, sizeof(unsigned char));
    if (present == NULL) return 0;
    for (i = 0; i < length; ++i) {
        if (values[i] > 0 && (size_t)values[i] <= length) present[values[i]] = 1;
    }
    for (i = 1; i <= length; ++i) {
        if (!present[i]) {
            missing = (int)i;
            break;
        }
    }
    if (missing == 0) missing = (int)(length + 1);
    free(present);
    return missing;
}

// 功能：同步推进三个递增数组中当前最小值的下标，求三元组两两距离和的最小值。
// 来源：《2027数据结构》第2章 2.2.4；PDF第42页；书页第30页。
long long minimum_three_array_distance(const int *a, size_t a_length,
                                       const int *b, size_t b_length,
                                       const int *c, size_t c_length) {
    size_t i = 0, j = 0, k = 0;
    long long best = LLONG_MAX;
    if (a == NULL || b == NULL || c == NULL || a_length == 0 || b_length == 0 || c_length == 0) return 0;
    while (i < a_length && j < b_length && k < c_length) {
        long long x = a[i], y = b[j], z = c[k];
        long long distance = llabs(x - y) + llabs(y - z) + llabs(z - x);
        int minimum = a[i] < b[j] ? a[i] : b[j];
        if (c[k] < minimum) minimum = c[k];
        if (distance < best) best = distance;
        if (a[i] == minimum) ++i;
        else if (b[j] == minimum) ++j;
        else ++k;
    }
    return best;
}

// 功能：从右向左维护后缀最大、最小值，按当前元素符号计算其与极值的乘积。
// 来源：《2027数据结构》第2章 2.2.4；PDF第33、42页；书页第21、30页。
void multiply_by_suffix_extreme(const int *values, size_t length, long long *output) {
    size_t i;
    int maximum, minimum;
    if (values == NULL || output == NULL || length == 0) return;
    maximum = values[length - 1];
    minimum = values[length - 1];
    for (i = length; i > 0; --i) {
        size_t index = i - 1;
        if (values[index] > maximum) maximum = values[index];
        if (values[index] < minimum) minimum = values[index];
        output[index] = (long long)values[index] * (values[index] >= 0 ? maximum : minimum);
    }
}
