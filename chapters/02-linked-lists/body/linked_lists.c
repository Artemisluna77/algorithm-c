#include "linked_lists.h"

#include <stdlib.h>

// 功能：初始化带头结点或不带头结点的单链表。
// 来源：《2027数据结构》第2章 2.3.2；PDF第43-44页；书页第31-32页。
int SinglyLinkedListInit(SinglyLinkedList *list, bool with_header) {
    if (list == NULL) return 0;
    list->head = NULL;
    list->with_header = with_header;
    if (with_header) {
        list->head = (LNode *)calloc(1, sizeof(LNode));
        if (list->head == NULL) return 0;
    }
    return 1;
}

// 功能：释放单链表拥有的全部结点并清空状态。
void SinglyLinkedListDestroy(SinglyLinkedList *list) {
    LNode *current;
    if (list == NULL) return;
    current = list->head;
    while (current != NULL) {
        LNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->with_header = false;
}

// 功能：取得首个数据结点。
LNode *SinglyLinkedListFirst(const SinglyLinkedList *list) {
    if (list == NULL || list->head == NULL) return NULL;
    return list->with_header ? list->head->next : list->head;
}

// 功能：统计单链表数据结点数量。
size_t SinglyLinkedListLength(const SinglyLinkedList *list) {
    size_t length = 0;
    LNode *current = SinglyLinkedListFirst(list);
    while (current != NULL) {
        ++length;
        current = current->next;
    }
    return length;
}

// 功能：按次序将链表数据复制到调用方缓冲区。
size_t SinglyLinkedListCopyValues(const SinglyLinkedList *list, int *output, size_t capacity) {
    size_t copied = 0;
    LNode *current = SinglyLinkedListFirst(list);
    if (output == NULL && capacity != 0) return 0;
    while (current != NULL && copied < capacity) {
        output[copied++] = current->data;
        current = current->next;
    }
    return copied;
}

// 功能：在链表末尾添加一个数据结点。
// 来源：《2027数据结构》第2章 2.3.2；PDF第47页；书页第35页。
int SinglyLinkedListAppend(SinglyLinkedList *list, int value) {
    LNode *node;
    LNode **link;
    if (list == NULL) return 0;
    node = (LNode *)malloc(sizeof(LNode));
    if (node == NULL) return 0;
    node->data = value;
    node->next = NULL;
    link = &list->head;
    while (*link != NULL) link = &(*link)->next;
    *link = node;
    return 1;
}

// 功能：清空数据结点，但保留原有头结点形态。
void SinglyLinkedListClear(SinglyLinkedList *list) {
    LNode *current;
    if (list == NULL) return;
    if (list->with_header) {
        if (list->head == NULL) return;
        current = list->head->next;
        list->head->next = NULL;
    } else {
        current = list->head;
        list->head = NULL;
    }
    while (current != NULL) {
        LNode *next = current->next;
        free(current);
        current = next;
    }
}

// 功能：按序号顺链遍历并返回结点指针。
// 来源：《2027数据结构》第2章 2.3.2；PDF第44页；书页第32页。
LNode *GetElem(SinglyLinkedList *list, size_t i) {
    LNode *current;
    size_t position = 0;
    if (list == NULL) return NULL;
    current = list->head;
    while (current != NULL && position < i) {
        current = current->next;
        ++position;
    }
    return current;
}

// 功能：从首个数据结点开始顺序查找给定值。
// 来源：《2027数据结构》第2章 2.3.2；PDF第44-45页；书页第32-33页。
LNode *LocateElemLinked(SinglyLinkedList *list, int value) {
    LNode *current = SinglyLinkedListFirst(list);
    while (current != NULL) {
        if (current->data == value) return current;
        current = current->next;
    }
    return NULL;
}

// 功能：在第 i 个（一基）位置插入新结点。
// 来源：《2027数据结构》第2章 2.3.2；PDF第45页；书页第33页。
int LinkedListInsert(SinglyLinkedList *list, size_t i, int value) {
    LNode *previous;
    LNode *node;
    size_t j;
    if (list == NULL || !list->with_header || list->head == NULL || i < 1) return 0;
    previous = list->head;
    for (j = 1; j < i && previous != NULL; ++j) previous = previous->next;
    if (previous == NULL) return 0;
    node = (LNode *)malloc(sizeof(LNode));
    if (node == NULL) return 0;
    node->data = value;
    node->next = previous->next;
    previous->next = node;
    return 1;
}

// 功能：删除第 i 个（一基）数据结点并返回被删值。
// 来源：《2027数据结构》第2章 2.3.2；PDF第46页；书页第34页。
int LinkedListDelete(SinglyLinkedList *list, size_t i, int *removed_value) {
    LNode *previous;
    LNode *removed;
    size_t j;
    if (list == NULL || !list->with_header || list->head == NULL || i < 1 || removed_value == NULL) return 0;
    previous = list->head;
    for (j = 1; j < i && previous != NULL; ++j) previous = previous->next;
    if (previous == NULL || previous->next == NULL) return 0;
    removed = previous->next;
    *removed_value = removed->data;
    previous->next = removed->next;
    free(removed);
    return 1;
}

// 功能：按输入顺序反向建立带头结点单链表。
// 来源：《2027数据结构》第2章 2.3.2；PDF第47页；书页第35页。
int List_HeadInsert(SinglyLinkedList *list, const int *input, size_t input_length, int terminator) {
    size_t i;
    if (list == NULL || (input == NULL && input_length != 0) || !SinglyLinkedListInit(list, true)) return 0;
    for (i = 0; i < input_length && input[i] != terminator; ++i) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
            SinglyLinkedListDestroy(list);
            return 0;
        }
        node->data = input[i];
        node->next = list->head->next;
        list->head->next = node;
    }
    return 1;
}

