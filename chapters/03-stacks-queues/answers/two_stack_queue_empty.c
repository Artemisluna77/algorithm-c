#include "stack_algorithms.h"
#include <stdlib.h>
#include <stddef.h>

// 功能：当输入栈和输出栈均为空时判定双栈队列为空。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第101页；书页第89页。
bool TwoStackQueueEmpty(const TwoStackQueue *queue) {
    return queue == NULL || (queue->input_size == 0 && queue->output_size == 0);
}

// 功能：释放双栈队列拥有的存储，并将结构恢复为空状态。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；C17 资源管理辅助操作。
void TwoStackQueueDestroy(TwoStackQueue *queue) {
    if (queue != NULL) {
        free(queue->input);
        free(queue->output);
        queue->input = NULL;
        queue->output = NULL;
        queue->capacity_per_stack = 0;
        queue->input_size = 0;
        queue->output_size = 0;
    }
}
