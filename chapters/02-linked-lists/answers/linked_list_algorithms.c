#include "linked_list_algorithms.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

static void set_first_node(SinglyLinkedList *list, LNode *first) {
    if (list->with_header) {
        if (list->head != NULL) list->head->next = first;
    } else {
        list->head = first;
    }
}

static void reverse_links(SinglyLinkedList *list) {
    LNode *previous = NULL;
    LNode *current = SinglyLinkedListFirst(list);
    while (current != NULL) {
        LNode *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    set_first_node(list, previous);
}

// 功能：通过前驱结点删除单链表中所有值为 x 的结点。
// 来源：《2027数据结构》第2章习题答案 Del_X_1；PDF第62页；书页第50页。
void delete_all_value_by_predecessor(SinglyLinkedList *list, int value) {
    LNode *previous;
    if (list == NULL || !list->with_header || list->head == NULL) return;
    previous = list->head;
    while (previous->next != NULL) {
        if (previous->next->data == value) {
            LNode *removed = previous->next;
            previous->next = removed->next;
            free(removed);
        } else {
            previous = previous->next;
        }
    }
}

// 功能：遍历并重建链表，只保留值不等于 x 的结点。
// 来源：《2027数据结构》第2章习题答案 Del_X_2；PDF第62页；书页第50页。
void delete_all_value_by_tail_builder(SinglyLinkedList *list, int value) {
    LNode *current;
    LNode *tail;
    if (list == NULL || !list->with_header || list->head == NULL) return;
    current = list->head->next;
    list->head->next = NULL;
    tail = list->head;
    while (current != NULL) {
        LNode *next = current->next;
        if (current->data == value) {
            free(current);
        } else {
            current->next = NULL;
            tail->next = current;
            tail = current;
        }
        current = next;
    }
}

// 功能：找到最小值结点，删除它并返回是否成功。
// 来源：《2027数据结构》第2章习题答案 Delete_Min；PDF第63页；书页第51页。
int delete_minimum_node(SinglyLinkedList *list) {
    LNode *predecessor;
    LNode *p;
    LNode *removed;
    if (list == NULL || !list->with_header || list->head == NULL || list->head->next == NULL) return 0;
    predecessor = list->head;
    for (p = predecessor->next; p->next != NULL; p = p->next) {
        if (p->next->data < predecessor->next->data) predecessor = p;
    }
    removed = predecessor->next;
    predecessor->next = removed->next;
    free(removed);
    return 1;
}

// 功能：使用头插法逆置单链表。
// 来源：《2027数据结构》第2章习题答案 Reverse_1；PDF第63页；书页第51页。
void reverse_by_head_insertion(SinglyLinkedList *list) {
    LNode dummy = {0, NULL};
    LNode *current;
    if (list == NULL) return;
    current = SinglyLinkedListFirst(list);
    while (current != NULL) {
        LNode *next = current->next;
        current->next = dummy.next;
        dummy.next = current;
        current = next;
    }
    set_first_node(list, dummy.next);
}

// 功能：通过逐结点改写 next 指针逆置单链表。
// 来源：《2027数据结构》第2章习题答案 Reverse_2；PDF第64页；书页第52页。
void reverse_by_pointer_reversal(SinglyLinkedList *list) {
    if (list != NULL) reverse_links(list);
}

// 功能：删除满足 lower < data < upper 的结点，并返回删除数量。
// 来源：《2027数据结构》第2章习题答案 RangeDelete；PDF第64页；书页第52页。
size_t delete_open_value_range(SinglyLinkedList *list, int lower, int upper) {
    size_t removed_count = 0;
    LNode *previous;
    if (list == NULL || !list->with_header || list->head == NULL || lower >= upper) return 0;
    previous = list->head;
    while (previous->next != NULL) {
        if (lower < previous->next->data && previous->next->data < upper) {
            LNode *removed = previous->next;
            previous->next = removed->next;
            free(removed);
            ++removed_count;
        } else {
            previous = previous->next;
        }
    }
    return removed_count;
}

// 功能：将奇数位结点按原序组成第一表，将偶数位结点头插到第二表（因此逆序）。
// 来源：《2027数据结构》第2章习题答案 DisCreat_2；PDF第65页；书页第53页。
int split_alternating_positions(const SinglyLinkedList *list,
                                SinglyLinkedList *odd_positions,
                                SinglyLinkedList *even_positions) {
    LNode *odd_tail;
    LNode *current;
    size_t position = 1;
    if (list == NULL || odd_positions == NULL || even_positions == NULL ||
        odd_positions == even_positions || odd_positions == list || even_positions == list) return 0;
    if (!SinglyLinkedListInit(odd_positions, true)) return 0;
    if (!SinglyLinkedListInit(even_positions, true)) {
        SinglyLinkedListDestroy(odd_positions);
        return 0;
    }
    odd_tail = odd_positions->head;
    current = SinglyLinkedListFirst(list);
    while (current != NULL) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        if (node == NULL) {
            SinglyLinkedListDestroy(odd_positions);
            SinglyLinkedListDestroy(even_positions);
            return 0;
        }
        node->data = current->data;
        if (position % 2 == 1) {
            node->next = NULL;
            odd_tail->next = node;
            odd_tail = node;
        } else {
            node->next = even_positions->head->next;
            even_positions->head->next = node;
        }
        ++position;
        current = current->next;
    }
    return 1;
}

