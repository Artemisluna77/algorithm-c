#include "sorting_algorithms.h"

#include <stdint.h>
#include <stdlib.h>

/* 功能：检查可写数组是否满足长度与指针约束，供正文数组算法复用。 */
static DsStatus ch08_validate_array(int *values, size_t length) {
    return length == 0 || values != NULL ? DS_STATUS_OK
                                         : DS_STATUS_INVALID_ARGUMENT;
}

/* 功能：对半开区间执行归并并使用调用方提供的复用缓冲区（正文 Merge 的 C 辅助过程，PDF 第376页，书页第364页）。 */
static void ch08_merge_with_buffer(int *values, int *buffer, size_t first,
                                  size_t middle, size_t last) {
    for (size_t i = first; i < last; ++i) {
        buffer[i] = values[i];
    }
    size_t left = first;
    size_t right = middle;
    size_t output = first;
    while (left < middle && right < last) {
        if (buffer[left] <= buffer[right]) {
            values[output++] = buffer[left++];
        } else {
            values[output++] = buffer[right++];
        }
    }
    while (left < middle) {
        values[output++] = buffer[left++];
    }
    while (right < last) {
        values[output++] = buffer[right++];
    }
}

/* 功能：递归排序左右半区并合并结果（正文 MergeSort 的 C 辅助过程，PDF 第376页，书页第364页）。 */
static void ch08_merge_sort_range(int *values, int *buffer,
                                  size_t first, size_t last) {
    if (last - first < 2) {
        return;
    }
    const size_t middle = first + (last - first) / 2;
    ch08_merge_sort_range(values, buffer, first, middle);
    ch08_merge_sort_range(values, buffer, middle, last);
    ch08_merge_with_buffer(values, buffer, first, middle, last);
}

/* 功能：按首元素枢轴划分区间；快速排序只递归较小区间（正文 QuickSort 的 C 辅助过程，PDF 第355页，书页第343页）。 */
static DsStatus ch08_quick_sort_range(int *values, size_t length,
                                      size_t low, size_t high) {
    while (low < high) {
        size_t pivot = 0;
        const DsStatus status = ch08_partition_first_pivot(
            values, length, low, high, &pivot);
        if (status != DS_STATUS_OK) {
            return status;
        }
        if (pivot - low < high - pivot) {
            if (pivot > low) {
                (void)ch08_quick_sort_range(values, length, low, pivot - 1);
            }
            low = pivot + 1;
        } else {
            if (pivot < high) {
                (void)ch08_quick_sort_range(values, length, pivot + 1, high);
            }
            if (pivot == 0) {
                return DS_STATUS_OK;
            }
            high = pivot - 1;
        }
    }
    return DS_STATUS_OK;
}

/* 功能：交换两个整数元素（正文冒泡排序脚注辅助代码，PDF 第352页，书页第340页）。 */
void ch08_swap_values(int *left, int *right) {
    if (left == NULL || right == NULL || left == right) {
        return;
    }
    const int temporary = *left;
    *left = *right;
    *right = temporary;
}

/* 功能：从左到右将当前元素插入前方有序区间（正文 InsertSort，PDF 第345页，书页约第333页）。 */
DsStatus ch08_insertion_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t i = 1; i < length; ++i) {
        const int key = values[i];
        size_t j = i;
        while (j > 0 && key < values[j - 1]) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = key;
    }
    return DS_STATUS_OK;
}

/* 功能：折半查找稳定插入位置并后移元素（正文 BInsertSort，PDF 第346页，书页第334页）。 */
DsStatus ch08_binary_insertion_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t i = 1; i < length; ++i) {
        const int key = values[i];
        size_t low = 0;
        size_t high = i;
        while (low < high) {
            const size_t middle = low + (high - low) / 2;
            if (values[middle] <= key) {
                low = middle + 1;
            } else {
                high = middle;
            }
        }
        for (size_t j = i; j > low; --j) {
            values[j] = values[j - 1];
        }
        values[low] = key;
    }
    return DS_STATUS_OK;
}

/* 功能：按逐次折半的增量对各子序列执行插入排序（正文 ShellSort，PDF 第347–348页，书页第335–336页）。 */
DsStatus ch08_shell_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t gap = length / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < length; ++i) {
            const int key = values[i];
            size_t j = i;
            while (j >= gap && values[j - gap] > key) {
                values[j] = values[j - gap];
                j -= gap;
            }
            values[j] = key;
        }
    }
    return DS_STATUS_OK;
}

/* 功能：从后往前交换相邻逆序项，将当前最小项冒泡到左端（正文 BubbleSort，PDF 第352页，书页第340页）。 */
DsStatus ch08_bubble_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t start = 0; start + 1 < length; ++start) {
        int swapped = 0;
        for (size_t j = length - 1; j > start; --j) {
            if (values[j - 1] > values[j]) {
                ch08_swap_values(&values[j - 1], &values[j]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return DS_STATUS_OK;
}

/* 功能：以区间首元素为枢轴执行挖坑式划分（正文 Partition，PDF 第355页，书页第343页）。 */
DsStatus ch08_partition_first_pivot(int *values, size_t length, size_t low,
                                     size_t high, size_t *pivot_index) {
    if (values == NULL || pivot_index == NULL || low > high || high >= length) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    const int pivot = values[low];
    while (low < high) {
        while (low < high && values[high] >= pivot) {
            --high;
        }
        if (low < high) {
            values[low] = values[high];
        }
        while (low < high && values[low] <= pivot) {
            ++low;
        }
        if (low < high) {
            values[high] = values[low];
        }
    }
    values[low] = pivot;
    *pivot_index = low;
    return DS_STATUS_OK;
}

/* 功能：使用首元素枢轴执行快速排序（正文 QuickSort，PDF 第355页，书页第343页）。 */
DsStatus ch08_quick_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK || length < 2) {
        return status;
    }
    return ch08_quick_sort_range(values, length, 0, length - 1);
}

/* 功能：每趟选取未排序部分最小元素并交换到前端（正文 SelectSort，PDF 第363页，书页第351页）。 */
DsStatus ch08_selection_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t i = 0; i + 1 < length; ++i) {
        size_t minimum = i;
        for (size_t j = i + 1; j < length; ++j) {
            if (values[j] < values[minimum]) {
                minimum = j;
            }
        }
        ch08_swap_values(&values[i], &values[minimum]);
    }
    return DS_STATUS_OK;
}

