#include "search_algorithms.h"

#include <stdint.h>
#include <stdlib.h>

/* 功能：递归插入结点并向上更新子树结点数（正文 BST_Insert 的 C 辅助过程，PDF 第292页，书页第280页）。 */
static Ch07Status ch07_insert_node(Ch07BSTNode **root, int key, int *inserted) {
    if (*root == NULL) {
        Ch07BSTNode *node = (Ch07BSTNode *)malloc(sizeof(*node));
        if (node == NULL) {
            return CH07_STATUS_NO_MEMORY;
        }
        node->data = key;
        node->count = 1;
        node->lchild = NULL;
        node->rchild = NULL;
        *root = node;
        *inserted = 1;
        return CH07_STATUS_OK;
    }
    if (key == (*root)->data) {
        *inserted = 0;
        return CH07_STATUS_OK;
    }
    Ch07BSTNode **child = key < (*root)->data
                              ? &(*root)->lchild
                              : &(*root)->rchild;
    Ch07Status status = ch07_insert_node(child, key, inserted);
    if (status == CH07_STATUS_OK && *inserted) {
        if ((*root)->count == SIZE_MAX) {
            return CH07_STATUS_OVERFLOW;
        }
        ++(*root)->count;
    }
    return status;
}

/* 功能：递归释放二叉排序树节点及其左右子树（C 内存所有权辅助过程）。 */
static void ch07_destroy_nodes(Ch07BSTNode *root) {
    if (root == NULL) {
        return;
    }
    ch07_destroy_nodes(root->lchild);
    ch07_destroy_nodes(root->rchild);
    free(root);
}

/* 功能：将二叉排序树初始化为空，建立动态节点管理的起始状态。 */
void ch07_bst_init(Ch07BinarySearchTree *tree) {
    if (tree != NULL) {
        tree->root = NULL;
        tree->size = 0;
    }
}

/* 功能：设置哨兵后自表尾向前查找，命中返回一基下标，未命中返回0（正文 Search_Seq，PDF 第277页，书页第265页）。 */
Ch07Status ch07_search_seq(Ch07SearchTable *table, int key, size_t *index) {
    if (table == NULL || table->elem == NULL || index == NULL ||
        table->capacity == 0 || table->length >= table->capacity) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    table->elem[0] = key;
    size_t current = table->length;
    while (table->elem[current] != key) {
        --current;
    }
    *index = current;
    return CH07_STATUS_OK;
}

/* 功能：在升序数组中迭代执行折半查找，未命中写入 SIZE_MAX（正文 Binary_Search，PDF 第279页，书页第267页）。 */
Ch07Status ch07_binary_search(const int *sorted, size_t length, int key,
                              size_t *index) {
    if ((length > 0 && sorted == NULL) || index == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    size_t low = 0;
    size_t high = length;
    while (low < high) {
        const size_t middle = low + (high - low) / 2;
        if (sorted[middle] == key) {
            *index = middle;
            return CH07_STATUS_OK;
        }
        if (sorted[middle] > key) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }
    *index = SIZE_MAX;
    return CH07_STATUS_OK;
}

/* 功能：沿二叉排序树的左、右子树方向迭代查找给定关键字（正文 BST_Search，PDF 第291页，书页第279页）。 */
const Ch07BSTNode *ch07_bst_search(const Ch07BSTNode *root, int key) {
    const Ch07BSTNode *current = root;
    while (current != NULL && key != current->data) {
        current = key < current->data ? current->lchild : current->rchild;
    }
    return current;
}

/* 功能：递归插入关键字，重复关键字不插入（正文 BST_Insert，PDF 第292页，书页第280页）。 */
Ch07Status ch07_bst_insert(Ch07BinarySearchTree *tree, int key, int *inserted) {
    if (tree == NULL || inserted == NULL) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    Ch07Status status = ch07_insert_node(&tree->root, key, inserted);
    if (status == CH07_STATUS_OK && *inserted) {
        if (tree->size == SIZE_MAX) {
            return CH07_STATUS_OVERFLOW;
        }
        ++tree->size;
    }
    return status;
}

/* 功能：从空树开始按输入顺序逐个插入关键字（正文 Create_BST，PDF 第292页，书页第280页）。 */
Ch07Status ch07_create_bst(Ch07BinarySearchTree *tree, const int *keys,
                           size_t length) {
    if (tree == NULL || (length > 0 && keys == NULL)) {
        return CH07_STATUS_INVALID_ARGUMENT;
    }
    Ch07BinarySearchTree replacement = {NULL, 0};
    for (size_t i = 0; i < length; ++i) {
        int inserted = 0;
        const Ch07Status status = ch07_bst_insert(&replacement, keys[i], &inserted);
        if (status != CH07_STATUS_OK) {
            ch07_destroy_nodes(replacement.root);
            return status;
        }
    }
    ch07_destroy_nodes(tree->root);
    *tree = replacement;
    return CH07_STATUS_OK;
}

/* 功能：释放整棵二叉排序树并恢复空树状态（C 动态内存所有权接口）。 */
void ch07_bst_destroy(Ch07BinarySearchTree *tree) {
    if (tree != NULL) {
        ch07_destroy_nodes(tree->root);
        tree->root = NULL;
        tree->size = 0;
    }
}
