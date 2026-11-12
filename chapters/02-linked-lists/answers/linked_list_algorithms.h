#ifndef CHAPTER02_LINKED_LIST_ALGORITHMS_H
#define CHAPTER02_LINKED_LIST_ALGORITHMS_H

#include "linked_lists.h"
#include "q17_node.h"
#include "q18_node.h"
#include "q19_node.h"

#include <stddef.h>

// 功能：通过前驱结点删除单链表中所有值为 x 的结点。
// 来源：《2027数据结构》第2章习题答案 Del_X_1；PDF第62页；书页第50页。
void delete_all_value_by_predecessor(SinglyLinkedList *list, int value);

// 功能：遍历并重建链表，只保留值不等于 x 的结点。
// 来源：《2027数据结构》第2章习题答案 Del_X_2；PDF第62页；书页第50页。
void delete_all_value_by_tail_builder(SinglyLinkedList *list, int value);

// 功能：找到最小值结点，删除它并返回是否成功。
// 来源：《2027数据结构》第2章习题答案 Delete_Min；PDF第63页；书页第51页。
int delete_minimum_node(SinglyLinkedList *list);

// 功能：使用头插法逆置单链表。
// 来源：《2027数据结构》第2章习题答案 Reverse_1；PDF第63页；书页第51页。
void reverse_by_head_insertion(SinglyLinkedList *list);

// 功能：通过逐结点改写 next 指针逆置单链表。
// 来源：《2027数据结构》第2章习题答案 Reverse_2；PDF第64页；书页第52页。
void reverse_by_pointer_reversal(SinglyLinkedList *list);

// 功能：删除满足 lower < data < upper 的结点，并返回删除数量。
// 来源：《2027数据结构》第2章习题答案 RangeDelete；PDF第64页；书页第52页。
size_t delete_open_value_range(SinglyLinkedList *list, int lower, int upper);

// 功能：将奇数位结点按原序组成第一表，将偶数位结点头插到第二表（因此逆序）。
// 两个输出须先清零，且彼此不同并且都不与输入链表别名；成功返回非零，失败返回零。
// 来源：《2027数据结构》第2章习题答案 DisCreat_2；PDF第65页；书页第53页。
int split_alternating_positions(const SinglyLinkedList *list,
                                SinglyLinkedList *odd_positions,
                                SinglyLinkedList *even_positions);

// 功能：在递增有序单链表中删除相邻重复值，保留一个副本。
// 来源：《2027数据结构》第2章习题答案 Del_Same；PDF第65页；书页第53页。
size_t erase_adjacent_duplicates(SinglyLinkedList *sorted_list);

// 功能：逐对比较两个递增有序单链表，求交集并保留匹配到的重复次数。
// 输出须先清零且不得与任一输入别名；左右输入可以是同一链表。成功返回非零，失败返回零。
// 来源：《2027数据结构》第2章习题答案 Get_Common；PDF第66页；书页第54页。
int common_values_sorted_lists(const SinglyLinkedList *left,
                               const SinglyLinkedList *right,
                               SinglyLinkedList *result);

// 功能：按原书名为 Union 的答案代码求两个有序链表交集，结果留在 left，right 被清空。
// 来源：《2027数据结构》第2章习题答案第09题（代码名 Union，题意为交集）；PDF第66-67页；书页第54-55页。
void intersection_by_source_union_algorithm(SinglyLinkedList *left, SinglyLinkedList *right);

// 功能：判断 pattern 是否为 text 中连续出现的子链表，空模式约定为匹配。
// 来源：《2027数据结构》第2章习题答案 Pattern；PDF第67页；书页第55页。
int contains_contiguous_list(const SinglyLinkedList *text, const SinglyLinkedList *pattern);

typedef struct CircularSinglyLinkedList {
    LNode *head;
    LNode *tail;
} CircularSinglyLinkedList;

// 功能：构造带头结点的循环单链表空环；首次初始化前须清零，重初始化前须先销毁。
// 来源：《2027数据结构》第2章习题答案 Link；PDF第68页；书页第56页。
int CircularSinglyLinkedListInit(CircularSinglyLinkedList *list);

// 功能：释放循环单链表中的全部数据结点和头结点。
void CircularSinglyLinkedListDestroy(CircularSinglyLinkedList *list);

// 功能：在循环单链表尾部追加一个数据结点。
int CircularSinglyLinkedListAppend(CircularSinglyLinkedList *list, int value);

