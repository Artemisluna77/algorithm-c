#include "tree_solutions.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ConstNodeArray {
    const BinaryNode **items;
    size_t length;
    size_t capacity;
    size_t front;
} ConstNodeArray;

typedef struct MutableNodeArray {
    BinaryNode **items;
    size_t length;
    size_t capacity;
    size_t front;
} MutableNodeArray;

typedef struct NodePath {
    const BinaryNode **items;
    size_t length;
    size_t capacity;
} NodePath;

typedef struct SubtreeBounds {
    int minimum;
    int maximum;
    int present;
} SubtreeBounds;

typedef struct StringBuilder {
    char *data;
    size_t length;
    size_t capacity;
    int ok;
} StringBuilder;

// 功能：将只读二叉树结点加入动态队列，并在需要时安全扩容。
static int PushConstNode(ConstNodeArray *queue, const BinaryNode *node) {
    const BinaryNode **items;
    size_t capacity;
    if (queue->length == queue->capacity) {
        if (queue->capacity == 0) {
            capacity = 8;
        } else if (queue->capacity > SIZE_MAX / 2) {
            return 0;
        } else {
            capacity = queue->capacity * 2;
        }
        if (capacity > SIZE_MAX / sizeof(*items)) {
            return 0;
        }
        items = (const BinaryNode **)realloc(queue->items, capacity * sizeof(*items));
        if (items == NULL) {
            return 0;
        }
        queue->items = items;
        queue->capacity = capacity;
    }
    queue->items[queue->length++] = node;
    return 1;
}

// 功能：将可修改二叉树结点加入动态队列，并在需要时安全扩容。
static int PushMutableNode(MutableNodeArray *queue, BinaryNode *node) {
    BinaryNode **items;
    size_t capacity;
    if (queue->length == queue->capacity) {
        if (queue->capacity == 0) {
            capacity = 8;
        } else if (queue->capacity > SIZE_MAX / 2) {
            return 0;
        } else {
            capacity = queue->capacity * 2;
        }
        if (capacity > SIZE_MAX / sizeof(*items)) {
            return 0;
        }
        items = (BinaryNode **)realloc(queue->items, capacity * sizeof(*items));
        if (items == NULL) {
            return 0;
        }
        queue->items = items;
        queue->capacity = capacity;
    }
    queue->items[queue->length++] = node;
    return 1;
}

// 功能：把一个结点追加到根至当前结点的路径缓冲区。
static int PushPath(NodePath *path, const BinaryNode *node) {
    const BinaryNode **items;
    size_t capacity;
    if (path->length == path->capacity) {
        if (path->capacity == 0) {
            capacity = 8;
        } else if (path->capacity > SIZE_MAX / 2) {
            return 0;
        } else {
            capacity = path->capacity * 2;
        }
        if (capacity > SIZE_MAX / sizeof(*items)) {
            return 0;
        }
        items = (const BinaryNode **)realloc(path->items, capacity * sizeof(*items));
        if (items == NULL) {
            return 0;
        }
        path->items = items;
        path->capacity = capacity;
    }
    path->items[path->length++] = node;
    return 1;
}

static int FindPath(const BinaryNode *node, const BinaryNode *target,
                    NodePath *path, int *ok) {
    if (node == NULL || !*ok) {
        return 0;
    }
    if (!PushPath(path, node)) {
        *ok = 0;
        return 0;
    }
    if (node == target || FindPath(node->left, target, path, ok) ||
        FindPath(node->right, target, path, ok)) {
        return 1;
    }
    --path->length;
    return 0;
}

static int FindValuePath(const BinaryNode *node, int value,
                         NodePath *path, int *ok) {
    if (node == NULL || !*ok) {
        return 0;
    }
    if (!PushPath(path, node)) {
        *ok = 0;
        return 0;
    }
    if (node->data == value || FindValuePath(node->left, value, path, ok) ||
        FindValuePath(node->right, value, path, ok)) {
        return 1;
    }
    --path->length;
    return 0;
}

static void DeleteNodes(BinaryNode *root) {
    if (root == NULL) {
        return;
    }
    DeleteNodes(root->left);
    DeleteNodes(root->right);
    free(root);
}

