#ifndef CH03_STACK_ALGORITHMS_H
#define CH03_STACK_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

#define TAGGED_CIRCULAR_QUEUE_MAX_SIZE 50

// 功能：判断由 I（入栈）和 O（出栈）组成的操作序列是否合法。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题03答案；PDF第86页；书页第74页。
bool JudgeStackSequence(const char *operations);

// 功能：用栈保存字符序列前半段并与后半段比较，判断序列是否对称。
// 来源：《2027数据结构》第3章 3.1.4 综合应用题04答案；PDF第86页；书页第74页。
bool IsLinkedListPalindrome(const char *values, size_t length);

// 功能：将队列元素依次出队入栈，再依次出栈入队，以反转连续存储的队列元素。
// 返回 false 表示参数无效或无法分配辅助栈；失败时不修改数组。
// 来源：《2027数据结构》第3章 3.2.5 综合应用题02答案；PDF第100页；书页第88页。
bool InverseQueue(int *queue, size_t length);

// 功能：表示通过 front、rear 与 tag 区分队空和队满的循环队列。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题01答案；PDF第99页；书页第87页。
typedef struct {
    int data[TAGGED_CIRCULAR_QUEUE_MAX_SIZE];
    int front;
    int rear;
    int tag;
} TaggedCircularQueue;

// 功能：在使用 tag 区分队空与队满的循环队列中入队。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题01答案；PDF第99页；书页第87页。
bool TaggedEnQueue(TaggedCircularQueue *queue, int value);

// 功能：在使用 tag 区分队空与队满的循环队列中出队。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题01答案；PDF第99–100页；书页第87–88页。
bool TaggedDeQueue(TaggedCircularQueue *queue, int *value);

// 功能：用两个动态数组栈实现 FIFO 队列；初始化后由此结构独占两个数组；不可按值复制，使用后必须销毁。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100–101页；书页第88–89页。
typedef struct {
    int *input;
    int *output;
    size_t capacity_per_stack;
    size_t input_size;
    size_t output_size;
} TwoStackQueue;

// 功能：初始化双栈队列；首次调用前 queue 必须零初始化，失败时资源保持为空。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100页；书页第88页。
bool TwoStackQueueInit(TwoStackQueue *queue, size_t capacity);

// 功能：释放双栈队列拥有的存储，并将结构恢复为空状态。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；C17 资源管理辅助操作。
void TwoStackQueueDestroy(TwoStackQueue *queue);

// 功能：输入栈未满时直接入栈；输入栈已满且输出栈空时先倒栈再入栈，否则失败。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100页；书页第88页。
bool TwoStackQueueEnQueue(TwoStackQueue *queue, int value);

// 功能：从双栈队列中弹出队首；队列为空或参数无效时返回 false。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第100–101页；书页第88–89页。
bool TwoStackQueueDeQueue(TwoStackQueue *queue, int *value);

// 功能：判断双栈队列是否为空；空指针或未初始化结构按空队列处理。
// 来源：《2027数据结构》第3章 3.2.6 综合应用题03答案；PDF第101页；书页第89页。
bool TwoStackQueueEmpty(const TwoStackQueue *queue);

#endif
