#include "stack_algorithms.h"
#include <stddef.h>

// 功能：用 front、rear 和 tag 判空，再从循环队列头端取出元素。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题01答案；PDF第99–100页；书页第87–88页。
bool TaggedDeQueue(TaggedCircularQueue *queue, int *value) {
    if (queue == NULL || value == NULL || queue->front < 0 ||
        queue->front >= TAGGED_CIRCULAR_QUEUE_MAX_SIZE || queue->rear < 0 ||
        queue->rear >= TAGGED_CIRCULAR_QUEUE_MAX_SIZE ||
        (queue->tag != 0 && queue->tag != 1)) {
        return false;
    }
    if (queue->front == queue->rear && queue->tag == 0) {
        return false;
    }
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % TAGGED_CIRCULAR_QUEUE_MAX_SIZE;
    queue->tag = 0;
    return true;
}