static int KthPreorderValueImpl(const BinaryNode *node, size_t *remaining,
                                int *value) {
    if (node == NULL || *remaining == 0) {
        return 0;
    }
    --*remaining;
    if (*remaining == 0) {
        *value = node->data;
        return 1;
    }
    return KthPreorderValueImpl(node->left, remaining, value) ||
           KthPreorderValueImpl(node->right, remaining, value);
}

static void ToPostorder(const int *preorder, size_t start, size_t length,
                        int *postorder, size_t *output) {
    size_t child_length;
    if (length == 0) {
        return;
    }
    child_length = (length - 1) / 2;
    ToPostorder(preorder, start + 1, child_length, postorder, output);
    ToPostorder(preorder, start + 1 + child_length, child_length, postorder, output);
    postorder[(*output)++] = preorder[start];
}

static void LinkLeaves(BinaryNode *node, BinaryNode **previous,
                       BinaryNode **first) {
    if (node == NULL) {
        return;
    }
    LinkLeaves(node->left, previous, first);
    if (node->left == NULL && node->right == NULL) {
        if (*first == NULL) {
            *first = node;
        } else {
            (*previous)->right = node;
        }
        *previous = node;
    }
    LinkLeaves(node->right, previous, first);
}

static int CheckedAdd64(int64_t first, int64_t second, int64_t *result) {
    if ((second > 0 && first > INT64_MAX - second) ||
        (second < 0 && first < INT64_MIN - second)) {
        return 0;
    }
    *result = first + second;
    return 1;
}

static int MultiplyWeightDepth(int weight, int64_t depth, int64_t *result) {
    uint64_t magnitude;
    uint64_t unsigned_depth;
    uint64_t product;
    uint64_t negative_limit = (uint64_t)INT64_MAX + UINT64_C(1);
    if (depth < 0) {
        return 0;
    }
    if (weight == 0 || depth == 0) {
        *result = 0;
        return 1;
    }
    magnitude = weight < 0 ? (uint64_t)(-(int64_t)weight) : (uint64_t)weight;
    unsigned_depth = (uint64_t)depth;
    if (weight > 0) {
        if (unsigned_depth > (uint64_t)INT64_MAX / magnitude) {
            return 0;
        }
        *result = (int64_t)(unsigned_depth * magnitude);
        return 1;
    }
    if (unsigned_depth > negative_limit / magnitude) {
        return 0;
    }
    product = unsigned_depth * magnitude;
    *result = product == negative_limit ? INT64_MIN : -(int64_t)product;
    return 1;
}

static int WeightedPathLengthImpl(const WeightedNode *node, int64_t depth,
                                  int64_t *result) {
    int64_t own;
    int64_t left;
    int64_t right;
    if (node == NULL) {
        *result = 0;
        return 1;
    }
    if (node->left == NULL && node->right == NULL) {
        return MultiplyWeightDepth(node->weight, depth, result);
    }
    if (depth == INT64_MAX ||
        !WeightedPathLengthImpl(node->left, depth + 1, &left) ||
        !WeightedPathLengthImpl(node->right, depth + 1, &right)) {
        return 0;
    }
    return CheckedAdd64(left, right, &own) ? (*result = own, 1) : 0;
}

static int WeightedPathLengthPostorderImpl(const WeightedNode *node,
                                           int64_t *result,
                                           int *subtree_weight) {
    int64_t left_wpl;
    int64_t right_wpl;
    int64_t total;
    int64_t combined_weight;
    int left_weight;
    int right_weight;
    if (node == NULL) {
        *result = 0;
        *subtree_weight = 0;
        return 1;
    }
    if (node->left == NULL && node->right == NULL) {
        *result = 0;
        *subtree_weight = node->weight;
        return 1;
    }
    if (!WeightedPathLengthPostorderImpl(node->left, &left_wpl, &left_weight) ||
        !WeightedPathLengthPostorderImpl(node->right, &right_wpl, &right_weight)) {
        return 0;
    }
    combined_weight = (int64_t)left_weight + (int64_t)right_weight;
    if (combined_weight < INT_MIN || combined_weight > INT_MAX ||
        !CheckedAdd64(left_wpl, right_wpl, &total) ||
        !CheckedAdd64(total, combined_weight, &total)) {
        return 0;
    }
    *subtree_weight = (int)combined_weight;
    *result = total;
    return 1;
}

