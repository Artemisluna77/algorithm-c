#ifndef CHAPTER02_SEQUENTIAL_ALGORITHMS_H
#define CHAPTER02_SEQUENTIAL_ALGORITHMS_H

#include "sequential_list.h"

#include <stddef.h>

// 功能：查找顺序表最小元素，以末元素填补被删除位置并通过指针返回最小值。
// 来源：《2027数据结构》第2章 2.2.4；PDF第34-35页；书页第22-23页。
int delete_minimum(SeqList *list, int *minimum);

// 功能：原地逆置顺序表元素。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void reverse_sequential_list(SeqList *list);

// 功能：通过压缩保留元素，删除顺序表中所有等于给定值的元素（解法一）。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void erase_value_by_compaction(SeqList *list, int value);

// 功能：统计已删除元素数量并前移后续元素，删除顺序表中所有等于给定值的元素（解法二）。
// 来源：《2027数据结构》第2章 2.2.4；PDF第35页；书页第23页。
void erase_value_by_counting(SeqList *list, int value);

// 功能：在非递减顺序表中原地删除重复元素，每个值只保留一个。
// 来源：《2027数据结构》第2章习题答案 Delete_Same；PDF第36页；书页第24页。
int erase_sorted_duplicates(SeqList *list);

// 功能：删除顺序表中值位于闭区间 [lower, upper] 的元素。
// 来源：《2027数据结构》第2章 2.2.4；PDF第36页；书页第24页。
int erase_closed_value_range(SeqList *list, int lower, int upper);

// 功能：将两个递增顺序表归并到有容量上限的第三个顺序表。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37页；书页第25页。
int merge_sorted_lists(const SeqList *left, const SeqList *right, SeqList *output);

// 功能：逆置数组指定闭区间，为三次逆置的循环左移算法提供基础操作。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37-39页；书页第25-27页。
void reverse_segment(int *values, size_t length, size_t left, size_t right);

// 功能：通过逆置前段、后段和整体，交换数组中相邻的两个数据块。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37页；书页第25页。
void exchange_adjacent_blocks(int *values, size_t length, size_t first_block_size);

// 功能：在递增数组中二分查找目标值；命中时与后继交换，未命中时插入到有序位置。
// 返回 1 表示命中，0 表示已插入，-1 表示参数非法或容量不足。
// 来源：《2027数据结构》第2章 2.2.4；PDF第37-38页；书页第25-26页。
int search_exchange_insert(int *sorted_values, size_t *length, size_t capacity, int value);

// 功能：用三个下标同步扫描递增数组，返回三者共有的不同值。
// 成功返回 1 并设置输出长度，缓冲区不足或参数非法返回 0。
// 来源：《2027数据结构》第2章 2.2.4；PDF第38页；书页第26页。
int common_values_in_three_sorted_arrays(const int *a, size_t a_length,
                                         const int *b, size_t b_length,
                                         const int *c, size_t c_length,
                                         int *common, size_t capacity,
                                         size_t *common_length);

// 功能：通过三次逆置将数组循环左移 distance 个位置。
// 来源：《2027数据结构》第2章 2.2.4；PDF第38-39页；书页第26-27页。
void rotate_left_by_reversal(int *values, size_t length, size_t distance);

// 功能：对两个等长递增数组使用二分划分，求合并后第 n 小的元素；无效输入返回 0。
// 来源：《2027数据结构》第2章 2.2.4；PDF第39-40页；书页第27-28页。
int median_of_two_equal_sorted_arrays(const int *a, size_t a_length,
                                      const int *b, size_t b_length, int *median);

// 功能：用候选值抵消法查找主元素，并再次计数确认其出现次数超过一半。
// 来源：《2027数据结构》第2章 2.2.4；PDF第40页；书页第28页。
int majority_element(const int *values, size_t length, int *majority);

// 功能：使用长度为 n 的标记数组找出数组中未出现的最小正整数；分配失败或结果不可表示时返回 0。
// 来源：《2027数据结构》第2章 2.2.4；PDF第41页；书页第29页。
int smallest_missing_positive(const int *values, size_t length);

// 功能：同步推进三个递增数组中当前最小值的下标，求三元组两两距离和的最小值。
// 来源：《2027数据结构》第2章 2.2.4；PDF第42页；书页第30页。
long long minimum_three_array_distance(const int *a, size_t a_length,
                                       const int *b, size_t b_length,
                                       const int *c, size_t c_length);

// 功能：从右向左维护后缀最大、最小值，按当前元素符号计算其与极值的乘积。
// 来源：《2027数据结构》第2章 2.2.4；PDF第33、42页；书页第21、30页。
void multiply_by_suffix_extreme(const int *values, size_t length, long long *output);

#endif
