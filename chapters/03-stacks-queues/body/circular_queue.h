#ifndef CH03_CIRCULAR_QUEUE_H
#define CH03_CIRCULAR_QUEUE_H

#include <stdbool.h>
#include <stddef.h>

#define CIRCULAR_QUEUE_MAX_SIZE 50

// 功能：定义 front 指向队首元素、rear 指向队尾后一个位置的顺序循环队列。
// 来源：《2027数据结构》第3章 3.2.2；PDF第89页；书页第77页。
typedef struct {
    int data[CIRCULAR_QUEUE_MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

// 功能：检查循环队列非空指针及 front、rear 下标是否有效，供各操作共享。
static inline bool CircularQueueHasValidIndices(const CircularQueue *queue) {
    return queue != NULL && queue->front >= 0 &&
           queue->front < CIRCULAR_QUEUE_MAX_SIZE && queue->rear >= 0 &&
           queue->rear < CIRCULAR_QUEUE_MAX_SIZE;
}

// 功能：初始化循环队列的队首和队尾指针。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
void InitQueue(CircularQueue *queue);

// 功能：判断循环队列是否为空；空指针或索引损坏时返回 true。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
bool QueueEmpty(const CircularQueue *queue);

// 功能：将元素加入循环队列尾部，采用牺牲一个存储单元区分队空与队满。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90页；书页第78页。
bool EnQueue(CircularQueue *queue, int value);

// 功能：从循环队列头部取出元素，队空或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.2.2；PDF第90–91页；书页第78–79页。
bool DeQueue(CircularQueue *queue, int *value);

#endif
