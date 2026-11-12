#include "sorting_answers.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* 功能：按首元素枢轴划分区间，供第 k 小选择与平衡分组使用（答案辅助过程，PDF 第361–363页，书页第349–351页）。 */
static size_t ch08_partition_first(int *values, size_t low, size_t high) {
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
    return low;
}

/* 功能：累加一个 int 到 int64_t，并在发生溢出时返回失败（平衡分组的安全边界辅助过程）。 */
static int ch08_checked_add_i64(int64_t *sum, int value) {
    if ((value > 0 && *sum > INT64_MAX - value) ||
        (value < 0 && *sum < INT64_MIN - value)) {
        return 0;
    }
    *sum += value;
    return 1;
}

/* 功能：双指针交换，将偶数划到左侧、奇数划到右侧（答案 8.3.4 第01题，PDF 第360–361页，书页第348–349页）。 */
DsStatus ch08_move_even_before_odd(int *values, size_t length) {
    if (length > 0 && values == NULL) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    size_t left = 0;
    size_t right = length;
    while (left < right) {
        while (left < right && values[left] % 2 == 0) {
            ++left;
        }
        while (left < right && values[right - 1] % 2 != 0) {
            --right;
        }
        if (left < right) {
            ch08_swap_values(&values[left], &values[right - 1]);
            ++left;
            --right;
        }
    }
    return DS_STATUS_OK;
}

