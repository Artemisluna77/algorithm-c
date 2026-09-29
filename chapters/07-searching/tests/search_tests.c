#include "search_algorithms.h"
#include "search_question_snippets.h"
#include "search_answers.h"
#include "test_harness.h"

#include <stdint.h>

/* 功能：验证带哨兵顺序查找命中位置、未命中和表尾边界。 */
DS_TEST_FUNCTION(sequential_search) {
    int elements[] = {0, 10, 20, 30, 40};
    Ch07SearchTable table = {elements, 4, 5};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_search_seq(&table, 10, &index) == CH07_STATUS_OK && index == 1);
    DS_CHECK(ch07_search_seq(&table, 30, &index) == CH07_STATUS_OK && index == 3);
    DS_CHECK(ch07_search_seq(&table, 40, &index) == CH07_STATUS_OK && index == 4);
    DS_CHECK(ch07_search_seq(&table, 99, &index) == CH07_STATUS_OK && index == 0);
}

/* 功能：验证空顺序表返回未命中，并拒绝缺少哨兵槽的缓冲区。 */
DS_TEST_FUNCTION(sequential_boundaries) {
    int sentinel_only[] = {0};
    Ch07SearchTable empty = {sentinel_only, 0, 1};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_search_seq(&empty, 1, &index) == CH07_STATUS_OK && index == 0);
    Ch07SearchTable invalid = {sentinel_only, 1, 1};
    DS_CHECK(ch07_search_seq(&invalid, 1, &index) == CH07_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证迭代折半查找命中、未命中和空数组。 */
DS_TEST_FUNCTION(binary_search) {
    const int sorted[] = {3, 7, 11, 18, 24, 31};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_binary_search(sorted, 6, 3, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(ch07_binary_search(sorted, 6, 31, &index) == CH07_STATUS_OK && index == 5);
    DS_CHECK(ch07_binary_search(sorted, 6, 18, &index) == CH07_STATUS_OK && index == 3);
    DS_CHECK(ch07_binary_search(sorted, 6, 17, &index) == CH07_STATUS_OK && index == SIZE_MAX);
    DS_CHECK(ch07_binary_search(NULL, 0, 1, &index) == CH07_STATUS_OK && index == SIZE_MAX);
}

/* 功能：验证固定步长查找回看选中区间并拒绝零步长。 */
DS_TEST_FUNCTION(stride_search) {
    const int sorted[] = {2, 5, 9, 12, 17, 20, 26};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_stride_search(sorted, 7, 2, 3, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(ch07_stride_search(sorted, 7, 9, 3, &index) == CH07_STATUS_OK && index == 2);
    DS_CHECK(ch07_stride_search(sorted, 7, 17, 3, &index) == CH07_STATUS_OK && index == 4);
    DS_CHECK(ch07_stride_search(sorted, 7, 26, 3, &index) == CH07_STATUS_OK && index == 6);
    DS_CHECK(ch07_stride_search(sorted, 7, 1, 3, &index) == CH07_STATUS_OK && index == SIZE_MAX);
    DS_CHECK(ch07_stride_search(sorted, 7, 21, 3, &index) == CH07_STATUS_OK && index == SIZE_MAX);
    DS_CHECK(ch07_stride_search(sorted, 7, 26, SIZE_MAX, &index) == CH07_STATUS_OK && index == 6);
    DS_CHECK(ch07_stride_search(NULL, 0, 1, 3, &index) == CH07_STATUS_OK && index == SIZE_MAX);
    DS_CHECK(ch07_stride_search(sorted, 7, 1, 0, &index) == CH07_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证递归折半查找的一基闭区间、子区间和空表。 */
DS_TEST_FUNCTION(recursive_binary_search) {
    int elements[] = {0, 4, 9, 13, 22, 28, 35};
    Ch07SearchTable table = {elements, 6, 7};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_bin_search_rec(&table, 4, 1, 6, &index) == CH07_STATUS_OK && index == 1);
    DS_CHECK(ch07_bin_search_rec(&table, 35, 1, 6, &index) == CH07_STATUS_OK && index == 6);
    DS_CHECK(ch07_bin_search_rec(&table, 20, 1, 6, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(ch07_bin_search_rec(&table, 22, 3, 5, &index) == CH07_STATUS_OK && index == 4);
    DS_CHECK(ch07_bin_search_rec(&table, 22, 8, 7, &index) == CH07_STATUS_INVALID_ARGUMENT);
    int empty_elem[] = {0};
    Ch07SearchTable empty = {empty_elem, 0, 1};
    DS_CHECK(ch07_bin_search_rec(&empty, 1, 1, 0, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(ch07_bin_search_rec(&empty, 1, 0, 0, &index) == CH07_STATUS_INVALID_ARGUMENT);
    DS_CHECK(ch07_bin_search_rec(&table, 4, 0, 2, &index) == CH07_STATUS_INVALID_ARGUMENT);
}

/* 功能：验证自组织查找将命中记录与前项交换且未命中不修改记录。 */
DS_TEST_FUNCTION(self_organizing_search) {
    Ch07Record records[] = {{10}, {20}, {30}, {40}};
    size_t index = SIZE_MAX;
    DS_CHECK(ch07_seq_srch(records, 4, 30, &index) == CH07_STATUS_OK && index == 1);
    DS_CHECK(records[1].key == 30 && records[2].key == 20);
    DS_CHECK(ch07_seq_srch(records, 4, 30, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(records[0].key == 30);
    DS_CHECK(ch07_seq_srch(records, 4, 10, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(ch07_seq_srch(records, 4, 99, &index) == CH07_STATUS_OK && index == SIZE_MAX);
    DS_CHECK(ch07_seq_srch(NULL, 0, 1, &index) == CH07_STATUS_OK && index == SIZE_MAX);
}

/* 功能：验证右上角矩阵查找命中、未命中和空矩阵。 */
DS_TEST_FUNCTION(sorted_matrix_search) {
    const int matrix[] = {
        1, 4, 7, 11,
        2, 5, 8, 12,
        3, 6, 9, 16,
        10, 13, 14, 17
    };
    int found = 0;
    DS_CHECK(ch07_find_key(matrix, 4, 1, &found) == CH07_STATUS_OK && found);
    DS_CHECK(ch07_find_key(matrix, 4, 14, &found) == CH07_STATUS_OK && found);
    DS_CHECK(ch07_find_key(matrix, 4, 15, &found) == CH07_STATUS_OK && !found);
    DS_CHECK(ch07_find_key(NULL, 0, 1, &found) == CH07_STATUS_OK && !found);
}

/* 功能：验证二叉排序树搜索能找到根/叶节点并报告缺失与空树。 */
DS_TEST_FUNCTION(bst_search) {
    Ch07BinarySearchTree tree;
    ch07_bst_init(&tree);
    const int keys[] = {8, 3, 10, 1, 6};
    DS_CHECK(ch07_create_bst(&tree, keys, 5) == CH07_STATUS_OK);
    const Ch07BSTNode *found = ch07_bst_search(tree.root, 8);
    DS_CHECK(found != NULL && found->data == 8);
    found = ch07_bst_search(tree.root, 6);
    DS_CHECK(found != NULL && found->data == 6);
    DS_CHECK(ch07_bst_search(tree.root, 99) == NULL);
    DS_CHECK(ch07_bst_search(NULL, 8) == NULL);
    ch07_bst_destroy(&tree);
    DS_CHECK(tree.root == NULL && tree.size == 0);
}

/* 功能：验证 BST 插入忽略重复键、更新子树大小并支持批量重建和清空。 */
DS_TEST_FUNCTION(bst_insert_build) {
    Ch07BinarySearchTree tree = {NULL, 0};
    int inserted = 0;
    DS_CHECK(ch07_bst_insert(&tree, 5, &inserted) == CH07_STATUS_OK && inserted);
    DS_CHECK(ch07_bst_insert(&tree, 5, &inserted) == CH07_STATUS_OK && !inserted);
    DS_CHECK(tree.size == 1 && tree.root->count == 1);
    const int keys[] = {3, 7, 2, 4};
    DS_CHECK(ch07_create_bst(&tree, keys, 4) == CH07_STATUS_OK);
    DS_CHECK(tree.size == 4 && tree.root->count == 4);
    DS_CHECK(ch07_bst_search(tree.root, 5) == NULL);
    DS_CHECK(ch07_create_bst(&tree, NULL, 0) == CH07_STATUS_OK);
    DS_CHECK(tree.size == 0 && tree.root == NULL);
    ch07_bst_destroy(&tree);
}

/* 功能：验证中序严格递增检查接受合法/空树并拒绝顺序错误和重复键。 */
DS_TEST_FUNCTION(judge_bst) {
    Ch07BinarySearchTree tree = {NULL, 0};
    const int keys[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    DS_CHECK(ch07_create_bst(&tree, keys, 9) == CH07_STATUS_OK);
    DS_CHECK(ch07_judge_bst(tree.root));
    DS_CHECK(ch07_judge_bst(NULL));
    Ch07BSTNode invalid_child = {12, 1, NULL, NULL};
    Ch07BSTNode invalid = {8, 2, &invalid_child, NULL};
    DS_CHECK(!ch07_judge_bst(&invalid));
    Ch07BSTNode duplicate_child = {5, 1, NULL, NULL};
    Ch07BSTNode duplicate = {5, 2, NULL, &duplicate_child};
    DS_CHECK(!ch07_judge_bst(&duplicate));
    ch07_bst_destroy(&tree);
}

/* 功能：验证查找层数按一开始计数并对未命中返回零层。 */
DS_TEST_FUNCTION(search_level) {
    Ch07BinarySearchTree tree = {NULL, 0};
    const int keys[] = {6, 2, 8, 1, 4, 7, 9, 3};
    size_t depth = SIZE_MAX;
    DS_CHECK(ch07_create_bst(&tree, keys, 8) == CH07_STATUS_OK);
    DS_CHECK(ch07_level(tree.root, 6, &depth) == CH07_STATUS_OK && depth == 1);
    DS_CHECK(ch07_level(tree.root, 3, &depth) == CH07_STATUS_OK && depth == 4);
    DS_CHECK(ch07_level(tree.root, 99, &depth) == CH07_STATUS_OK && depth == 0);
    DS_CHECK(ch07_level(NULL, 1, &depth) == CH07_STATUS_OK && depth == 0);
    ch07_bst_destroy(&tree);
}

/* 功能：验证 AVL 判断返回空树、平衡树、叶节点和偏斜树的高度与平衡性。 */
DS_TEST_FUNCTION(judge_avl) {
    Ch07AvlJudgement result = ch07_judge_avl(NULL);
    DS_CHECK(result.balanced && result.height == 0);
    Ch07BinarySearchTree balanced = {NULL, 0};
    const int balanced_keys[] = {4, 2, 6, 1, 3, 5, 7};
    DS_CHECK(ch07_create_bst(&balanced, balanced_keys, 7) == CH07_STATUS_OK);
    result = ch07_judge_avl(balanced.root);
    DS_CHECK(result.balanced && result.height == 3);
    Ch07BinarySearchTree skewed = {NULL, 0};
    const int skewed_keys[] = {1, 2, 3, 4};
    DS_CHECK(ch07_create_bst(&skewed, skewed_keys, 4) == CH07_STATUS_OK);
    result = ch07_judge_avl(skewed.root);
    DS_CHECK(!result.balanced && result.height == 4);
    ch07_bst_destroy(&balanced);
    ch07_bst_destroy(&skewed);
}

/* 功能：验证最小/最大关键字沿树边界查找及空树状态。 */
DS_TEST_FUNCTION(minmax) {
    Ch07BinarySearchTree tree = {NULL, 0};
    const int keys[] = {6, 2, 8, 1, 4, 7, 9};
    int key = 0;
    DS_CHECK(ch07_create_bst(&tree, keys, 7) == CH07_STATUS_OK);
    DS_CHECK(ch07_min_key(tree.root, &key) == CH07_STATUS_OK && key == 1);
    DS_CHECK(ch07_max_key(tree.root, &key) == CH07_STATUS_OK && key == 9);
    DS_CHECK(ch07_min_key(NULL, &key) == CH07_STATUS_NOT_FOUND);
    DS_CHECK(ch07_max_key(NULL, &key) == CH07_STATUS_NOT_FOUND);
    ch07_bst_destroy(&tree);
}

/* 功能：验证阈值输出按降序返回目标关键字，并在缓冲区不足时不写入部分结果。 */
DS_TEST_FUNCTION(output_threshold) {
    Ch07BinarySearchTree tree = {NULL, 0};
    const int keys[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    const int expected[] = {14, 13, 10, 8, 7};
    int output[5] = {0};
    size_t length = 0;
    DS_CHECK(ch07_create_bst(&tree, keys, 9) == CH07_STATUS_OK);
    DS_CHECK(ch07_output_threshold(tree.root, 7, output, 5, &length) == CH07_STATUS_OK);
    DS_CHECK(length == 5);
    for (size_t i = 0; i < length; ++i) DS_CHECK(output[i] == expected[i]);
    DS_CHECK(ch07_output_threshold(tree.root, 7, output, 4, &length) == CH07_STATUS_BUFFER_TOO_SMALL);
    DS_CHECK(length == 5);
    DS_CHECK(ch07_output_threshold(tree.root, 15, NULL, 0, &length) == CH07_STATUS_OK && length == 0);
    DS_CHECK(ch07_output_threshold(NULL, 0, NULL, 0, &length) == CH07_STATUS_OK && length == 0);
    ch07_bst_destroy(&tree);
}

/* 功能：验证根据子树规模查找第 k 小元素并拒绝无效秩。 */
DS_TEST_FUNCTION(kth_smallest) {
    Ch07BinarySearchTree tree = {NULL, 0};
    const int keys[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    int key = 0;
    DS_CHECK(ch07_create_bst(&tree, keys, 9) == CH07_STATUS_OK);
    DS_CHECK(ch07_search_small(tree.root, 1, &key) == CH07_STATUS_OK && key == 1);
    DS_CHECK(ch07_search_small(tree.root, 5, &key) == CH07_STATUS_OK && key == 7);
    DS_CHECK(ch07_search_small(tree.root, 9, &key) == CH07_STATUS_OK && key == 14);
    DS_CHECK(ch07_search_small(tree.root, 0, &key) == CH07_STATUS_NOT_FOUND);
    DS_CHECK(ch07_search_small(tree.root, 10, &key) == CH07_STATUS_NOT_FOUND);
    DS_CHECK(ch07_search_small(NULL, 1, &key) == CH07_STATUS_NOT_FOUND);
    ch07_bst_destroy(&tree);
}

/* 功能：验证顺序表和树类型可在纯 C 中创建、传递并销毁。 */
DS_TEST_FUNCTION(source_types) {
    int sentinel[] = {0};
    Ch07SearchTable table = {sentinel, 0, 1};
    Ch07BinarySearchTree tree;
    ch07_bst_init(&tree);
    size_t index = SIZE_MAX;
    DS_CHECK(table.length == 0 && table.capacity == 1);
    DS_CHECK(ch07_search_seq(&table, 1, &index) == CH07_STATUS_OK && index == 0);
    DS_CHECK(tree.root == NULL && tree.size == 0);
    ch07_bst_destroy(&tree);
}

int main(int argc, char **argv) {
    static const DsTestCase cases[] = {
        DS_TEST_CASE(sequential_search),
        DS_TEST_CASE(sequential_boundaries),
        DS_TEST_CASE(binary_search),
        DS_TEST_CASE(stride_search),
        DS_TEST_CASE(recursive_binary_search),
        DS_TEST_CASE(self_organizing_search),
        DS_TEST_CASE(sorted_matrix_search),
        DS_TEST_CASE(bst_search),
        DS_TEST_CASE(bst_insert_build),
        DS_TEST_CASE(judge_bst),
        DS_TEST_CASE(search_level),
        DS_TEST_CASE(judge_avl),
        DS_TEST_CASE(minmax),
        DS_TEST_CASE(output_threshold),
        DS_TEST_CASE(kth_smallest),
        DS_TEST_CASE(source_types)
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