// 功能：在递增有序单链表中删除相邻重复值，保留一个副本。
// 来源：《2027数据结构》第2章习题答案 Del_Same；PDF第65页；书页第53页。
size_t erase_adjacent_duplicates(SinglyLinkedList *sorted_list) {
    size_t removed_count = 0;
    LNode *current;
    if (sorted_list == NULL || !sorted_list->with_header || sorted_list->head == NULL) return 0;
    current = sorted_list->head->next;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            LNode *removed = current->next;
            current->next = removed->next;
            free(removed);
            ++removed_count;
        } else {
            current = current->next;
        }
    }
    return removed_count;
}

// 功能：逐对比较两个递增有序单链表，求交集并保留匹配到的重复次数。
// 来源：《2027数据结构》第2章习题答案 Get_Common；PDF第66页；书页第54页。
int common_values_sorted_lists(const SinglyLinkedList *left,
                               const SinglyLinkedList *right,
                               SinglyLinkedList *result) {
    LNode *tail;
    LNode *a;
    LNode *b;
    if (left == NULL || right == NULL || result == NULL || result == left || result == right ||
        !SinglyLinkedListInit(result, true)) return 0;
    tail = result->head;
    a = SinglyLinkedListFirst(left);
    b = SinglyLinkedListFirst(right);
    while (a != NULL && b != NULL) {
        if (a->data < b->data) a = a->next;
        else if (b->data < a->data) b = b->next;
        else {
            LNode *node = (LNode *)malloc(sizeof(LNode));
            if (node == NULL) {
                SinglyLinkedListDestroy(result);
                return 0;
            }
            node->data = a->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            a = a->next;
            b = b->next;
        }
    }
    return 1;
}

// 功能：按原书名为 Union 的答案代码求两个有序链表交集，结果留在 left，right 被清空。
// 来源：《2027数据结构》第2章习题答案第09题（代码名 Union，题意为交集）；PDF第66-67页；书页第54-55页。
void intersection_by_source_union_algorithm(SinglyLinkedList *left, SinglyLinkedList *right) {
    LNode *a;
    LNode *b;
    LNode *result_tail;
    if (left == NULL || right == NULL || left == right || !left->with_header ||
        !right->with_header || left->head == NULL || right->head == NULL) return;
    a = left->head->next;
    b = right->head->next;
    result_tail = left->head;
    while (a != NULL && b != NULL) {
        if (a->data == b->data) {
            LNode *next_a = a->next;
            LNode *next_b = b->next;
            result_tail->next = a;
            result_tail = a;
            a = next_a;
            free(b);
            b = next_b;
        } else if (a->data < b->data) {
            LNode *next_a = a->next;
            result_tail->next = next_a;
            free(a);
            a = next_a;
        } else {
            LNode *next_b = b->next;
            free(b);
            b = next_b;
        }
    }
    while (a != NULL) {
        LNode *next = a->next;
        free(a);
        a = next;
    }
    result_tail->next = NULL;
    while (b != NULL) {
        LNode *next = b->next;
        free(b);
        b = next;
    }
    right->head->next = NULL;
}

// 功能：判断 pattern 是否为 text 中连续出现的子链表，空模式约定为匹配。
// 来源：《2027数据结构》第2章习题答案 Pattern；PDF第67页；书页第55页。
int contains_contiguous_list(const SinglyLinkedList *text, const SinglyLinkedList *pattern) {
    LNode *pattern_first;
    LNode *start;
    if (text == NULL || pattern == NULL) return 0;
    pattern_first = SinglyLinkedListFirst(pattern);
    if (pattern_first == NULL) return 1;
    for (start = SinglyLinkedListFirst(text); start != NULL; start = start->next) {
        LNode *a = start;
        LNode *b = pattern_first;
        while (a != NULL && b != NULL && a->data == b->data) {
            a = a->next;
            b = b->next;
        }
        if (b == NULL) return 1;
    }
    return 0;
}