/* 功能：将以 root 为根的最大堆子树向下调整（正文 HeapAdjust，PDF 第365页，书页第353页）。 */
DsStatus ch08_heap_adjust(int *values, size_t length, size_t root) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    if (root >= length) {
        return DS_STATUS_OK;
    }
    const int root_value = values[root];
    size_t child = root * 2 + 1;
    while (child < length) {
        if (child + 1 < length && values[child] < values[child + 1]) {
            ++child;
        }
        if (root_value >= values[child]) {
            break;
        }
        values[root] = values[child];
        root = child;
        child = root * 2 + 1;
    }
    values[root] = root_value;
    return DS_STATUS_OK;
}

/* 功能：从最后一个分支结点向根逐个调整以构建最大堆（正文 BuildMaxHeap，PDF 第365页，书页第353页）。 */
DsStatus ch08_build_max_heap(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t i = length / 2; i > 0; --i) {
        (void)ch08_heap_adjust(values, length, i - 1);
    }
    return DS_STATUS_OK;
}

/* 功能：反复输出堆顶并重建剩余元素的最大堆（正文 HeapSort，PDF 第365页，书页第353页）。 */
DsStatus ch08_heap_sort(int *values, size_t length) {
    DsStatus status = ch08_build_max_heap(values, length);
    if (status != DS_STATUS_OK) {
        return status;
    }
    for (size_t i = length; i > 1; --i) {
        ch08_swap_values(&values[0], &values[i - 1]);
        (void)ch08_heap_adjust(values, i - 1, 0);
    }
    return DS_STATUS_OK;
}

/* 功能：合并两个相邻有序区间 [first,middle) 与 [middle,last)（正文 Merge，PDF 第376页，书页第364页）。 */
DsStatus ch08_merge_sorted_ranges(int *values, size_t length, size_t first,
                                  size_t middle, size_t last) {
    if ((length > 0 && values == NULL) || first > middle || middle > last ||
        last > length) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    const size_t count = last - first;
    if (count < 2) {
        return DS_STATUS_OK;
    }
    if (count > SIZE_MAX / sizeof(int)) {
        return DS_STATUS_OVERFLOW;
    }
    int *buffer = (int *)malloc(count * sizeof(int));
    if (buffer == NULL) {
        return DS_STATUS_NO_MEMORY;
    }
    for (size_t i = 0; i < count; ++i) {
        buffer[i] = values[first + i];
    }
    size_t left = 0;
    size_t right = middle - first;
    size_t output = first;
    const size_t end = count;
    while (left < middle - first && right < end) {
        values[output++] = buffer[left] <= buffer[right]
                               ? buffer[left++] : buffer[right++];
    }
    while (left < middle - first) {
        values[output++] = buffer[left++];
    }
    while (right < end) {
        values[output++] = buffer[right++];
    }
    free(buffer);
    return DS_STATUS_OK;
}

/* 功能：递归分治并稳定合并有序区间（正文 MergeSort，PDF 第376页，书页第364页）。 */
DsStatus ch08_merge_sort(int *values, size_t length) {
    const DsStatus status = ch08_validate_array(values, length);
    if (status != DS_STATUS_OK || length < 2) {
        return status;
    }
    if (length > SIZE_MAX / sizeof(int)) {
        return DS_STATUS_OVERFLOW;
    }
    int *buffer = (int *)malloc(length * sizeof(int));
    if (buffer == NULL) {
        return DS_STATUS_NO_MEMORY;
    }
    ch08_merge_sort_range(values, buffer, 0, length);
    free(buffer);
    return DS_STATUS_OK;
}

/* 功能：按键值范围 [0,key_range) 执行稳定计数排序（正文 CountSort，PDF 第378–379页，书页第366–367页）。 */
DsStatus ch08_counting_sort(const int *values, size_t length, size_t key_range,
                            int *output) {
    if ((length > 0 && (values == NULL || output == NULL)) ||
        (length > 0 && key_range == 0)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (length == 0) {
        return DS_STATUS_OK;
    }
    if (key_range > SIZE_MAX / sizeof(size_t)) {
        return DS_STATUS_OVERFLOW;
    }
    size_t *counts = (size_t *)calloc(key_range, sizeof(size_t));
    if (counts == NULL) {
        return DS_STATUS_NO_MEMORY;
    }
    for (size_t i = 0; i < length; ++i) {
        if (values[i] < 0 || (size_t)values[i] >= key_range) {
            free(counts);
            return DS_STATUS_INVALID_VALUE;
        }
        ++counts[(size_t)values[i]];
    }
    size_t output_index = 0;
    for (size_t key = 0; key < key_range; ++key) {
        while (counts[key] > 0) {
            output[output_index++] = (int)key;
            --counts[key];
        }
    }
    free(counts);
    return DS_STATUS_OK;
}
