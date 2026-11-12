#ifndef CH07_SEARCH_ALGORITHMS_H
#define CH07_SEARCH_ALGORITHMS_H

#include <stddef.h>

typedef enum Ch07Status {
    CH07_STATUS_OK = 0,
    CH07_STATUS_INVALID_ARGUMENT = 1,
    CH07_STATUS_NO_MEMORY = 2,
    CH07_STATUS_OVERFLOW = 3,
    CH07_STATUS_BUFFER_TOO_SMALL = 4,
    CH07_STATUS_NOT_FOUND = 5
} Ch07Status;

/* 功能：描述 elem[0] 为哨兵、elem[1..length] 为数据的顺序查找表；capacity 是含哨兵的总槽数，须大于 length（正文 7.2.1，PDF 第277页，书页第265页）。 */
typedef struct Ch07SearchTable {
    int *elem;
    size_t length;
    size_t capacity;
} Ch07SearchTable;

/* 功能：描述缓存子树结点数的二叉排序树结点（查找算法测试上下文，正文算法来源见 PDF 第291–292页）。 */
typedef struct Ch07BSTNode {
    int data;
    size_t count;
    struct Ch07BSTNode *lchild;
    struct Ch07BSTNode *rchild;
} Ch07BSTNode;

/* 功能：保存二叉排序树根结点与树中结点总数；使用前先调用 ch07_bst_init（测试上下文，算法来源见 PDF 第291–292页）。 */
typedef struct Ch07BinarySearchTree {
    Ch07BSTNode *root;
    size_t size;
} Ch07BinarySearchTree;

/* 功能：设置哨兵后自表尾向前查找，命中返回一基下标，未命中写入 0（正文 Search_Seq，PDF 第277页，书页第265页）。 */
Ch07Status ch07_search_seq(Ch07SearchTable *table, int key, size_t *index);
/* 功能：在升序数组中迭代折半查找，未命中写入 SIZE_MAX（正文 Binary_Search，PDF 第279页，书页第267页）。 */
Ch07Status ch07_binary_search(const int *sorted, size_t length, int key,
                              size_t *index);
/* 功能：沿二叉排序树的左、右子树方向查找关键字（正文 BST_Search，PDF 第291页，书页第279页）。 */
const Ch07BSTNode *ch07_bst_search(const Ch07BSTNode *root, int key);
/* 功能：递归插入关键字并更新子树规模，重复关键字不插入；tree 须先初始化（正文 BST_Insert，PDF 第292页，书页第280页）。 */
Ch07Status ch07_bst_insert(Ch07BinarySearchTree *tree, int key, int *inserted);
/* 功能：清除已初始化目标树并按输入顺序逐个插入数组元素（正文 Create_BST，PDF 第292页，书页第280页）。 */
Ch07Status ch07_create_bst(Ch07BinarySearchTree *tree, const int *keys,
                           size_t length);
/* 功能：首次使用或 destroy 后初始化空二叉排序树；不得覆盖仍持有节点的树（C 动态节点所有权接口）。 */
void ch07_bst_init(Ch07BinarySearchTree *tree);
/* 功能：释放已初始化二叉排序树的全部节点并清零状态（C 动态内存所有权接口）。 */
void ch07_bst_destroy(Ch07BinarySearchTree *tree);

#endif