// 功能：构造带头结点的循环单链表空环。
// 来源：《2027数据结构》第2章习题答案 Link；PDF第68页；书页第56页。
int CircularSinglyLinkedListInit(CircularSinglyLinkedList *list) {
    if (list == NULL) return 0;
    list->head = (LNode *)calloc(1, sizeof(LNode));
    if (list->head == NULL) {
        list->tail = NULL;
        return 0;
    }
    list->head->next = list->head;
    list->tail = list->head;
    return 1;
}

// 功能：释放循环单链表中的全部数据结点和头结点。
void CircularSinglyLinkedListDestroy(CircularSinglyLinkedList *list) {
    LNode *current;
    if (list == NULL || list->head == NULL) return;
    current = list->head->next;
    while (current != list->head) {
        LNode *next = current->next;
        free(current);
        current = next;
    }
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
}

// 功能：在循环单链表尾部追加一个数据结点。
int CircularSinglyLinkedListAppend(CircularSinglyLinkedList *list, int value) {
    LNode *node;
    if (list == NULL || list->head == NULL || list->tail == NULL) return 0;
    node = (LNode *)malloc(sizeof(LNode));
    if (node == NULL) return 0;
    node->data = value;
    node->next = list->head;
    list->tail->next = node;
    list->tail = node;
    return 1;
}

// 功能：判断循环单链表中是否没有数据结点。
int CircularSinglyLinkedListEmpty(const CircularSinglyLinkedList *list) {
    return list == NULL || list->head == NULL || list->head->next == list->head;
}

// 功能：将第二个循环单链表拼接到第一个表尾，并让第二个表变为空表。
// 来源：《2027数据结构》第2章习题答案 Link；PDF第68页；书页第56页。
void Link(CircularSinglyLinkedList *first, CircularSinglyLinkedList *second) {
    if (first == NULL || second == NULL || first == second || first->head == NULL || second->head == NULL ||
        CircularSinglyLinkedListEmpty(second)) return;
    first->tail->next = second->head->next;
    first->tail = second->tail;
    first->tail->next = first->head;
    second->head->next = second->head;
    second->tail = second->head;
}

// 功能：构造带头结点循环双链表，头结点的前驱和后继均指向自身。
// 来源：《2027数据结构》第2章习题答案 Symmetry；PDF第68页；书页第56页。
int CircularDoublyLinkedListInit(CircularDoublyLinkedList *list) {
    if (list == NULL) return 0;
    list->head = (DNode *)calloc(1, sizeof(DNode));
    if (list->head == NULL) return 0;
    list->head->next = list->head;
    list->head->prior = list->head;
    return 1;
}

// 功能：释放循环双链表中的数据结点和头结点。
void CircularDoublyLinkedListDestroy(CircularDoublyLinkedList *list) {
    DNode *current;
    if (list == NULL || list->head == NULL) return;
    current = list->head->next;
    while (current != list->head) {
        DNode *next = current->next;
        free(current);
        current = next;
    }
    free(list->head);
    list->head = NULL;
}

// 功能：在循环双链表末尾追加结点并维护双向环链。
int CircularDoublyLinkedListAppend(CircularDoublyLinkedList *list, int value) {
    DNode *node;
    DNode *tail;
    if (list == NULL || list->head == NULL) return 0;
    tail = list->head->prior;
    node = (DNode *)malloc(sizeof(DNode));
    if (node == NULL) return 0;
    node->data = value;
    node->prior = tail;
    node->next = list->head;
    tail->next = node;
    list->head->prior = node;
    return 1;
}

// 功能：从两端向中间比较结点数据，判断循环双链表是否对称。
// 来源：《2027数据结构》第2章习题答案 Symmetry；PDF第68页；书页第56页。
int Symmetry(const CircularDoublyLinkedList *list) {
    DNode *left;
    DNode *right;
    if (list == NULL || list->head == NULL) return 1;
    left = list->head->next;
    right = list->head->prior;
    while (left != right && left->prior != right) {
        if (left->data != right->data) return 0;
        left = left->next;
        right = right->prior;
    }
    return 1;
}

// 功能：构造空的频次有序双链表。
int FrequencyListInit(FrequencyList *list) {
    if (list == NULL) return 0;
    list->head = (FrequencyNode *)calloc(1, sizeof(FrequencyNode));
    return list->head != NULL;
}