// 功能：按输入顺序正向建立带头结点单链表。
// 来源：《2027数据结构》第2章 2.3.2；PDF第47页；书页第35页。
int List_TailInsert(SinglyLinkedList *list, const int *input, size_t input_length, int terminator) {
    size_t i;
    LNode *tail;
    if (list == NULL || (input == NULL && input_length != 0) || !SinglyLinkedListInit(list, true)) return 0;
    tail = list->head;
    for (i = 0; i < input_length && input[i] != terminator; ++i) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
            SinglyLinkedListDestroy(list);
            return 0;
        }
        node->data = input[i];
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return 1;
}

// 功能：初始化带头结点的非循环双链表。
// 来源：《2027数据结构》第2章 2.3.3；PDF第48-49页；书页第36-37页。
int DoublyLinkedListInit(DoublyLinkedList *list) {
    if (list == NULL) return 0;
    list->head = (DNode *)calloc(1, sizeof(DNode));
    return list->head != NULL;
}

// 功能：释放双链表数据结点和头结点。
void DoublyLinkedListDestroy(DoublyLinkedList *list) {
    DNode *current;
    if (list == NULL) return;
    current = list->head;
    while (current != NULL) {
        DNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// 功能：在双链表末尾追加结点并同时维护前驱和后继指针。
// 来源：《2027数据结构》第2章 2.3.3；PDF第48-49页；书页第36-37页。
DNode *DoublyLinkedListAppend(DoublyLinkedList *list, int value) {
    DNode *tail;
    DNode *node;
    if (list == NULL || list->head == NULL) return NULL;
    tail = list->head;
    while (tail->next != NULL) tail = tail->next;
    node = (DNode *)malloc(sizeof(DNode));
    if (node == NULL) return NULL;
    node->data = value;
    node->prior = tail;
    node->next = NULL;
    tail->next = node;
    return node;
}

// 功能：在给定结点之后插入新结点，按书中顺序连接 next 与 prior。
// 来源：《2027数据结构》第2章 2.3.3；PDF第48页；书页第36页。
DNode *DoublyLinkedListInsertAfter(DNode *position, int value) {
    DNode *successor;
    DNode *node;
    if (position == NULL) return NULL;
    successor = position->next;
    node = (DNode *)malloc(sizeof(DNode));
    if (node == NULL) return NULL;
    node->data = value;
    node->prior = position;
    node->next = successor;
    position->next = node;
    if (successor != NULL) successor->prior = node;
    return node;
}

// 功能：删除给定结点之后的结点并返回其值。
// 来源：《2027数据结构》第2章 2.3.3；PDF第49页；书页第37页。
int DoublyLinkedListEraseAfter(DNode *position, int *removed_value) {
    DNode *removed;
    if (position == NULL || position->next == NULL || removed_value == NULL) return 0;
    removed = position->next;
    position->next = removed->next;
    if (removed->next != NULL) removed->next->prior = position;
    *removed_value = removed->data;
    free(removed);
    return 1;
}
