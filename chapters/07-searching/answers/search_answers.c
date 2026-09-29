#include "search_answers.h"

#include <stdint.h>
#include <stdlib.h>

/* 功能：递归在一基闭区间内折半查找并返回 0 表示未命中（答案 BinSearchRec，PDF 第289页，书页第277页）。 */
static size_t ch07_bin_search_range(const Ch07SearchTable *table, int key,
                                    size_t low, size_t high) {
    if (low > high) {
        return 0;
    }
    const size_t middle = low + (high - low) / 2;
    if (table->elem[middle] == key) {
        return middle;
    }
    if (table->elem[middle] > key) {
        return ch07_bin_search_range(table, key, low, middle - 1);
    }
    return ch07_bin_search_range(table, key, middle + 1, high);
}

/* 功能：递归中序遍历并检查关键字严格递增（答案 JudgeBST 的辅助过程，PDF 第314页，书页第302页）。 */
static int ch07_judge_bst_visit(const Ch07BSTNode *root, int *has_previous,
                                int *previous) {
    if (root == NULL) {
        return 1;
    }
    if (!ch07_judge_bst_visit(root->lchild, has_previous, previous)) {
        return 0;
    }
    if (*has_previous && *previous >= root->data) {
        return 0;
    }
    *previous = root->data;
    *has_previous = 1;
    return ch07_judge_bst_visit(root->rchild, has_previous, previous);
}

/* 功能：递归计算符合阈值的结点数，为输出缓冲区预检容量（答案 OutPut 的 C 辅助过程，PDF 第316页，书页第304页）。 */
static size_t ch07_count_threshold(const Ch07BSTNode *root, int minimum_key) {
    if (root == NULL) {
        return 0;
    }
    if (root->data < minimum_key) {
        return ch07_count_threshold(root->rchild, minimum_key);
    }
    return 1 + ch07_count_threshold(root->lchild, minimum_key) +
           ch07_count_threshold(root->rchild, minimum_key);
}

/* 功能：按右根左次序将不小于阈值的结点写入调用方缓冲区（答案 OutPut 的 C 辅助过程，PDF 第316页，书页第304页）。 */
static void ch07_write_threshold(const Ch07BSTNode *root, int minimum_key,
                                 int *output, size_t *position) {
    if (root == NULL) {
        return;
    }
    ch07_write_threshold(root->rchild, minimum_key, output, position);
    if (root->data >= minimum_key) {
        output[(*position)++] = root->data;
        ch07_write_threshold(root->lchild, minimum_key, output, position);
    }
}

/* 功能：递归计算各结点 AVL 高度和平衡状态（答案 Judge_AVL 的辅助过程，PDF 第315页，书页第303页）。 */
static Ch07AvlJudgement ch07_judge_avl_visit(const Ch07BSTNode *root) {
    Ch07AvlJudgement result = {1, 0};
    if (root == NULL) {
        return result;
    }
    const Ch07AvlJudgement left = ch07_judge_avl_visit(root->lchild);
    const Ch07AvlJudgement right = ch07_judge_avl_visit(root->rchild);
    result.height = (left.height > right.height ? left.height : right.height) + 1;
    const size_t difference = left.height > right.height
                                  ? left.height - right.height
                                  : right.height - left.height;
    result.balanced = left.balanced && right.balanced && difference < 2;
    return result;
}

/* 功能：递归折半查找一基闭区间，命中返回一基位置，未命中返回0（答案 BinSearchRec，PDF 第289页，书页第277页）。 */
Ch07Status ch07_bin_search_rec(const Ch07SearchTable *table, int key,
                               size_t low, size_t high, size_t *index) {
    if (table == NULL || index == NULL || table->elem == NULL ||
        table->capacity == 0 || table->length >= table->capacity) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    if (low == 0 || low > table->length + 1 || high > table->length) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    if (low > high) {
        *index = 0;
        return CH07_STATUS_OK;
    }
    *index = ch07_bin_search_range(table, key, low, high);
    return CH07_STATUS_OK;
}

