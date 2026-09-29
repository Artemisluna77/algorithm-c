#include "linked_queue.h"

#include <stdlib.h>

// 功能：删除头结点后的首个数据结点并返回其值，移除末结点时恢复 rear。
// 来源：《2027数据结构》第3章 3.2.3；PDF第92页；书页第80页。
bool LinkedDeQueue(LinkedQueue *queue, int *value) {
    LinkQueueNode *first;
    if (queue == NULL || value == NULL || !queue->initialized ||
        queue->rear == NULL || queue->header.next == NULL) {
        return false;
    }
    first = queue->header.next;
    *value = first->data;
    queue->header.next = first->next;
    if (queue->rear == first) {
        queue->rear = &queue->header;
    }
    free(first);
    return true;
}