static void UpdateInternalWeights(WeightedNode *node) {
    if (node == NULL || (node->left == NULL && node->right == NULL)) {
        return;
    }
    UpdateInternalWeights(node->left);
    UpdateInternalWeights(node->right);
    node->weight = (node->left == NULL ? 0 : node->left->weight) +
                   (node->right == NULL ? 0 : node->right->weight);
}

static int AppendString(StringBuilder *builder, const char *value, size_t length) {
    char *new_data;
    size_t needed;
    size_t capacity;
    if (!builder->ok || length > SIZE_MAX - builder->length - 1) {
        builder->ok = 0;
        return 0;
    }
    needed = builder->length + length + 1;
    if (needed > builder->capacity) {
        capacity = builder->capacity == 0 ? 32 : builder->capacity;
        while (capacity < needed) {
            if (capacity > SIZE_MAX / 2) {
                capacity = needed;
                break;
            }
            capacity *= 2;
        }
        new_data = (char *)realloc(builder->data, capacity);
        if (new_data == NULL) {
            builder->ok = 0;
            return 0;
        }
        builder->data = new_data;
        builder->capacity = capacity;
    }
    if (length != 0) {
        memcpy(builder->data + builder->length, value, length);
    }
    builder->length += length;
    builder->data[builder->length] = '\0';
    return 1;
}

static size_t ExpressionDataLength(const char data[10]) {
    size_t length = 0;
    while (length < 10 && data[length] != '\0') {
        ++length;
    }
    return length;
}

static void ExpressionToInfixImpl(const ExpressionNode *node, size_t depth,
                                  StringBuilder *builder) {
    int leaf;
    size_t length;
    if (node == NULL || !builder->ok) {
        return;
    }
    leaf = node->left == NULL && node->right == NULL;
    length = ExpressionDataLength(node->data);
    if (leaf) {
        (void)AppendString(builder, node->data, length);
        return;
    }
    if (depth > 1) {
        (void)AppendString(builder, "(", 1);
    }
    ExpressionToInfixImpl(node->left, depth + 1, builder);
    (void)AppendString(builder, node->data, length);
    ExpressionToInfixImpl(node->right, depth + 1, builder);
    if (depth > 1) {
        (void)AppendString(builder, ")", 1);
    }
}

static int HasNonRootWithoutParent(const SequentialTree *tree) {
    size_t index;
    if (tree->elementCount > SEQUENTIAL_TREE_MAX_SIZE) {
        return 1;
    }
    for (index = 1; index < tree->elementCount; ++index) {
        if (tree->nodes[index] != SEQUENTIAL_TREE_EMPTY_NODE &&
            tree->nodes[(index - 1) / 2] == SEQUENTIAL_TREE_EMPTY_NODE) {
            return 1;
        }
    }
    return 0;
}

static int IsStrictBstInorder(const SequentialTree *tree, size_t index,
                             int *previous, int *has_previous) {
    size_t left;
    size_t right;
    if (index >= tree->elementCount || tree->nodes[index] == SEQUENTIAL_TREE_EMPTY_NODE) {
        return 1;
    }
    left = index * 2 + 1;
    right = left + 1;
    if (!IsStrictBstInorder(tree, left, previous, has_previous)) {
        return 0;
    }
    if (*has_previous && tree->nodes[index] <= *previous) {
        return 0;
    }
    *previous = tree->nodes[index];
    *has_previous = 1;
    return IsStrictBstInorder(tree, right, previous, has_previous);
}

