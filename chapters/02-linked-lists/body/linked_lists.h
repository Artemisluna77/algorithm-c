#ifndef CHAPTER02_LINKED_LISTS_H
#define CHAPTER02_LINKED_LISTS_H

#include <stdbool.h>
#include <stddef.h>

// 功能：定义单链表结点，数据域保存元素，指针域指向后继结点。
// 来源：《2027数据结构》第2章 2.3.1；PDF第43页；书页第31页。
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;

typedef struct SinglyLinkedList {
    LNode *head;
    bool with_header;
} SinglyLinkedList;

// 功能：初始化带头结点或不带头结点的单链表；首次初始化前须清零，重初始化前须先销毁。
// 来源：《2027数据结构》第2章 2.3.1–2.3.2；PDF第43-47页；书页第31-35页。
int SinglyLinkedListInit(SinglyLinkedList *list, bool with_header);

// 功能：释放单链表拥有的全部结点并清空状态。
void SinglyLinkedListDestroy(SinglyLinkedList *list);

// 功能：取得首个数据结点，不带头结点时 head 本身就是首结点。
LNode *SinglyLinkedListFirst(const SinglyLinkedList *list);

// 功能：统计单链表数据结点数量。
size_t SinglyLinkedListLength(const SinglyLinkedList *list);

// 功能：按次序将链表数据复制到调用方缓冲区，返回实际复制数量。
size_t SinglyLinkedListCopyValues(const SinglyLinkedList *list, int *output, size_t capacity);

// 功能：在链表末尾添加一个数据结点。
int SinglyLinkedListAppend(SinglyLinkedList *list, int value);

// 功能：清空数据结点，但保留原有头结点形态。
void SinglyLinkedListClear(SinglyLinkedList *list);

// 功能：按序号查找结点；带头结点时 0 为头结点、1 为首个数据结点；不带头结点时 0 为首个数据结点。
LNode *GetElem(SinglyLinkedList *list, size_t i);

// 功能：从首个数据结点开始按值查找，返回匹配结点或空指针。
LNode *LocateElemLinked(SinglyLinkedList *list, int value);

// 功能：在带头结点单链表第 i 个（一基）位置插入结点。
int LinkedListInsert(SinglyLinkedList *list, size_t i, int value);

// 功能：删除带头结点单链表第 i 个（一基）数据结点并返回其值。
int LinkedListDelete(SinglyLinkedList *list, size_t i, int *removed_value);

// 功能：按输入序列头插建表，遇到结束标记时停止；输出须先清零。
// 来源：《2027数据结构》第2章 2.3.2；PDF第47页；书页第35页。
int List_HeadInsert(SinglyLinkedList *list, const int *input, size_t input_length, int terminator);

// 功能：按输入序列尾插建表，遇到结束标记时停止；输出须先清零。
// 来源：《2027数据结构》第2章 2.3.2；PDF第47页；书页第35页。
int List_TailInsert(SinglyLinkedList *list, const int *input, size_t input_length, int terminator);

// 功能：定义双链表结点，prior 和 next 分别指向直接前驱与后继。
// 来源：《2027数据结构》第2章 2.3.3；PDF第48页；书页第36页。
typedef struct DNode {
    int data;
    struct DNode *prior;
    struct DNode *next;
} DNode;

typedef struct DoublyLinkedList {
    DNode *head;
} DoublyLinkedList;

// 功能：初始化带头结点的非循环双链表；首次初始化前须清零，重初始化前须先销毁。
// 来源：《2027数据结构》第2章 2.3.3；PDF第48-49页；书页第36-37页。
int DoublyLinkedListInit(DoublyLinkedList *list);

// 功能：释放双链表数据结点和头结点。
void DoublyLinkedListDestroy(DoublyLinkedList *list);

// 功能：在双链表末尾追加结点并返回新结点。
DNode *DoublyLinkedListAppend(DoublyLinkedList *list, int value);

// 功能：在给定结点之后插入新结点，按书中顺序连接 next 与 prior。
DNode *DoublyLinkedListInsertAfter(DNode *position, int value);

// 功能：删除给定结点之后的结点并通过指针返回其值。
int DoublyLinkedListEraseAfter(DNode *position, int *removed_value);

// 功能：定义静态链表结点数组，next 保存下一结点的数组下标，-1 表示链尾。
// 来源：《2027数据结构》第2章 2.3.5；PDF第50页；书页第38页。
typedef struct StaticNode {
    int data;
    int next;
} StaticNode;

typedef StaticNode StaticLinkedList[50];

#endif
