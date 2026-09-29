#include "linked_queue.h"

#include <stdlib.h>

// 功能：创建新结点并插入链式队列尾部，再更新 rear。
// 来源：《2027数据结构》第3章 3.2.3；PDF第92页；书页第80页。
bool LinkedEnQueue(LinkedQueue *queue, int value) {
    LinkQueueNode *node;
    if (queue == NULL || !queue->initialized || queue->rear == NULL) {
        return false;
    }
    node = (LinkQueueNode *)malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }
    node->data = value;
    node->next = NULL;
    queue->rear->next = node;
    queue->rear = node;
    return true;
}
