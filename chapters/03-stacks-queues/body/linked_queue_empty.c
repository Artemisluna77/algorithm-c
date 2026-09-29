#include "linked_queue.h"
#include <stddef.h>

// 功能：当 front 与 rear 同指向头结点时判定链式队列为空。
// 来源：《2027数据结构》第3章 3.2.3；PDF第91–92页；书页第79–80页。
bool LinkedQueueEmpty(const LinkedQueue *queue) {
    return queue == NULL || !queue->initialized ||
           queue->header.next == NULL;
}