static int IsStrictBstByBounds(const SequentialTree *tree, size_t index,
                               SubtreeBounds *bounds) {
    size_t left;
    size_t right;
    SubtreeBounds current;
    if (index >= tree->elementCount) {
        return 1;
    }
    if (tree->nodes[index] == SEQUENTIAL_TREE_EMPTY_NODE) {
        bounds[index].present = 0;
        return 1;
    }
    left = index * 2 + 1;
    right = left + 1;
    if (!IsStrictBstByBounds(tree, left, bounds) ||
        !IsStrictBstByBounds(tree, right, bounds)) {
        return 0;
    }
    current.minimum = tree->nodes[index];
    current.maximum = tree->nodes[index];
    current.present = 1;
    if (left < tree->elementCount && bounds[left].present) {
        if (bounds[left].maximum >= tree->nodes[index]) {
            return 0;
        }
        current.minimum = bounds[left].minimum;
    }
    if (right < tree->elementCount && bounds[right].present) {
        if (bounds[right].minimum <= tree->nodes[index]) {
            return 0;
        }
        current.maximum = bounds[right].maximum;
    }
    bounds[index] = current;
    return 1;
}

// 功能：使用层次遍历和当前层最右结点位置计算二叉树高度。
// 来源：《2027数据结构》第5章 5.3.4 综合题03；PDF第170–171页；书页第158–159页。
int BinaryTreeHeightByLevel(const BinaryNode *root) {
    ConstNodeArray queue = {NULL, 0, 0, 0};
    int height = 0;
    if (root == NULL) {
        return 0;
    }
    if (!PushConstNode(&queue, root)) {
        return -1;
    }
    while (queue.front < queue.length) {
        const size_t level_end = queue.length;
        if (height == INT_MAX) {
            free(queue.items);
            return -1;
        }
        ++height;
        while (queue.front < level_end) {
            const BinaryNode *node = queue.items[queue.front++];
            if ((node->left != NULL && !PushConstNode(&queue, node->left)) ||
                (node->right != NULL && !PushConstNode(&queue, node->right))) {
                free(queue.items);
                return -1;
            }
        }
    }
    free(queue.items);
    return height;
}

// 功能：递归比较左右子树高度并计算二叉树高度。
// 来源：《2027数据结构》第5章 5.3.4 综合题03；PDF第171页；书页第159页。
int BinaryTreeHeightRecursive(const BinaryNode *root) {
    int left;
    int right;
    if (root == NULL) {
        return 0;
    }
    left = BinaryTreeHeightRecursive(root->left);
    right = BinaryTreeHeightRecursive(root->right);
    if (left < 0 || right < 0 || (left > right ? left : right) == INT_MAX) {
        return -1;
    }
    return (left > right ? left : right) + 1;
}

// 功能：层次遍历并在首次遇到空位置后拒绝后续非空结点。
// 来源：《2027数据结构》第5章 5.3.4 综合题04；PDF第171页；书页第159页。
int IsCompleteBinaryTree(const BinaryNode *root) {
    ConstNodeArray queue = {NULL, 0, 0, 0};
    size_t front = 0;
    int saw_missing_child = 0;
    if (root == NULL) {
        return 1;
    }
    if (!PushConstNode(&queue, root)) {
        return -1;
    }
    while (front < queue.length) {
        const BinaryNode *node = queue.items[front++];
        if (node->left != NULL) {
            if (saw_missing_child || !PushConstNode(&queue, node->left)) {
                free(queue.items);
                return saw_missing_child ? 0 : -1;
            }
        } else {
            saw_missing_child = 1;
        }
        if (node->right != NULL) {
            if (saw_missing_child || !PushConstNode(&queue, node->right)) {
                free(queue.items);
                return saw_missing_child ? 0 : -1;
            }
        } else {
            saw_missing_child = 1;
        }
    }
    free(queue.items);
    return 1;
}

// 功能：递归统计左右孩子均非空的双分支结点。
// 来源：《2027数据结构》第5章 5.3.4 综合题05；PDF第172页；书页第160页。
size_t CountTwoChildNodes(const BinaryNode *root) {
    if (root == NULL) {
        return 0;
    }
    return (root->left != NULL && root->right != NULL ? 1u : 0u) +
           CountTwoChildNodes(root->left) + CountTwoChildNodes(root->right);
}

