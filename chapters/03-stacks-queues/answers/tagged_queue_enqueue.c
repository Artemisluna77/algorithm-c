#include "stack_algorithms.h"
#include <stddef.h>

// 功能：用 front、rear 和 tag 判满，并将元素写入循环队列尾端。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题01答案；PDF第99页；书页第87页。
bool TaggedEnQueue(TaggedCircularQueue *queue, int value) {
    if (queue == NULL || queue->front < 0 ||
        queue->front >= TAGGED_CIRCULAR_QUEUE_MAX_SIZE || queue->rear < 0 ||
        queue->rear >= TAGGED_CIRCULAR_QUEUE_MAX_SIZE ||
        (queue->tag != 0 && queue->tag != 1)) {
        return false;
    }
    if (queue->front == queue->rear && queue->tag == 1) {
        return false;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % TAGGED_CIRCULAR_QUEUE_MAX_SIZE;
    queue->tag = 1;
    return true;
}
