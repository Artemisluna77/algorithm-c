#ifndef CHAPTER02_SEQUENTIAL_LIST_H
#define CHAPTER02_SEQUENTIAL_LIST_H

#include <stddef.h>

#define SEQ_LIST_MAX_SIZE 50

typedef struct SeqList {
    int data[SEQ_LIST_MAX_SIZE];
    size_t length;
} SeqList;

typedef struct DynamicSeqList {
    int *data;
    size_t MaxSize;
    size_t length;
} DynamicSeqList;

// 功能：将静态顺序表初始化为空表。
// 来源：《2027数据结构》第2章 2.2.2；PDF第28页；书页第16页。
void SeqListInit(SeqList *list);

// 功能：初始化动态顺序表；list 首次使用前须清零，重新初始化时会释放旧数组。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28-29页；书页第16-17页。
int InitDynamicList(DynamicSeqList *list, size_t initial_size);

// 功能：释放动态顺序表数组并清空其状态。
void DynamicSeqListDestroy(DynamicSeqList *list);

// 功能：将书中 malloc 动态初始化示例转换为 C17 动态数组分配。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28页；书页第16页。
int InitDynamicListFromMallocExample(DynamicSeqList *list, size_t initial_size);

// 功能：将书中 new[] 动态初始化示例转换为 C17 malloc/free 管理。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28页；书页第16页。
int InitDynamicListFromNewExample(DynamicSeqList *list, size_t initial_size);

// 功能：在静态顺序表的第 i 个（一基）位置插入元素，容量不足或位置非法时失败。
// 来源：《2027数据结构》第2章 2.2.2；PDF第29页；书页第17页。
int SeqListInsert(SeqList *list, size_t i, int element);

// 功能：删除静态顺序表第 i 个（一基）位置的元素，并通过指针返回被删元素。
// 来源：《2027数据结构》第2章 2.2.2；PDF第29页；书页第17页。
int SeqListDelete(SeqList *list, size_t i, int *removed_element);

// 功能：顺序查找首个等于目标值的元素，返回一基位置；未找到返回 0。
// 来源：《2027数据结构》第2章 2.2.2；PDF第30页；书页第18页。
size_t SeqListLocate(const SeqList *list, int element);

#endif
