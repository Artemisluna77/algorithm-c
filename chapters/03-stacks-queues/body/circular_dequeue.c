#include "circular_queue.h"
#include <stddef.h>

// 功能：从循环队列头部取出元素并循环移动 front，空队列时失败。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90–91页；书页第78–79页。
bool DeQueue(CircularQueue *queue, int *value) {
    if (!CircularQueueHasValidIndices(queue) || value == NULL ||
        queue->rear == queue->front) {
        return false;
    }
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % CIRCULAR_QUEUE_MAX_SIZE;
    return true;
}
