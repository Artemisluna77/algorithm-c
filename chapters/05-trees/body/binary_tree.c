#include "binary_tree.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct NodeQueue {
    const BinaryNode **items;
    size_t length;
    size_t capacity;
    size_t front;
} NodeQueue;

static int AppendValue(IntArray *values, size_t *capacity, int value) {
    int *new_data;
    size_t new_capacity;
    if (values->length == *capacity) {
        if (*capacity == 0) {
            new_capacity = 8;
        } else if (*capacity > SIZE_MAX / 2) {
            return 0;
        } else {
            new_capacity = *capacity * 2;
        }
        if (new_capacity > SIZE_MAX / sizeof(int)) {
            return 0;
        }
        new_data = (int *)realloc(values->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        values->data = new_data;
        *capacity = new_capacity;
    }
    values->data[values->length++] = value;
    return 1;
}

static void Traverse(const BinaryNode *root, TraversalOrder order,
                     IntArray *values, size_t *capacity) {
    if (root == NULL || !values->ok) {
        return;
    }
    if (order == Preorder && !AppendValue(values, capacity, root->data)) {
        values->ok = 0;
        return;
    }
    Traverse(root->left, order, values, capacity);
    if (order == Inorder && values->ok &&
        !AppendValue(values, capacity, root->data)) {
        values->ok = 0;
    }
    Traverse(root->right, order, values, capacity);
    if (order == Postorder && values->ok &&
        !AppendValue(values, capacity, root->data)) {
        values->ok = 0;
    }
}

static IntArray CollectDepthFirst(const BinaryNode *root, TraversalOrder order) {
    IntArray values = {NULL, 0, 1};
    size_t capacity = 0;
    Traverse(root, order, &values, &capacity);
    if (!values.ok) {
        IntArrayDestroy(&values);
    }
    return values;
}

static int QueuePush(NodeQueue *queue, const BinaryNode *node) {
    const BinaryNode **new_items;
    size_t new_capacity;
    if (queue->length == queue->capacity) {
        if (queue->capacity == 0) {
            new_capacity = 8;
        } else if (queue->capacity > SIZE_MAX / 2) {
            return 0;
        } else {
            new_capacity = queue->capacity * 2;
        }
        if (new_capacity > SIZE_MAX / sizeof(*queue->items)) {
            return 0;
        }
        new_items = (const BinaryNode **)realloc(
            queue->items, new_capacity * sizeof(*queue->items));
        if (new_items == NULL) {
            return 0;
        }
        queue->items = new_items;
        queue->capacity = new_capacity;
    }
    queue->items[queue->length++] = node;
    return 1;
}

// 功能：递归以前序顺序收集二叉树结点。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray PreOrder(const BinaryNode *root) {
    return CollectDepthFirst(root, Preorder);
}

// 功能：递归以中序顺序收集二叉树结点。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray InOrder(const BinaryNode *root) {
    return CollectDepthFirst(root, Inorder);
}

// 功能：递归以后序顺序收集二叉树结点。
// 来源：《2027数据结构》第5章 5.3.1；PDF第153页；书页第141页。
IntArray PostOrder(const BinaryNode *root) {
    return CollectDepthFirst(root, Postorder);
}

// 功能：使用队列按层次顺序收集二叉树结点。
// 来源：《2027数据结构》第5章 5.3.1；PDF第154页；书页第142页。
IntArray LevelOrder(const BinaryNode *root) {
    IntArray values = {NULL, 0, 1};
    NodeQueue queue = {NULL, 0, 0, 0};
    size_t capacity = 0;
    if (root == NULL) {
        return values;
    }
    if (!QueuePush(&queue, root)) {
        values.ok = 0;
    }
    while (values.ok && queue.front < queue.length) {
        const BinaryNode *node = queue.items[queue.front++];
        if (!AppendValue(&values, &capacity, node->data) ||
            (node->left != NULL && !QueuePush(&queue, node->left)) ||
            (node->right != NULL && !QueuePush(&queue, node->right))) {
            values.ok = 0;
        }
    }
    free(queue.items);
    if (!values.ok) {
        IntArrayDestroy(&values);
    }
    return values;
}

// 功能：释放遍历结果数组并清空字段。
void IntArrayDestroy(IntArray *array) {
    if (array != NULL) {
        free(array->data);
        array->data = NULL;
        array->length = 0;
        array->ok = 0;
    }
}

// 功能：按先序、中序或后序的访问位置递归遍历二叉树。
// 来源：依据《2027数据结构》第5章归纳总结中的 Track 模板补入访问回调；PDF第204–205页；书页第192–193页。
void Track(const BinaryNode *root, TraversalOrder order,
           VisitFunction visit, void *context) {
    if (root == NULL || visit == NULL) {
        return;
    }
    if (order == Preorder) {
        visit(root->data, context);
    }
    Track(root->left, order, visit, context);
    if (order == Inorder) {
        visit(root->data, context);
    }
    Track(root->right, order, visit, context);
    if (order == Postorder) {
        visit(root->data, context);
    }
}
