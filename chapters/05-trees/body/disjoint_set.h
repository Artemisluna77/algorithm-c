#ifndef CHAPTER05_DISJOINT_SET_H
#define CHAPTER05_DISJOINT_SET_H

#include <stddef.h>

// 功能：定义并查集的双亲数组表示，根结点用负值保存集合规模。
// 来源：《2027数据结构》第5章 5.5.2；PDF第195页；书页第183页。
typedef struct DisjointSet {
    size_t count;
    int *parent_or_size;
} DisjointSet;

#define DISJOINT_SET_INIT {0, NULL}

// 功能：初始化零初始化的并查集双亲数组；可安全重初始化，分配失败时保留旧状态。成功返回 1，最后须销毁。
int DisjointSetInit(DisjointSet *sets, size_t size);

// 功能：释放双亲数组并清空字段。
void DisjointSetDestroy(DisjointSet *sets);

// 功能：把每个元素初始化为独立集合。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
void Initialize(DisjointSet *sets);

// 功能：不压缩路径地查找元素所属集合的根；成功返回 1 并写入 root。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int FindWithoutCompression(const DisjointSet *sets, int element, int *root);

// 功能：查找集合根并将查找路径上的结点直接连接到根。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196–197页；书页第184–185页。
int Find(DisjointSet *sets, int element, int *root);

// 功能：把第二棵集合树的根连接到第一棵集合树的根；合并成功返回 1。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int UnionRoots(DisjointSet *sets, int root1, int root2);

// 功能：按集合规模合并两棵树，使较小集合并入较大集合。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int UnionBySize(DisjointSet *sets, int root1, int root2);

// 功能：查找两个元素的根并按规模合并其集合。
int Union(DisjointSet *sets, int element1, int element2);

size_t DisjointSetSize(const DisjointSet *sets);

#endif
