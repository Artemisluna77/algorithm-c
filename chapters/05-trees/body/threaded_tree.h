#ifndef CHAPTER05_THREADED_TREE_H
#define CHAPTER05_THREADED_TREE_H

// 功能：定义带左右线索标志的中序线索二叉树结点。
// 来源：《2027数据结构》第5章 5.3.2；PDF第156页；书页第144页。
typedef struct ThreadNode {
    char data;
    struct ThreadNode *left;
    struct ThreadNode *right;
    int leftTag;
    int rightTag;
} ThreadNode;

// 功能：按中序递归访问结点，并为空左指针和前驱结点建立线索。
// 来源：《2027数据结构》第5章 5.3.2；PDF第156–157页；书页第144–145页。
void InThread(ThreadNode *node, ThreadNode **predecessor);

// 功能：创建中序线索并将中序序列最后一个结点的右域标为后继线索。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
void CreateInThread(ThreadNode *root);

// 功能：沿左孩子指针找到中序序列的第一个结点。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
ThreadNode *FirstNode(ThreadNode *node);

// 功能：通过右孩子或右线索取得结点的中序后继。
// 来源：《2027数据结构》第5章 5.3.2；PDF第157页；书页第145页。
ThreadNode *NextNode(ThreadNode *node);

// 功能：沿线索链非递归输出二叉树的中序序列；调用者负责释放返回字符串。
// 来源：《2027数据结构》第5章 5.3.2；PDF第158页；书页第146页。
char *ThreadedInOrder(ThreadNode *root);

#endif