/* 功能：顺序查找后将命中记录与前一项交换，实现自组织查找转置策略（答案 SeqSrch，PDF 第289页，书页第277页）。 */
Ch07Status ch07_seq_srch(Ch07Record *records, size_t length, int key,
                          size_t *index) {
    if ((length > 0 && records == NULL) || index == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    size_t current = 0;
    while (current < length && records[current].key != key) {
        ++current;
    }
    if (current == length) {
        *index = SIZE_MAX;
        return CH07_STATUS_OK;
    }
    if (current > 0) {
        const Ch07Record temporary = records[current];
        records[current] = records[current - 1];
        records[current - 1] = temporary;
        --current;
    }
    *index = current;
    return CH07_STATUS_OK;
}

/* 功能：从有序方阵右上角出发逐行或逐列缩小范围（答案 findkey，PDF 第290页，书页第278页）。 */
Ch07Status ch07_find_key(const int *matrix, size_t size, int key, int *found) {
    if ((size > 0 && matrix == NULL) || found == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    if (size > 0 && size > SIZE_MAX / size) {
        return CH07_STATUS_OVERFLOW;
    }
    *found = 0;
    if (size == 0) {
        return CH07_STATUS_OK;
    }
    size_t row = 0;
    size_t column = size - 1;
    while (row < size) {
        const int current = matrix[row * size + column];
        if (current == key) {
            *found = 1;
            return CH07_STATUS_OK;
        }
        if (current > key) {
            if (column == 0) {
                return CH07_STATUS_OK;
            }
            --column;
        } else {
            ++row;
        }
    }
    return CH07_STATUS_OK;
}

/* 功能：以中序遍历检查关键字是否严格递增（答案 JudgeBST，PDF 第314页，书页第302页）。 */
int ch07_judge_bst(const Ch07BSTNode *root) {
    int has_previous = 0;
    int previous = 0;
    return ch07_judge_bst_visit(root, &has_previous, &previous);
}

/* 功能：沿二叉排序树搜索路径统计查找层数，未命中写 0（答案 level，PDF 第314–315页，书页第302–303页）。 */
Ch07Status ch07_level(const Ch07BSTNode *root, int key, size_t *depth) {
    if (depth == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    *depth = 0;
    size_t current_depth = 0;
    while (root != NULL) {
        ++current_depth;
        if (root->data == key) {
            *depth = current_depth;
            break;
        }
        root = key < root->data ? root->lchild : root->rchild;
    }
    return CH07_STATUS_OK;
}

/* 功能：递归计算左右子树高度并判断每个结点是否平衡（答案 Judge_AVL，PDF 第315页，书页第303页）。 */
Ch07AvlJudgement ch07_judge_avl(const Ch07BSTNode *root) {
    return ch07_judge_avl_visit(root);
}

/* 功能：沿左孩子链查找二叉排序树中的最小关键字（答案 MinKey，PDF 第315页，书页第303页）。 */
Ch07Status ch07_min_key(const Ch07BSTNode *root, int *key) {
    if (key == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    if (root == NULL) {
        return CH07_STATUS_NOT_FOUND;
    }
    while (root->lchild != NULL) {
        root = root->lchild;
    }
    *key = root->data;
    return CH07_STATUS_OK;
}

/* 功能：沿右孩子链查找二叉排序树中的最大关键字（答案 MaxKey，PDF 第315页，书页第303页）。 */
Ch07Status ch07_max_key(const Ch07BSTNode *root, int *key) {
    if (key == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    if (root == NULL) {
        return CH07_STATUS_NOT_FOUND;
    }
    while (root->rchild != NULL) {
        root = root->rchild;
    }
    *key = root->data;
    return CH07_STATUS_OK;
}

/* 功能：按右根左逆中序输出所有大于等于阈值的关键字（答案 OutPut，PDF 第316页，书页第304页）。 */
Ch07Status ch07_output_threshold(const Ch07BSTNode *root, int minimum_key,
                                 int *output, size_t capacity, size_t *length) {
    if (length == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    const size_t required = ch07_count_threshold(root, minimum_key);
    *length = required;
    if (required > capacity || (required > 0 && output == NULL)) {
        return CH07_STATUS_BUFFER_TOO_SMALL;
    }
    size_t position = 0;
    ch07_write_threshold(root, minimum_key, output, &position);
    return CH07_STATUS_OK;
}

/* 功能：利用左子树规模查找二叉排序树中第 k 小关键字（答案 Search_Small，PDF 第316页，书页第304页）。 */
Ch07Status ch07_search_small(const Ch07BSTNode *root, size_t k, int *key) {
    if (key == NULL || k == 0 || root == NULL || k > root->count) {
        return CH07_STATUS_NOT_FOUND;
    }
    while (root != NULL) {
        const size_t left_count = root->lchild == NULL ? 0 : root->lchild->count;
        if (k == left_count + 1) {
            *key = root->data;
            return CH07_STATUS_OK;
        }
        if (k <= left_count) {
            root = root->lchild;
        } else {
            k -= left_count + 1;
            root = root->rchild;
        }
    }
    return CH07_STATUS_NOT_FOUND;
}
