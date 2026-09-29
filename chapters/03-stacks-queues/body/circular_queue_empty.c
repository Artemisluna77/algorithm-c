#include "circular_queue.h"
#include <stddef.h>

// 功能：当循环队列的 front 与 rear 相等时判定队列为空。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
bool QueueEmpty(const CircularQueue *queue) {
    return !CircularQueueHasValidIndices(queue) || queue->rear == queue->front;
}
