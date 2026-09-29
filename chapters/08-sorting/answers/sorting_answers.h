#ifndef CH08_SORTING_ANSWERS_H
#define CH08_SORTING_ANSWERS_H

#include "../body/sorting_algorithms.h"
#include "../questions/sorting_question_types.h"

#include <stddef.h>

typedef struct DsIntNode {
    int value;
    struct DsIntNode *next;
} DsIntNode;

typedef struct DsPriorityQueue {
    PriorityQueueElement *heap;
    size_t size;
    size_t capacity;
} DsPriorityQueue;

/* 功能：将偶数划到左侧、奇数划到右侧（答案 8.3.4 第01题，PDF 第360–361页，书页第348–349页）。 */
DsStatus ch08_move_even_before_odd(int *values, size_t length);
/* 功能：用快速划分选择第 k 小元素，k 从 1 开始（答案 8.3.4 第02题，PDF 第361页，书页第349页）。 */
DsStatus ch08_kth_element(const int *values, size_t length, size_t k, int *result);
/* 功能：用三指针将红、白、蓝分别整理到对应区段（答案 8.3.4 第03题，PDF 第361–362页，书页第349–350页）。 */
DsStatus ch08_arrange_flag(Color *colors, size_t length);
/* 功能：把前 floor(n/2) 个较小元素划到左区并输出右区和减左区和（答案 8.3.4 第04题，PDF 第362–363页，书页第350–351页）。 */
DsStatus ch08_partition_for_balance(int *values, size_t length, int *difference);
/* 功能：反复摘取最大结点并头插到结果链表；返回重排后的链表头（答案 8.4.3 第05题，PDF 第374页，书页第362页）。 */
DsIntNode *ch08_linked_list_selection_sort(DsIntNode *head);
/* 功能：判断顺序存储数组是否满足小根堆性质（答案 8.4.3 第06题，PDF 第374页，书页第362页）。 */
int ch08_is_min_heap(const int *values, size_t length);
/* 功能：初始化固定容量最大堆优先队列（答案 8.4.3 第07题，PDF 第374页，书页第362页）。首次调用传入未持有堆内存的结构体；重复初始化前须先 destroy。 */
DsStatus ch08_priority_queue_init(DsPriorityQueue *queue, size_t capacity);
/* 功能：释放优先队列占用的动态数组（答案 8.4.3 第07题，PDF 第374页，书页第362页）。 */
void ch08_priority_queue_destroy(DsPriorityQueue *queue);
/* 功能：按优先级插入元素，队列满时返回 DS_STATUS_FULL（答案 8.4.3 第07题，PDF 第374页，书页第362页）。 */
DsStatus ch08_priority_queue_enqueue(DsPriorityQueue *queue,
                                     PriorityQueueElement element);
/* 功能：移除并返回最高优先级元素，队列空时返回 DS_STATUS_EMPTY（答案 8.4.3 第07题，PDF 第374–375页，书页第362–363页）。 */
DsStatus ch08_priority_queue_dequeue(DsPriorityQueue *queue,
                                     PriorityQueueElement *result);
/* 功能：将已有序前缀之后的元素逐个插入前缀（答案 8.6.3 第02题，PDF 第391–392页，书页第379–380页）。 */
DsStatus ch08_insertion_sort_suffix(int *values, size_t length,
                                    size_t sorted_prefix_length);
/* 功能：以末元素为枢轴执行快速排序划分并输出最终下标（答案 8.6.3 第03题，PDF 第392页，书页第380页）。 */
DsStatus ch08_partition_last_pivot(int *values, size_t length,
                                   size_t *pivot_index);
/* 功能：稳定处理一对关键字，相等时让原序列中靠前元素保留较小秩（答案 8.5.4 第03题，PDF 第385页，书页第373页）。 */
DsStatus ch08_count_stable_pair(int left_value, int right_value,
                                size_t *left_count, size_t *right_count);
#endif
