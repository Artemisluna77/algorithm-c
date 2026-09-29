#include "sequential_list.h"

#include <stdint.h>
#include <stdlib.h>

// 功能：将静态顺序表初始化为空表。
// 来源：《2027数据结构》第2章 2.2.2；PDF第28页；书页第16页。
void SeqListInit(SeqList *list) {
    if (list != NULL) list->length = 0;
}

// 功能：为动态顺序表分配初始数组并设置容量与表长。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28-29页；书页第16-17页。
int InitDynamicList(DynamicSeqList *list, size_t initial_size) {
    int *new_data = NULL;
    if (list == NULL || initial_size > SIZE_MAX / sizeof(int)) return 0;
    if (initial_size != 0) {
        new_data = (int *)malloc(initial_size * sizeof(int));
        if (new_data == NULL) return 0;
    }
    free(list->data);
    list->data = new_data;
    list->MaxSize = initial_size;
    list->length = 0;
    return 1;
}

// 功能：释放动态顺序表数组并清空其状态。
void DynamicSeqListDestroy(DynamicSeqList *list) {
    if (list == NULL) return;
    free(list->data);
    list->data = NULL;
    list->MaxSize = 0;
    list->length = 0;
}

// 功能：把书中的 C malloc 示例转换为 C17 动态数组分配。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28页；书页第16页。
int InitDynamicListFromMallocExample(DynamicSeqList *list, size_t initial_size) {
    return InitDynamicList(list, initial_size);
}

// 功能：把书中的 C++ new[] 示例转换为 C17 malloc/free 管理。
// 来源：《2027数据结构》第2章 2.2.1；PDF第28页；书页第16页。
int InitDynamicListFromNewExample(DynamicSeqList *list, size_t initial_size) {
    return InitDynamicList(list, initial_size);
}

// 功能：在静态顺序表的第 i 个（一基）位置插入元素。
// 来源：《2027数据结构》第2章 2.2.2；PDF第29页；书页第17页。
int SeqListInsert(SeqList *list, size_t i, int element) {
    size_t j;
    if (list == NULL || i < 1 || i > list->length + 1 ||
        list->length >= SEQ_LIST_MAX_SIZE) return 0;
    for (j = list->length; j >= i; --j) list->data[j] = list->data[j - 1];
    list->data[i - 1] = element;
    ++list->length;
    return 1;
}

// 功能：删除静态顺序表第 i 个（一基）位置的元素并返回被删元素。
// 来源：《2027数据结构》第2章 2.2.2；PDF第29页；书页第17页。
int SeqListDelete(SeqList *list, size_t i, int *removed_element) {
    size_t j;
    if (list == NULL || removed_element == NULL || i < 1 || i > list->length) return 0;
    *removed_element = list->data[i - 1];
    for (j = i; j < list->length; ++j) list->data[j - 1] = list->data[j];
    --list->length;
    return 1;
}

// 功能：顺序查找首个等于目标值的元素，返回一基位置；未找到时返回 0。
// 来源：《2027数据结构》第2章 2.2.2；PDF第30页；书页第18页。
size_t SeqListLocate(const SeqList *list, int element) {
    size_t i;
    if (list == NULL) return 0;
    for (i = 0; i < list->length; ++i) {
        if (list->data[i] == element) return i + 1;
    }
    return 0;
}
