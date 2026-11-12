#include "circular_queue.h"
#include <stddef.h>

// 功能：将循环队列队头和队尾指针置为 0，建立空队列。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
void InitQueue(CircularQueue *queue) {
    if (queue != NULL) {
        queue->front = 0;
        queue->rear = 0;
    }
}
