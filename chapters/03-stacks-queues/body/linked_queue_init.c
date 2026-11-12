#include "linked_queue.h"
#include <stdlib.h>
#include <stddef.h>

// 功能：初始化链式队列头结点，并令 front 与 rear 同指向头结点。
// 来源：《2027数据结构》第3章 3.2.3；PDF第91页；书页第79页。
void InitLinkedQueue(LinkedQueue *queue) {
    if (queue != NULL) {
        if (queue->initialized) {
            DestroyLinkedQueue(queue);
        }
        queue->header.data = 0;
        queue->header.next = NULL;
        queue->rear = &queue->header;
        queue->initialized = true;
    }
}

// 功能：释放队列拥有的全部数据结点并恢复为空队列。
// 来源：《2027数据结构》第3章 3.2.3；C17 资源管理辅助操作。
void DestroyLinkedQueue(LinkedQueue *queue) {
    LinkQueueNode *node;
    if (queue == NULL || !queue->initialized) {
        return;
    }
    node = queue->header.next;
    while (node != NULL) {
        LinkQueueNode *next = node->next;
        free(node);
        node = next;
    }
    queue->header.next = NULL;
    queue->rear = &queue->header;
    queue->initialized = false;
}
