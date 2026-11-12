#include "circular_queue.h"
#include <stddef.h>

// 功能：在循环队列尾部插入元素，预留一个空单元检测队满并循环移动 rear。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
bool EnQueue(CircularQueue *queue, int value) {
    int next_rear;
    if (!CircularQueueHasValidIndices(queue)) {
        return false;
    }
    next_rear = (queue->rear + 1) % CIRCULAR_QUEUE_MAX_SIZE;
    if (next_rear == queue->front) {
        return false;
    }
    queue->data[queue->rear] = value;
    queue->rear = next_rear;
    return true;
}
