#include "tree_forest.h"

#include <stdint.h>
#include <stdlib.h>

static ChildSiblingNode *ConvertNode(const GeneralTreeNode *source, int *ok) {
    ChildSiblingNode *target;
    ChildSiblingNode *previous_child = NULL;
    size_t i;
    if (source == NULL || (source->child_count != 0 && source->children == NULL)) {
        *ok = 0;
        return NULL;
    }
    target = (ChildSiblingNode *)malloc(sizeof(*target));
    if (target == NULL) {
        *ok = 0;
        return NULL;
    }
    target->data = source->data;
    target->firstChild = NULL;
    target->nextSibling = NULL;
    for (i = 0; i < source->child_count; ++i) {
        ChildSiblingNode *converted_child = ConvertNode(source->children[i], ok);
        if (!*ok) {
            DestroyChildSibling(target);
            return NULL;
        }
        if (previous_child == NULL) {
            target->firstChild = converted_child;
        } else {
            previous_child->nextSibling = converted_child;
        }
        previous_child = converted_child;
    }
    return target;
}

static GeneralTreeNode *ConvertBack(const ChildSiblingNode *source, int *ok) {
    GeneralTreeNode *result;
    const ChildSiblingNode *child;
    size_t count = 0;
    size_t index = 0;
    if (source == NULL) {
        *ok = 0;
        return NULL;
    }
    for (child = source->firstChild; child != NULL; child = child->nextSibling) {
        if (count == SIZE_MAX) {
            *ok = 0;
            return NULL;
        }
        ++count;
    }
    result = (GeneralTreeNode *)calloc(1, sizeof(*result));
    if (result == NULL) {
        *ok = 0;
        return NULL;
    }
    result->data = source->data;
    result->child_count = count;
    if (count != 0) {
        if (count > SIZE_MAX / sizeof(*result->children)) {
            free(result);
            *ok = 0;
            return NULL;
        }
        result->children = (GeneralTreeNode **)calloc(count, sizeof(*result->children));
        if (result->children == NULL) {
            free(result);
            *ok = 0;
            return NULL;
        }
    }
    for (child = source->firstChild; child != NULL; child = child->nextSibling) {
        result->children[index] = ConvertBack(child, ok);
        if (!*ok) {
            DestroyGeneralTree(result);
            return NULL;
        }
        ++index;
    }
    return result;
}

// 功能：按左孩子-右兄弟规则将一般树转换为孩子兄弟二叉表示。
// 来源：依据《2027数据结构》第5章 5.4.2 的转换规则派生；PDF第182–183页；书页第170–171页。
ChildSiblingNode *TreeToChildSibling(const GeneralTreeNode *root) {
    int ok = 1;
    ChildSiblingNode *result;
    if (root == NULL) {
        return NULL;
    }
    result = ConvertNode(root, &ok);
    return ok ? result : NULL;
}

// 功能：把孩子兄弟表示还原为一般树，忽略根结点自身的兄弟链。
// 来源：依据《2027数据结构》第5章 5.4.2 的转换规则派生；PDF第182–183页；书页第170–171页。
GeneralTreeNode *ChildSiblingToTree(const ChildSiblingNode *root) {
    int ok = 1;
    if (root == NULL) {
        return NULL;
    }
    return ConvertBack(root, &ok);
}

// 功能：释放还原后的一般树及其动态孩子数组。
void DestroyGeneralTree(GeneralTreeNode *root) {
    size_t i;
    if (root == NULL) {
        return;
    }
    for (i = 0; i < root->child_count; ++i) {
        DestroyGeneralTree(root->children[i]);
    }
    free(root->children);
    free(root);
}

// 功能：释放结点、孩子链和兄弟链占用的动态存储。
void DestroyChildSibling(ChildSiblingNode *root) {
    if (root == NULL) {
        return;
    }
    DestroyChildSibling(root->firstChild);
    DestroyChildSibling(root->nextSibling);
    free(root);
}

// 功能：递归统计孩子兄弟表示的树或森林中的叶结点数。
// 来源：《2027数据结构》第5章 5.4.3；PDF第192页；书页第180页。
size_t CountLeaves(const ChildSiblingNode *root) {
    if (root == NULL) {
        return 0;
    }
    if (root->firstChild == NULL) {
        return 1 + CountLeaves(root->nextSibling);
    }
    return CountLeaves(root->firstChild) + CountLeaves(root->nextSibling);
}

// 功能：按孩子高度加一与兄弟高度取最大值递归计算树高。
// 来源：《2027数据结构》第5章 5.4.3；PDF第192页；书页第180页。
size_t ChildSiblingHeight(const ChildSiblingNode *root) {
    size_t child_height;
    size_t sibling_height;
    if (root == NULL) {
        return 0;
    }
    child_height = ChildSiblingHeight(root->firstChild);
    sibling_height = ChildSiblingHeight(root->nextSibling);
    return child_height + 1 > sibling_height ? child_height + 1 : sibling_height;
}
