#ifndef CHAPTER05_TREE_FOREST_H
#define CHAPTER05_TREE_FOREST_H

#include <stddef.h>

#define PARENT_TREE_MAX_SIZE 100

// 功能：定义树的双亲表示结点及其定长顺序表。
// 来源：《2027数据结构》第5章 5.4.1；PDF第180–181页；书页第168–169页。
typedef struct ParentTreeNode {
    int data;
    int parent;
} ParentTreeNode;

typedef struct ParentTree {
    ParentTreeNode nodes[PARENT_TREE_MAX_SIZE];
    size_t count;
} ParentTree;

// 功能：定义树的孩子兄弟表示结点，分别连接第一个孩子和下一个兄弟。
// 来源：《2027数据结构》第5章 5.4.1；PDF第182页；书页第170页。
typedef struct ChildSiblingNode {
    int data;
    struct ChildSiblingNode *firstChild;
    struct ChildSiblingNode *nextSibling;
} ChildSiblingNode;

// 功能：表示按从左到右次序排列孩子的一般树，用于验证孩子兄弟转换。
// 来源：依据《2027数据结构》第5章 5.4.2 的转换规则派生；PDF第182–183页；书页第170–171页。
typedef struct GeneralTreeNode {
    int data;
    struct GeneralTreeNode **children;
    size_t child_count;
} GeneralTreeNode;

// 输入树中的结点和 children 数组由调用者持有。
// 功能：按左孩子-右兄弟规则将一般树转换为孩子兄弟二叉表示。
// 来源：依据《2027数据结构》第5章 5.4.2 的转换规则派生；PDF第182–183页；书页第170–171页。
ChildSiblingNode *TreeToChildSibling(const GeneralTreeNode *root);

// 功能：把孩子兄弟表示还原为动态分配的一般树，忽略根结点自身的兄弟链；调用者须用 DestroyGeneralTree 释放。
// 来源：依据《2027数据结构》第5章 5.4.2 的转换规则派生；PDF第182–183页；书页第170–171页。
GeneralTreeNode *ChildSiblingToTree(const ChildSiblingNode *root);

// 功能：释放还原后的一般树、孩子数组和所有子树。
void DestroyGeneralTree(GeneralTreeNode *root);

// 功能：释放孩子兄弟表示的结点及其孩子和兄弟链。
void DestroyChildSibling(ChildSiblingNode *root);

// 功能：递归统计孩子兄弟表示的树或森林中的叶结点数。
// 来源：《2027数据结构》第5章 5.4.3；PDF第192页；书页第180页。
size_t CountLeaves(const ChildSiblingNode *root);

// 功能：递归计算孩子兄弟表示的树的高度。
// 来源：《2027数据结构》第5章 5.4.3；PDF第192页；书页第180页。
size_t ChildSiblingHeight(const ChildSiblingNode *root);

#endif
