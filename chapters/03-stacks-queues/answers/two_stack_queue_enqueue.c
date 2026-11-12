#include "stack_algorithms.h"

#include <stdlib.h>

// 功能：初始化双栈队列；capacity 表示每个栈的最大容量。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100页；书页第88页。
bool TwoStackQueueInit(TwoStackQueue *queue, size_t capacity) {
    if (queue == NULL) {
        return false;
    }
    TwoStackQueueDestroy(queue);
    if (capacity > (size_t)-1 / sizeof(int)) {
        return false;
    }
    queue->capacity_per_stack = capacity;
    if (capacity == 0) {
        return true;
    }
    queue->input = (int *)malloc(capacity * sizeof(int));
    queue->output = (int *)malloc(capacity * sizeof(int));
    if (queue->input == NULL || queue->output == NULL) {
        TwoStackQueueDestroy(queue);
        return false;
    }
    return true;
}

// 功能：输入栈未满时直接入栈；输入栈已满且输出栈空时先倒栈再入栈，否则失败。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100页；书页第88页。
bool TwoStackQueueEnQueue(TwoStackQueue *queue, int value) {
    if (queue == NULL || queue->capacity_per_stack == 0 ||
        queue->input == NULL || queue->output == NULL) {
        return false;
    }
    if (queue->input_size < queue->capacity_per_stack) {
        queue->input[queue->input_size++] = value;
        return true;
    }
    if (queue->output_size != 0) {
        return false;
    }
    while (queue->input_size > 0) {
        queue->output[queue->output_size++] = queue->input[--queue->input_size];
    }
    queue->input[queue->input_size++] = value;
    return true;
}
