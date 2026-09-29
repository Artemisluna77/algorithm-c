#ifndef CHAPTER05_TREE_SOLUTIONS_H
#define CHAPTER05_TREE_SOLUTIONS_H

#include "binary_tree.h"
#include "problem_types.h"

#include <stddef.h>
#include <stdint.h>

// 功能：用层次遍历和队列末结点位置计算二叉树高度；分配失败返回 -1。
// 来源：《2027数据结构》第5章 5.3.4 综合题03；PDF第170–171页；书页第158–159页。
int BinaryTreeHeightByLevel(const BinaryNode *root);

// 功能：递归比较左右子树高度并计算二叉树高度。
// 来源：《2027数据结构》第5章 5.3.4 综合题03；PDF第171页；书页第159页。
int BinaryTreeHeightRecursive(const BinaryNode *root);

// 功能：按层次遍历检测二叉树是否满足完全二叉树的顺序填充性质；分配失败返回 -1。
// 来源：《2027数据结构》第5章 5.3.4 综合题04；PDF第171页；书页第159页。
int IsCompleteBinaryTree(const BinaryNode *root);

// 功能：递归统计左右孩子均非空的双分支结点数。
// 来源：《2027数据结构》第5章 5.3.4 综合题05；PDF第172页；书页第160页。
size_t CountTwoChildNodes(const BinaryNode *root);

// 功能：递归交换二叉树各结点的左右子树。
// 来源：《2027数据结构》第5章 5.3.4 综合题06；PDF第172页；书页第160页。
void MirrorBinaryTree(BinaryNode *root);

// 功能：按先序遍历次序查询第 k 个结点值，k 从 1 开始；找到返回 1 并写入 value。
// 来源：《2027数据结构》第5章 5.3.4 综合题07；PDF第172–173页；书页第160–161页。
int KthPreorderValue(const BinaryNode *root, size_t k, int *value);

// 功能：按后序方式释放动态分配的子树并置空根指针。
// 来源：《2027数据结构》第5章 5.3.4 综合题08；PDF第173页；书页第161页。
void DeleteSubtree(BinaryNode **root);

// 功能：层次遍历二叉树，删除每个值为目标值的结点及其整棵子树。
// 来源：《2027数据结构》第5章 5.3.4 综合题08；PDF第173页；书页第161页。
int DeleteSubtreesWithValue(BinaryNode **root, int value);

// 功能：迭代查找目标结点并返回从根到其父结点的祖先值序列；调用者负责销毁结果。
// 来源：《2027数据结构》第5章 5.3.4 综合题09；PDF第174页；书页第162页。
IntArray AncestorsOfValue(const BinaryNode *root, int value);

// 功能：按结点指针身份查找两个结点最近公共祖先。
// 来源：《2027数据结构》第5章 5.3.4 综合题10；PDF第174–175页；书页第162–163页。
const BinaryNode *LowestCommonAncestor(const BinaryNode *root,
                                       const BinaryNode *first,
                                       const BinaryNode *second);

// 功能：层次遍历并统计二叉树的最大层宽；分配失败返回 -1。
// 来源：《2027数据结构》第5章 5.3.4 综合题11；PDF第175–176页；书页第163–164页。
int BinaryTreeWidth(const BinaryNode *root);

// 功能：将满二叉树的先序序列递归转换为后序序列；结果由调用者销毁，非法长度或分配失败时 ok=0。
// 来源：《2027数据结构》第5章 5.3.4 综合题12；PDF第176页；书页第164页。
IntArray FullTreePreorderToPostorder(const int *preorder, size_t length);

// 功能：执行书中 ABCDEFG 满二叉树先序转后序示例数据。
// 来源：《2027数据结构》第5章 5.3.4 综合题12 示例代码；PDF第176页；书页第164页。
IntArray PreorderToPostorderExample(void);

// 功能：按完全二叉树顺序存储下标公式查找最近公共祖先；空位用 SEQUENTIAL_TREE_EMPTY_NODE 表示，找到返回 1 并写入 value。
// 来源：《2027数据结构》第5章 5.2.4 解答05；PDF第151–152页；书页第139–140页。
// 注：接口使用 C 零基下标，对应原文从 1 开始的数组下标。
int SequentialLowestCommonAncestor(const SequentialTree *tree,
                                   size_t firstIndex, size_t secondIndex,
                                   int *value);

// 功能：按中序次序将叶结点链接为单链表，使用叶结点右指针保存后继。
// 来源：《2027数据结构》第5章 5.3.4 综合题13；PDF第176–177页；书页第164–165页。
BinaryNode *LinkLeavesInorder(BinaryNode *root);

// 功能：递归判断两棵二叉树的形状是否相似。
// 来源：《2027数据结构》第5章 5.3.4 综合题14；PDF第177页；书页第165页。
int AreStructurallySimilar(const BinaryNode *first, const BinaryNode *second);

// 功能：保存带权路径长度算法使用的权值与左右子树指针。
// 来源：《2027数据结构》第5章 5.3.4 综合题15；PDF第178页；书页第166页。
typedef struct WeightedNode {
    int weight;
    struct WeightedNode *left;
    struct WeightedNode *right;
} WeightedNode;

// 功能：按叶结点权值乘深度之和计算带权路径长度；结果超出 int64_t 时返回 0。
// 来源：《2027数据结构》第5章 5.3.4 综合题15；PDF第178页；书页第166页。
int WeightedPathLength(const WeightedNode *root, int64_t *result);

// 功能：后序遍历时将内部结点权值更新为左右子树权值和并累计 WPL；返回 0 表示结果溢出。
// 来源：《2027数据结构》第5章 5.3.4 综合题15；PDF第178页；书页第166页。
int WeightedPathLengthPostorder(WeightedNode *root, int64_t *result);

// 功能：中序遍历表达式树，并为非根运算子表达式添加括号；调用者负责释放字符串。
// 来源：《2027数据结构》第5章 5.3.4 综合题16；PDF第179页；书页第167页。
char *ExpressionToInfix(const ExpressionNode *root);

// 功能：用中序遍历递增检查顺序存储二叉树是否为严格二叉搜索树；空位用 SEQUENTIAL_TREE_EMPTY_NODE 表示。
// 来源：《2027数据结构》第5章 5.3.4 综合题17解答1；PDF第179页；书页第167页。
int IsBinarySearchTreeInorder(const SequentialTree *tree);

// 功能：从数组后向前汇总子树最小值和最大值以判断二叉搜索树；空位用 SEQUENTIAL_TREE_EMPTY_NODE 表示。
// 来源：《2027数据结构》第5章 5.3.4 综合题17解答2；PDF第180页；书页第168页。
int IsBinarySearchTreeBySubtreeBounds(const SequentialTree *tree);

#endif