// 功能：递归交换每个结点的左右子树。
// 来源：《2027数据结构》第5章 5.3.4 综合题06；PDF第172页；书页第160页。
void MirrorBinaryTree(BinaryNode *root) {
    BinaryNode *temporary;
    if (root == NULL) {
        return;
    }
    MirrorBinaryTree(root->left);
    MirrorBinaryTree(root->right);
    temporary = root->left;
    root->left = root->right;
    root->right = temporary;
}

// 功能：按先序次序查询第 k 个结点值，k 从 1 开始。
// 来源：《2027数据结构》第5章 5.3.4 综合题07；PDF第172–173页；书页第160–161页。
int KthPreorderValue(const BinaryNode *root, size_t k, int *value) {
    if (k == 0 || value == NULL) {
        return 0;
    }
    return KthPreorderValueImpl(root, &k, value);
}

// 功能：以后序顺序释放以 root 为根的二叉树子树并置空根指针。
// 来源：《2027数据结构》第5章 5.3.4 综合题08；PDF第173页；书页第161页。
void DeleteSubtree(BinaryNode **root) {
    if (root == NULL) {
        return;
    }
    DeleteNodes(*root);
    *root = NULL;
}

// 功能：层次遍历并删除值等于目标值的结点及其整棵子树。
// 来源：《2027数据结构》第5章 5.3.4 综合题08；PDF第173页；书页第161页。
int DeleteSubtreesWithValue(BinaryNode **root, int value) {
    MutableNodeArray queue = {NULL, 0, 0, 0};
    if (root == NULL) {
        return 0;
    }
    if (*root == NULL) {
        return 1;
    }
    if ((*root)->data == value) {
        DeleteSubtree(root);
        return 1;
    }
    if (!PushMutableNode(&queue, *root)) {
        return 0;
    }
    while (queue.front < queue.length) {
        BinaryNode *node = queue.items[queue.front++];
        if (node->left != NULL) {
            if (node->left->data == value) {
                DeleteSubtree(&node->left);
            } else if (!PushMutableNode(&queue, node->left)) {
                free(queue.items);
                return 0;
            }
        }
        if (node->right != NULL) {
            if (node->right->data == value) {
                DeleteSubtree(&node->right);
            } else if (!PushMutableNode(&queue, node->right)) {
                free(queue.items);
                return 0;
            }
        }
    }
    free(queue.items);
    return 1;
}

// 功能：按先序寻找目标值并返回根至目标结点父结点的值序列。
// 来源：《2027数据结构》第5章 5.3.4 综合题09；PDF第174页；书页第162页。
IntArray AncestorsOfValue(const BinaryNode *root, int value) {
    NodePath path = {NULL, 0, 0};
    IntArray ancestors = {NULL, 0, 1};
    size_t i;
    int ok = 1;
    if (!FindValuePath(root, value, &path, &ok)) {
        if (!ok) {
            ancestors.ok = 0;
        }
        free(path.items);
        return ancestors;
    }
    if (path.length > 1) {
        if (path.length - 1 > SIZE_MAX / sizeof(int)) {
            ancestors.ok = 0;
        } else {
            ancestors.data = (int *)malloc((path.length - 1) * sizeof(int));
            if (ancestors.data == NULL) {
                ancestors.ok = 0;
            } else {
                for (i = 0; i + 1 < path.length; ++i) {
                    ancestors.data[ancestors.length++] = path.items[i]->data;
                }
            }
        }
    }
    free(path.items);
    return ancestors;
}

// 功能：比较两条根到目标结点的路径并返回最后一个公共结点。
// 来源：依据《2027数据结构》第5章 5.3.4 综合题10 的祖先栈规则，用动态路径数组实现；PDF第174–175页；书页第162–163页。
const BinaryNode *LowestCommonAncestor(const BinaryNode *root,
                                       const BinaryNode *first,
                                       const BinaryNode *second) {
    NodePath first_path = {NULL, 0, 0};
    NodePath second_path = {NULL, 0, 0};
    const BinaryNode *common = NULL;
    size_t i;
    size_t shared;
    int ok = 1;
    if (first == NULL || second == NULL ||
        !FindPath(root, first, &first_path, &ok) || !ok ||
        !FindPath(root, second, &second_path, &ok) || !ok) {
        free(first_path.items);
        free(second_path.items);
        return NULL;
    }
    shared = first_path.length < second_path.length
                 ? first_path.length
                 : second_path.length;
    for (i = 0; i < shared && first_path.items[i] == second_path.items[i]; ++i) {
        common = first_path.items[i];
    }
    free(first_path.items);
    free(second_path.items);
    return common;
}

