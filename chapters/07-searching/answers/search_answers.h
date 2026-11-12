#ifndef CH07_SEARCH_ANSWERS_H
#define CH07_SEARCH_ANSWERS_H

#include "../body/search_algorithms.h"

#include <stddef.h>

typedef struct Ch07Record {
    int key;
} Ch07Record;

typedef struct Ch07AvlJudgement {
    int balanced;
    size_t height;
} Ch07AvlJudgement;

/* 功能：递归折半查找一基闭区间，命中写一基位置，未命中写 0（答案 BinSearchRec，PDF 第289页，书页第277页）。 */
Ch07Status ch07_bin_search_rec(const Ch07SearchTable *table, int key,
                               size_t low, size_t high, size_t *index);
/* 功能：顺序查找后将命中记录与前一项交换，实现转置策略（答案 SeqSrch，PDF 第289页，书页第277页）。 */
Ch07Status ch07_seq_srch(Ch07Record *records, size_t length, int key,
                          size_t *index);
/* 功能：从行列递增的 n×n 方阵右上角开始缩小搜索范围（答案 findkey，PDF 第290页，书页第278页）。 */
Ch07Status ch07_find_key(const int *matrix, size_t size, int key, int *found);
/* 功能：以中序遍历检验树关键字是否严格递增（答案 JudgeBST，PDF 第314页，书页第302页）。 */
int ch07_judge_bst(const Ch07BSTNode *root);
/* 功能：沿二叉排序树搜索路径统计比较层数，未命中写 0（答案 level，PDF 第314–315页，书页第302–303页）。 */
Ch07Status ch07_level(const Ch07BSTNode *root, int key, size_t *depth);
/* 功能：递归求左右子树高度并判断平衡性（答案 Judge_AVL，PDF 第315页，书页第303页）。 */
Ch07AvlJudgement ch07_judge_avl(const Ch07BSTNode *root);
/* 功能：沿左孩子链查找最小关键字（答案 MinKey，PDF 第315页，书页第303页）。 */
Ch07Status ch07_min_key(const Ch07BSTNode *root, int *key);
/* 功能：沿右孩子链查找最大关键字（答案 MaxKey，PDF 第315页，书页第303页）。 */
Ch07Status ch07_max_key(const Ch07BSTNode *root, int *key);
/* 功能：按右根左次序输出所有大于等于阈值的关键字（答案 OutPut，PDF 第316页，书页第304页）。 */
Ch07Status ch07_output_threshold(const Ch07BSTNode *root, int minimum_key,
                                 int *output, size_t capacity, size_t *length);
/* 功能：利用左子树结点数查找第 k 小关键字，k 从 1 开始（答案 Search_Small，PDF 第316页，书页第304页）。 */
Ch07Status ch07_search_small(const Ch07BSTNode *root, size_t k, int *key);

#endif
