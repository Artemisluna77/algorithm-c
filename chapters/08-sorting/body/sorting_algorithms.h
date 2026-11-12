#ifndef CH08_SORTING_ALGORITHMS_H
#define CH08_SORTING_ALGORITHMS_H

#include <stddef.h>

typedef enum DsStatus {
    DS_STATUS_OK = 0,
    DS_STATUS_INVALID_ARGUMENT = 1,
    DS_STATUS_NO_MEMORY = 2,
    DS_STATUS_OVERFLOW = 3,
    DS_STATUS_EMPTY = 4,
    DS_STATUS_FULL = 5,
    DS_STATUS_INVALID_VALUE = 6
} DsStatus;

/* 功能：交换两个整数元素（正文冒泡排序脚注辅助代码，PDF 第352页，书页第340页）。 */
void ch08_swap_values(int *left, int *right);

/* 功能：按非降序执行直接插入排序（正文 8.2.1，PDF 第345页，书页约第333页）。 */
DsStatus ch08_insertion_sort(int *values, size_t length);
/* 功能：先折半查找插入位置，再后移元素排序（正文 8.2.2，PDF 第346页，书页第334页）。 */
DsStatus ch08_binary_insertion_sort(int *values, size_t length);
/* 功能：按逐次折半增量对各子序列执行希尔排序（正文 8.2.3，PDF 第347–348页，书页第335–336页）。 */
DsStatus ch08_shell_sort(int *values, size_t length);
/* 功能：从后向前冒泡并在一趟无交换时提前结束（正文 8.3.1，PDF 第352页，书页第340页）。 */
DsStatus ch08_bubble_sort(int *values, size_t length);
/* 功能：对闭区间 [low, high] 按首元素枢轴划分并写回枢轴下标（正文 8.3.2，PDF 第355页，书页第343页）。 */
DsStatus ch08_partition_first_pivot(int *values, size_t length, size_t low,
                                     size_t high, size_t *pivot_index);
/* 功能：使用首元素枢轴完成快速排序，并递归较小区间限制栈深度（正文 8.3.2，PDF 第355页，书页第343页）。 */
DsStatus ch08_quick_sort(int *values, size_t length);
/* 功能：按非降序执行简单选择排序（正文 8.4.1，PDF 第363页，书页第351页）。 */
DsStatus ch08_selection_sort(int *values, size_t length);
/* 功能：将以 root 为根的最大堆子树向下调整（正文 8.4.2，PDF 第365页，书页第353页）。 */
DsStatus ch08_heap_adjust(int *values, size_t length, size_t root);
/* 功能：将数组原地构建为最大堆（正文 8.4.2，PDF 第365页，书页第353页）。 */
DsStatus ch08_build_max_heap(int *values, size_t length);
/* 功能：原地执行最大堆排序（正文 8.4.2，PDF 第365页，书页第353页）。 */
DsStatus ch08_heap_sort(int *values, size_t length);
/* 功能：合并两个相邻有序半开区间 [first, middle) 与 [middle, last)（正文 8.5.1，PDF 第376页，书页第364页）。 */
DsStatus ch08_merge_sorted_ranges(int *values, size_t length, size_t first,
                                  size_t middle, size_t last);
/* 功能：以稳定二路归并排序数组（正文 8.5.1，PDF 第376页，书页第364页）。 */
DsStatus ch08_merge_sort(int *values, size_t length);
/* 功能：按键值范围 [0, key_range) 执行稳定计数排序（正文 8.5.3，PDF 第378–379页，书页第366–367页）。 */
DsStatus ch08_counting_sort(const int *values, size_t length, size_t key_range,
                            int *output);

#endif