// 功能：按层次遍历统计二叉树的最大层宽。
// 来源：《2027数据结构》第5章 5.3.4 综合题11；PDF第175–176页；书页第163–164页。
int BinaryTreeWidth(const BinaryNode *root) {
    ConstNodeArray queue = {NULL, 0, 0, 0};
    size_t front = 0;
    size_t maximum = 0;
    if (root == NULL) {
        return 0;
    }
    if (!PushConstNode(&queue, root)) {
        return -1;
    }
    while (front < queue.length) {
        const size_t level_end = queue.length;
        const size_t width = level_end - front;
        if (width > (size_t)INT_MAX) {
            free(queue.items);
            return -1;
        }
        if (width > maximum) {
            maximum = width;
        }
        while (front < level_end) {
            const BinaryNode *node = queue.items[front++];
            if ((node->left != NULL && !PushConstNode(&queue, node->left)) ||
                (node->right != NULL && !PushConstNode(&queue, node->right))) {
                free(queue.items);
                return -1;
            }
        }
    }
    free(queue.items);
    return (int)maximum;
}

// 功能：将满二叉树先序序列递归分割并输出后序序列。
// 来源：《2027数据结构》第5章 5.3.4 综合题12；PDF第176页；书页第164页。
IntArray FullTreePreorderToPostorder(const int *preorder, size_t length) {
    IntArray postorder = {NULL, 0, 1};
    size_t reduced_length = length;
    size_t output = 0;
    if (preorder == NULL && length != 0) {
        postorder.ok = 0;
        return postorder;
    }
    while (reduced_length > 1 && reduced_length % 2 == 1) {
        reduced_length = (reduced_length - 1) / 2;
    }
    if (reduced_length != 1 && length != 0) {
        postorder.ok = 0;
        return postorder;
    }
    if (length == 0) {
        return postorder;
    }
    if (length > SIZE_MAX / sizeof(int)) {
        postorder.ok = 0;
        return postorder;
    }
    postorder.data = (int *)malloc(length * sizeof(int));
    if (postorder.data == NULL) {
        postorder.ok = 0;
        return postorder;
    }
    ToPostorder(preorder, 0, length, postorder.data, &output);
    postorder.length = output;
    return postorder;
}