// 功能：释放频次双链表的全部结点。
void FrequencyListDestroy(FrequencyList *list) {
    FrequencyNode *current;
    if (list == NULL) return;
    current = list->head;
    while (current != NULL) {
        FrequencyNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// 功能：在频次表尾部插入一个值及其初始访问次数。
FrequencyNode *FrequencyListAppend(FrequencyList *list, int value, size_t frequency) {
    FrequencyNode *tail;
    FrequencyNode *node;
    if (list == NULL || list->head == NULL) return NULL;
    tail = list->head;
    while (tail->next != NULL) tail = tail->next;
    node = (FrequencyNode *)malloc(sizeof(FrequencyNode));
    if (node == NULL) return NULL;
    node->data = value;
    node->frequency = frequency;
    node->prior = tail;
    node->next = NULL;
    tail->next = node;
    return node;
}

// 功能：访问值为 x 的结点，使访问频次加一并向前移动到非递增频次位置。
// 来源：《2027数据结构》第2章习题答案 Locate；PDF第69页；书页第57页。
FrequencyNode *Locate(FrequencyList *list, int value) {
    FrequencyNode *current;
    FrequencyNode *previous;
    if (list == NULL || list->head == NULL) return NULL;
    current = list->head->next;
    while (current != NULL && current->data != value) current = current->next;
    if (current == NULL) return NULL;
    if (current->frequency == SIZE_MAX) return current;
    ++current->frequency;
    previous = current->prior;
    while (previous != list->head && previous->frequency <= current->frequency) previous = previous->prior;
    if (previous != current->prior) {
        current->prior->next = current->next;
        if (current->next != NULL) current->next->prior = current->prior;
        current->next = previous->next;
        current->prior = previous;
        previous->next->prior = current;
        previous->next = current;
    }
    return current;
}

// 功能：将带头结点单链表向右循环移动 k 个位置。
// 来源：《2027数据结构》第2章习题答案 Converse；PDF第69页；书页第57页。
void rotate_right_by_k(SinglyLinkedList *list, size_t k) {
    LNode *first;
    LNode *tail;
    LNode *new_tail;
    size_t length = 1, shift, i;
    if (list == NULL) return;
    first = SinglyLinkedListFirst(list);
    if (first == NULL || first->next == NULL) return;
    tail = first;
    while (tail->next != NULL) {
        tail = tail->next;
        ++length;
    }
    shift = k % length;
    if (shift == 0) return;
    tail->next = first;
    new_tail = first;
    for (i = 1; i < length - shift; ++i) new_tail = new_tail->next;
    first = new_tail->next;
    new_tail->next = NULL;
    set_first_node(list, first);
}

// 功能：求偶数长度链表中对称位置元素之和的最大值；奇数长度输入无定义结果。
// 来源：《2027数据结构》第2章习题答案 PairSum；PDF第70页；书页第58页。
int maximum_symmetric_pair_sum(SinglyLinkedList *list, long long *maximum) {
    size_t length, half, i;
    LNode dummy;
    LNode *midpoint;
    LNode *second_half;
    LNode *previous = NULL;
    LNode *left;
    LNode *right;
    long long best;
    if (list == NULL || maximum == NULL) return 0;
    length = SinglyLinkedListLength(list);
    if (length == 0 || length % 2 != 0) return 0;
    half = length / 2;
    dummy.data = 0;
    dummy.next = SinglyLinkedListFirst(list);
    midpoint = &dummy;
    for (i = 0; i < half; ++i) midpoint = midpoint->next;
    second_half = midpoint->next;
    midpoint->next = NULL;
    while (second_half != NULL) {
        LNode *next = second_half->next;
        second_half->next = previous;
        previous = second_half;
        second_half = next;
    }
    left = dummy.next;
    right = previous;
    best = (long long)left->data + right->data;
    for (i = 0; i < half; ++i) {
        long long sum = (long long)left->data + right->data;
        if (sum > best) best = sum;
        left = left->next;
        right = right->next;
    }
    second_half = NULL;
    while (previous != NULL) {
        LNode *next = previous->next;
        previous->next = second_half;
        second_half = previous;
        previous = next;
    }
    midpoint->next = second_half;
    set_first_node(list, dummy.next);
    *maximum = best;
    return 1;
}

// 功能：使用快慢指针检测单链表是否有环，并返回环入口结点。
// 来源：《2027数据结构》第2章习题答案 FindLoopStart；PDF第70页；书页第58页。
const LNode *find_loop_start(const LNode *head) {
    const LNode *slow = head;
    const LNode *fast = head;
    do {
        if (fast == NULL || fast->next == NULL) return NULL;
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    while (head != slow) {
        head = head->next;
        slow = slow->next;
    }
    return head;
}

// 功能：单次遍历带头结点 link 链表，返回倒数第 k 个数据结点值，k 从 1 开始。
// 来源：《2027数据结构》第2章习题答案 Search_k；PDF第71页；书页第59页。
int kth_from_end(Q17LinkList head, size_t k, int *value) {
    Q17Node *fast;
    Q17Node *slow;
    size_t i;
    if (head == NULL || k == 0 || value == NULL) return 0;
    fast = head->link;
    slow = head->link;
    for (i = 0; i < k; ++i) {
        if (fast == NULL) return 0;
        fast = fast->link;
    }
    while (fast != NULL) {
        fast = fast->link;
        slow = slow->link;
    }
    if (slow == NULL) return 0;
    *value = slow->data;
    return 1;
}

// 功能：统计带头结点单链表中头结点之后的数据结点数量。
// 来源：《2027数据结构》第2章习题答案 listlen；PDF第72页；书页第60页。
size_t singly_list_length(const Q18Node *head) {
    size_t length = 0;
    const Q18Node *current;
    if (head == NULL) return 0;
    for (current = head->next; current != NULL; current = current->next) ++length;
    return length;
}

// 功能：对齐两个单链表尾部后，返回它们共享的第一个后缀结点。
// 来源：《2027数据结构》第2章习题答案 find；PDF第72页；书页第60页。
const Q18Node *find_common_suffix_start(const Q18Node *first_head, const Q18Node *second_head) {
    size_t first_length, second_length;
    const Q18Node *first;
    const Q18Node *second;
    if (first_head == NULL || second_head == NULL) return NULL;
    first_length = singly_list_length(first_head);
    second_length = singly_list_length(second_head);
    first = first_head;
    second = second_head;
    while (first_length > second_length) {
        first = first->next;
        --first_length;
    }
    while (second_length > first_length) {
        second = second->next;
        --second_length;
    }
    while (first->next != NULL && second->next != NULL && first->next != second->next) {
        first = first->next;
        second = second->next;
    }
    return first->next == second->next ? first->next : NULL;
}

// 功能：删除绝对值重复结点，只保留首次出现的值，时间复杂度 O(n+M)。
// 来源：《2027数据结构》第2章习题答案第19题；PDF第73页；书页第61页。
size_t remove_duplicate_absolute_values(Q19Node *head, size_t absolute_value_bound) {
    unsigned char *seen;
    size_t removed_count = 0;
    Q19Node *previous;
    if (head == NULL || absolute_value_bound == SIZE_MAX) return 0;
    seen = (unsigned char *)calloc(absolute_value_bound + 1, sizeof(unsigned char));
    if (seen == NULL) return 0;
    previous = head;
    while (previous->link != NULL) {
        long long value = previous->link->data;
        size_t magnitude = (size_t)(value < 0 ? -value : value);
        if (magnitude > absolute_value_bound) {
            previous = previous->link;
        } else if (seen[magnitude]) {
            Q19Node *removed = previous->link;
            previous->link = removed->link;
            free(removed);
            ++removed_count;
        } else {
            seen[magnitude] = 1;
            previous = previous->link;
        }
    }
    free(seen);
    return removed_count;
}

// 功能：将链表重排为首、尾、次首、次尾的交替次序。
// 来源：《2027数据结构》第2章习题答案 change_list；PDF第73-74页；书页第61-62页。
void reorder_first_last(SinglyLinkedList *list) {
    size_t length, i;
    LNode *midpoint;
    LNode *second;
    LNode *previous = NULL;
    LNode *first;
    if (list == NULL || !list->with_header || list->head == NULL || list->head->next == NULL ||
        list->head->next->next == NULL) return;
    length = SinglyLinkedListLength(list);
    midpoint = list->head;
    for (i = 0; i < (length + 1) / 2; ++i) midpoint = midpoint->next;
    second = midpoint->next;
    midpoint->next = NULL;
    while (second != NULL) {
        LNode *next = second->next;
        second->next = previous;
        previous = second;
        second = next;
    }
    first = list->head->next;
    second = previous;
    while (second != NULL) {
        LNode *next_first = first->next;
        LNode *next_second = second->next;
        first->next = second;
        second->next = next_first;
        first = next_first;
        second = next_second;
    }
}