// 功能：判断循环单链表中是否没有数据结点。
int CircularSinglyLinkedListEmpty(const CircularSinglyLinkedList *list);

// 功能：将第二个循环单链表拼接到第一个表尾，并让第二个表变为空表。
// 来源：《2027数据结构》第2章习题答案 Link；PDF第68页；书页第56页。
void Link(CircularSinglyLinkedList *first, CircularSinglyLinkedList *second);

typedef struct CircularDoublyLinkedList {
    DNode *head;
} CircularDoublyLinkedList;

// 功能：构造带头结点循环双链表，头结点的前驱和后继均指向自身；首次初始化前须清零，重初始化前须先销毁。
// 来源：《2027数据结构》第2章习题答案 Symmetry；PDF第68页；书页第56页。
int CircularDoublyLinkedListInit(CircularDoublyLinkedList *list);

// 功能：释放循环双链表中的数据结点和头结点。
void CircularDoublyLinkedListDestroy(CircularDoublyLinkedList *list);

// 功能：在循环双链表末尾追加结点并维护双向环链。
int CircularDoublyLinkedListAppend(CircularDoublyLinkedList *list, int value);

// 功能：从两端向中间比较结点数据，判断循环双链表是否对称。
// 来源：《2027数据结构》第2章习题答案 Symmetry；PDF第68页；书页第56页。
int Symmetry(const CircularDoublyLinkedList *list);

typedef struct FrequencyNode {
    int data;
    size_t frequency;
    struct FrequencyNode *prior;
    struct FrequencyNode *next;
} FrequencyNode;

typedef struct FrequencyList {
    FrequencyNode *head;
} FrequencyList;

// 功能：构造空的频次有序双链表；首次初始化前须清零，重初始化前须先销毁。
int FrequencyListInit(FrequencyList *list);

// 功能：释放频次双链表的全部结点。
void FrequencyListDestroy(FrequencyList *list);

// 功能：在频次表尾部插入一个值及其初始访问次数。
FrequencyNode *FrequencyListAppend(FrequencyList *list, int value, size_t frequency);

// 功能：按访问频次递减维护双链表，访问后返回被访问结点；频次达到 SIZE_MAX 后保持饱和。
// 来源：《2027数据结构》第2章习题答案 Locate；PDF第69页；书页第57页。
FrequencyNode *Locate(FrequencyList *list, int value);

// 功能：将带头结点单链表向右循环移动 k 个位置。
// 来源：《2027数据结构》第2章习题答案 Converse；PDF第69页；书页第57页。
void rotate_right_by_k(SinglyLinkedList *list, size_t k);

// 功能：求偶数长度链表中对称位置元素之和的最大值；奇数长度或空表返回零。
// 来源：《2027数据结构》第2章习题答案 PairSum；PDF第70页；书页第58页。
int maximum_symmetric_pair_sum(SinglyLinkedList *list, long long *maximum);

// 功能：使用快慢指针检测单链表是否有环，并返回环入口结点。
// 来源：《2027数据结构》第2章习题答案 FindLoopStart；PDF第70页；书页第58页。
const LNode *find_loop_start(const LNode *head);

// 功能：单次遍历带头结点 link 链表，返回倒数第 k 个数据结点值，k 从 1 开始。
// 来源：《2027数据结构》第2章习题答案 Search_k；PDF第71页；书页第59页。
int kth_from_end(Q17LinkList head, size_t k, int *value);

// 功能：统计带头结点单链表中头结点之后的数据结点数量。
// 来源：《2027数据结构》第2章习题答案 listlen；PDF第72页；书页第60页。
size_t singly_list_length(const Q18Node *head);

// 功能：对齐两个单链表尾部后，返回它们共享的第一个后缀结点。
// 来源：《2027数据结构》第2章习题答案 find；PDF第72页；书页第60页。
const Q18Node *find_common_suffix_start(const Q18Node *first_head,
                                        const Q18Node *second_head);

// 功能：删除绝对值重复结点，只保留首次出现的值，时间复杂度 O(n+M)。
// 来源：《2027数据结构》第2章习题答案第19题；PDF第73页；书页第61页。
size_t remove_duplicate_absolute_values(Q19Node *head, size_t absolute_value_bound);

// 功能：将链表重排为首、尾、次首、次尾的交替次序。
// 来源：《2027数据结构》第2章习题答案 change_list；PDF第73-74页；书页第61-62页。
void reorder_first_last(SinglyLinkedList *list);

#endif
