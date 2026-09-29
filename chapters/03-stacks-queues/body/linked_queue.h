#ifndef CH03_LINKED_QUEUE_H
#define CH03_LINKED_QUEUE_H

#include <stdbool.h>

// 功能：定义链式队列结点及带头结点的队列，front 是内嵌头结点，rear 指向尾结点；初始化后不可按值复制队列。
// 来源：《2027数据结构》第3章 3.2.3；PDF第91页；书页第79页。
typedef struct LinkQueueNode {
    int data;
    struct LinkQueueNode *next;
} LinkQueueNode;

typedef struct {
    LinkQueueNode header;
    LinkQueueNode *rear;
    bool initialized;
} LinkedQueue;

// 功能：初始化带头结点的空链式队列；队列对象需先零初始化或已初始化。
// 来源：《2027数据结构》第3章 3.2.3；PDF第91页；书页第79页。
void InitLinkedQueue(LinkedQueue *queue);

// 功能：释放队列拥有的全部数据结点并将其恢复为未初始化状态。
// 来源：《2027数据结构》第3章 3.2.3；C17 资源管理辅助操作。
void DestroyLinkedQueue(LinkedQueue *queue);

// 功能：判断带头结点的链式队列是否为空。
// 来源：《2027数据结构》第3章 3.2.3；PDF第91–92页；书页第79–80页。
bool LinkedQueueEmpty(const LinkedQueue *queue);

// 功能：在链式队列尾部创建结点并入队；内存不足或队列未初始化时返回 false。
// 来源：《2027数据结构》第3章 3.2.3；PDF第92页；书页第80页。
bool LinkedEnQueue(LinkedQueue *queue, int value);

// 功能：从链式队列头部取出并释放结点；空队列或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.2.3；PDF第92页；书页第80页。
bool LinkedDeQueue(LinkedQueue *queue, int *value);

#endif
