#include "stack_algorithms.h"
#include <stddef.h>

// 功能：输出栈非空时直接弹出；否则将输入栈倒入输出栈后弹出队首。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100–101页；书页第88–89页。
bool TwoStackQueueDeQueue(TwoStackQueue *queue, int *value) {
    if (queue == NULL || value == NULL ||
        (queue->capacity_per_stack != 0 &&
         (queue->input == NULL || queue->output == NULL))) {
        return false;
    }
    if (queue->output_size == 0) {
        while (queue->input_size > 0) {
            queue->output[queue->output_size++] =
                queue->input[--queue->input_size];
        }
    }
    if (queue->output_size == 0) {
        return false;
    }
    *value = queue->output[--queue->output_size];
    return true;
}