// 功能：运行书中 ABCDEFG 满二叉树先序转后序的示例数据。
// 来源：《2027数据结构》第5章 5.3.4 综合题12 示例代码；PDF第176页；书页第164页。
IntArray PreorderToPostorderExample(void) {
    const int preorder[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    return FullTreePreorderToPostorder(preorder, sizeof(preorder) / sizeof(preorder[0]));
}


// 功能：按中序次序把叶结点串接为单链表并返回表头。
// 来源：《2027数据结构》第5章 5.3.4 综合题13；PDF第176–177页；书页第164–165页。
BinaryNode *LinkLeavesInorder(BinaryNode *root) {
    BinaryNode *previous = NULL;
    BinaryNode *first = NULL;
    LinkLeaves(root, &previous, &first);
    if (previous != NULL) {
        previous->right = NULL;
    }
    return first;
}

// 功能：忽略结点值，递归判断两棵二叉树结构是否相似。
// 来源：《2027数据结构》第5章 5.3.4 综合题14；PDF第177页；书页第165页。
int AreStructurallySimilar(const BinaryNode *first, const BinaryNode *second) {
    if (first == NULL || second == NULL) {
        return first == NULL && second == NULL;
    }
    return AreStructurallySimilar(first->left, second->left) &&
           AreStructurallySimilar(first->right, second->right);
}

// 功能：从根深度 0 开始累计叶结点权值与路径长度的乘积。
// 来源：《2027数据结构》第5章 5.3.4 综合题15 解法一；PDF第178页；书页第166页。
int WeightedPathLength(const WeightedNode *root, int64_t *result) {
    if (result == NULL) {
        return 0;
    }
    return WeightedPathLengthImpl(root, 0, result);
}

// 功能：后序遍历时用左右子树权值和覆盖内部结点并累计 WPL。
// 来源：《2027数据结构》第5章 5.3.4 综合题15 解法二；PDF第178页；书页第166页。
int WeightedPathLengthPostorder(WeightedNode *root, int64_t *result) {
    int64_t calculated;
    int calculated_weight;
    if (result == NULL) {
        return 0;
    }
    if (!WeightedPathLengthPostorderImpl(root, &calculated, &calculated_weight)) {
        return 0;
    }
    UpdateInternalWeights(root);
    *result = calculated;
    return 1;
}

// 功能：把表达式树转换成根运算符不加括号、内部子表达式加括号的中缀式。
// 来源：《2027数据结构》第5章 5.3.4 综合题16；PDF第179页；书页第167页。
char *ExpressionToInfix(const ExpressionNode *root) {
    StringBuilder builder = {NULL, 0, 0, 1};
    ExpressionToInfixImpl(root, 1, &builder);
    if (!builder.ok) {
        free(builder.data);
        return NULL;
    }
    if (builder.data == NULL) {
        builder.data = (char *)malloc(1);
        if (builder.data == NULL) {
            return NULL;
        }
        builder.data[0] = '\0';
    }
    return builder.data;
}

// 功能：对顺序存储二叉树做中序遍历并检查结点值严格递增。
// 来源：《2027数据结构》第5章 5.3.4 综合题17 解答1；PDF第179页；书页第167页。
int IsBinarySearchTreeInorder(const SequentialTree *tree) {
    int previous = 0;
    int has_previous = 0;
    if (tree == NULL || tree->elementCount > SEQUENTIAL_TREE_MAX_SIZE ||
        HasNonRootWithoutParent(tree)) {
        return 0;
    }
    return tree->elementCount == 0 ||
           IsStrictBstInorder(tree, 0, &previous, &has_previous);
}

// 功能：自底向上汇总顺序存储二叉树每棵子树的最小值和最大值并检查 BST 性质。
// 来源：《2027数据结构》第5章 5.3.4 综合题17 解答2；PDF第180页；书页第168页。
int IsBinarySearchTreeBySubtreeBounds(const SequentialTree *tree) {
    SubtreeBounds bounds[SEQUENTIAL_TREE_MAX_SIZE] = {{0, 0, 0}};
    if (tree == NULL || tree->elementCount > SEQUENTIAL_TREE_MAX_SIZE ||
        HasNonRootWithoutParent(tree)) {
        return 0;
    }
    if (tree->elementCount == 0 || tree->nodes[0] == SEQUENTIAL_TREE_EMPTY_NODE) {
        return 1;
    }
    return IsStrictBstByBounds(tree, 0, bounds);
}

// 功能：按完全二叉树数组下标逐级上移，返回两个结点的最近公共祖先值。
// 来源：《2027数据结构》第5章 5.2.4 解答05；PDF第151–152页；书页第139–140页。
int SequentialLowestCommonAncestor(const SequentialTree *tree,
                                   size_t firstIndex, size_t secondIndex,
                                   int *value) {
    if (tree == NULL || value == NULL ||
        tree->elementCount > SEQUENTIAL_TREE_MAX_SIZE ||
        firstIndex >= tree->elementCount || secondIndex >= tree->elementCount ||
        tree->nodes[firstIndex] == SEQUENTIAL_TREE_EMPTY_NODE ||
        tree->nodes[secondIndex] == SEQUENTIAL_TREE_EMPTY_NODE ||
        HasNonRootWithoutParent(tree)) {
        return 0;
    }
    while (firstIndex != secondIndex) {
        if (firstIndex > secondIndex) {
            firstIndex = (firstIndex - 1) / 2;
        } else {
            secondIndex = (secondIndex - 1) / 2;
        }
    }
    *value = tree->nodes[firstIndex];
    return 1;
}