/* 功能：按快速划分选择第 k 小元素，k 从 1 开始且不修改调用方数组（答案 8.3.4 第02题，PDF 第361页，书页第349页）。 */
DsStatus ch08_kth_element(const int *values, size_t length, size_t k, int *result) {
    if (values == NULL || result == NULL || k == 0 || k > length ||
        length > SIZE_MAX / sizeof(int)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    int *copy = (int *)malloc(length * sizeof(int));
    if (copy == NULL) {
        return DS_STATUS_NO_MEMORY;
    }
    memcpy(copy, values, length * sizeof(int));
    size_t low = 0;
    size_t high = length - 1;
    const size_t target = k - 1;
    while (low <= high) {
        const size_t pivot = ch08_partition_first(copy, low, high);
        if (pivot == target) {
            *result = copy[pivot];
            free(copy);
            return DS_STATUS_OK;
        }
        if (pivot > target) {
            if (pivot == 0) {
                break;
            }
            high = pivot - 1;
        } else {
            low = pivot + 1;
        }
    }
    free(copy);
    return DS_STATUS_INVALID_VALUE;
}

/* 功能：用三指针一次扫描把红、白、蓝分别放到对应区段（答案 8.3.4 第03题，PDF 第361–362页，书页第349–350页）。 */
DsStatus ch08_arrange_flag(Color *colors, size_t length) {
    if (length > 0 && colors == NULL) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    for (size_t i = 0; i < length; ++i) {
        if (colors[i] != COLOR_RED && colors[i] != COLOR_WHITE &&
            colors[i] != COLOR_BLUE) {
            return DS_STATUS_INVALID_VALUE;
        }
    }
    size_t red_end = 0;
    size_t current = 0;
    size_t blue_begin = length;
    while (current < blue_begin) {
        switch (colors[current]) {
            case COLOR_RED:
                if (red_end != current) {
                    const Color temporary = colors[red_end];
                    colors[red_end] = colors[current];
                    colors[current] = temporary;
                }
                ++red_end;
                ++current;
                break;
            case COLOR_WHITE:
                ++current;
                break;
            case COLOR_BLUE:
                --blue_begin;
                if (current != blue_begin) {
                    const Color temporary = colors[current];
                    colors[current] = colors[blue_begin];
                    colors[blue_begin] = temporary;
                }
                break;
            default:
                return DS_STATUS_INVALID_VALUE;
        }
    }
    return DS_STATUS_OK;
}

/* 功能：用快速选择把前 floor(n/2) 个最小元素划到左区并计算两区和差（答案 8.3.4 第04题，PDF 第362–363页，书页第350–351页）。 */
DsStatus ch08_partition_for_balance(int *values, size_t length, int *difference) {
    if (values == NULL || difference == NULL || length < 2) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    const size_t left_count = length / 2;
    const size_t target = left_count - 1;
    size_t low = 0;
    size_t high = length - 1;
    for (;;) {
        const size_t pivot = ch08_partition_first(values, low, high);
        if (pivot == target) {
            break;
        }
        if (pivot < target) {
            low = pivot + 1;
        } else {
            if (pivot == 0) {
                return DS_STATUS_INVALID_VALUE;
            }
            high = pivot - 1;
        }
    }

    int64_t left_sum = 0;
    int64_t right_sum = 0;
    for (size_t i = 0; i < left_count; ++i) {
        if (!ch08_checked_add_i64(&left_sum, values[i])) {
            return DS_STATUS_OVERFLOW;
        }
    }
    for (size_t i = left_count; i < length; ++i) {
        if (!ch08_checked_add_i64(&right_sum, values[i])) {
            return DS_STATUS_OVERFLOW;
        }
    }
    if ((left_sum < 0 && right_sum > INT64_MAX + left_sum) ||
        (left_sum > 0 && right_sum < INT64_MIN + left_sum)) {
        return DS_STATUS_OVERFLOW;
    }
    const int64_t result = right_sum - left_sum;
    if (result < INT_MIN || result > INT_MAX) {
        return DS_STATUS_OVERFLOW;
    }
    *difference = (int)result;
    return DS_STATUS_OK;
}

/* 功能：反复从单链表摘取最大结点并头插到结果链表（答案 8.4.3 第05题，PDF 第374页，书页第362页）。 */
DsIntNode *ch08_linked_list_selection_sort(DsIntNode *head) {
    DsIntNode *sorted = NULL;
    while (head != NULL) {
        DsIntNode *previous_max = NULL;
        DsIntNode *previous = NULL;
        DsIntNode *maximum = head;
        for (DsIntNode *current = head; current != NULL;
             previous = current, current = current->next) {
            if (current->value > maximum->value) {
                maximum = current;
                previous_max = previous;
            }
        }
        if (previous_max == NULL) {
            head = maximum->next;
        } else {
            previous_max->next = maximum->next;
        }
        maximum->next = sorted;
        sorted = maximum;
    }
    return sorted;
}

/* 功能：逐个检查父子关键字以判定小根堆（答案 8.4.3 第06题，PDF 第374页，书页第362页）。 */
int ch08_is_min_heap(const int *values, size_t length) {
    if (length > 0 && values == NULL) {
        return 0;
    }
    for (size_t child = 1; child < length; ++child) {
        const size_t parent = (child - 1) / 2;
        if (values[parent] > values[child]) {
            return 0;
        }
    }
    return 1;
}

/* 功能：建立固定容量最大堆优先队列（答案 8.4.3 第07题，PDF 第374页，书页第362页）。 */
DsStatus ch08_priority_queue_init(DsPriorityQueue *queue, size_t capacity) {
    if (queue == NULL || capacity > SIZE_MAX / sizeof(PriorityQueueElement)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    queue->heap = capacity == 0
                      ? NULL
                      : (PriorityQueueElement *)malloc(
                            capacity * sizeof(PriorityQueueElement));
    if (capacity > 0 && queue->heap == NULL) {
        queue->size = 0;
        queue->capacity = 0;
        return DS_STATUS_NO_MEMORY;
    }
    queue->size = 0;
    queue->capacity = capacity;
    return DS_STATUS_OK;
}

/* 功能：释放优先队列数组并清空队列状态（答案 8.4.3 第07题的 C 资源管理接口，PDF 第374页，书页第362页）。 */
void ch08_priority_queue_destroy(DsPriorityQueue *queue) {
    if (queue != NULL) {
        free(queue->heap);
        queue->heap = NULL;
        queue->size = 0;
        queue->capacity = 0;
    }
}

/* 功能：把新元素追加到堆尾并向上调整（答案 8.4.3 第07题入队代码，PDF 第374页，书页第362页）。 */
DsStatus ch08_priority_queue_enqueue(DsPriorityQueue *queue,
                                     PriorityQueueElement element) {
    if (queue == NULL || (queue->capacity > 0 && queue->heap == NULL)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (queue->size >= queue->capacity) {
        return DS_STATUS_FULL;
    }
    size_t child = queue->size++;
    queue->heap[child] = element;
    while (child > 0) {
        const size_t parent = (child - 1) / 2;
        if (queue->heap[parent].priority >= queue->heap[child].priority) {
            break;
        }
        const PriorityQueueElement temporary = queue->heap[parent];
        queue->heap[parent] = queue->heap[child];
        queue->heap[child] = temporary;
        child = parent;
    }
    return DS_STATUS_OK;
}

/* 功能：移除堆顶并将堆尾元素向下调整（答案 8.4.3 第07题出队代码，PDF 第374–375页，书页第362–363页）。 */
DsStatus ch08_priority_queue_dequeue(DsPriorityQueue *queue,
                                     PriorityQueueElement *result) {
    if (queue == NULL || result == NULL ||
        (queue->capacity > 0 && queue->heap == NULL)) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (queue->size == 0) {
        return DS_STATUS_EMPTY;
    }
    *result = queue->heap[0];
    --queue->size;
    if (queue->size == 0) {
        return DS_STATUS_OK;
    }
    queue->heap[0] = queue->heap[queue->size];
    size_t parent = 0;
    while (parent <= (queue->size - 1) / 2) {
        const size_t left = parent * 2 + 1;
        if (left >= queue->size) {
            break;
        }
        size_t child = left;
        const size_t right = left + 1;
        if (right < queue->size &&
            queue->heap[left].priority < queue->heap[right].priority) {
            child = right;
        }
        if (queue->heap[parent].priority >= queue->heap[child].priority) {
            break;
        }
        const PriorityQueueElement temporary = queue->heap[parent];
        queue->heap[parent] = queue->heap[child];
        queue->heap[child] = temporary;
        parent = child;
    }
    return DS_STATUS_OK;
}

/* 功能：将已有序前缀之后的元素依次插入前面的有序序列（答案 Insert_Sort，PDF 第391–392页，书页第379–380页）。 */
DsStatus ch08_insertion_sort_suffix(int *values, size_t length,
                                    size_t sorted_prefix_length) {
    if ((length > 0 && values == NULL) || sorted_prefix_length > length) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    for (size_t i = 1; i < sorted_prefix_length; ++i) {
        if (values[i - 1] > values[i]) {
            return DS_STATUS_INVALID_VALUE;
        }
    }
    for (size_t i = sorted_prefix_length; i < length; ++i) {
        const int key = values[i];
        size_t j = i;
        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = key;
    }
    return DS_STATUS_OK;
}

/* 功能：使用最后一个元素作枢轴并交替扫描划分（答案 Partition，PDF 第392页，书页第380页）。 */
DsStatus ch08_partition_last_pivot(int *values, size_t length,
                                   size_t *pivot_index) {
    if (values == NULL || pivot_index == NULL || length == 0) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    size_t low = 0;
    size_t high = length - 1;
    const int pivot = values[high];
    while (low < high) {
        while (low < high && values[low] <= pivot) {
            ++low;
        }
        if (low < high) {
            values[high] = values[low];
        }
        while (low < high && values[high] >= pivot) {
            --high;
        }
        if (low < high) {
            values[low] = values[high];
        }
    }
    values[low] = pivot;
    *pivot_index = low;
    return DS_STATUS_OK;
}

/* 功能：处理印刷答案中用于修正相等关键字稳定性的两行分支（答案 8.5.4 第03题，PDF 第385页，书页第373页）。 */
DsStatus ch08_count_stable_pair(int left_value, int right_value,
                                size_t *left_count, size_t *right_count) {
    if (left_count == NULL || right_count == NULL) {
        return DS_STATUS_INVALID_ARGUMENT;
    }
    if (left_value <= right_value) {
        if (*right_count == SIZE_MAX) {
            return DS_STATUS_OVERFLOW;
        }
        ++*right_count;
    } else {
        if (*left_count == SIZE_MAX) {
            return DS_STATUS_OVERFLOW;
        }
        ++*left_count;
    }
    return DS_STATUS_OK;
}
