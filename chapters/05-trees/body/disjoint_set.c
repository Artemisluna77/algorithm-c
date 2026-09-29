#include "disjoint_set.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

// 功能：初始化双亲数组并为每个元素建立单元素集合。
int DisjointSetInit(DisjointSet *sets, size_t size) {
    int *parent_or_size = NULL;
    if (sets == NULL || size > (size_t)INT_MAX ||
        size > (size_t)-1 / sizeof(int)) {
        return 0;
    }
    if (size != 0) {
        parent_or_size = (int *)malloc(size * sizeof(int));
        if (parent_or_size == NULL) {
            return 0;
        }
    }
    free(sets->parent_or_size);
    sets->parent_or_size = parent_or_size;
    sets->count = size;
    Initialize(sets);
    return 1;
}

// 功能：释放并查集存储。
void DisjointSetDestroy(DisjointSet *sets) {
    if (sets != NULL) {
        free(sets->parent_or_size);
        sets->parent_or_size = NULL;
        sets->count = 0;
    }
}

// 功能：把双亲数组中的每个元素初始化为独立单元素集合。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
void Initialize(DisjointSet *sets) {
    size_t i;
    if (sets == NULL) {
        return;
    }
    for (i = 0; i < sets->count; ++i) {
        sets->parent_or_size[i] = -1;
    }
}

static int IsValidElement(const DisjointSet *sets, int element) {
    return sets != NULL && sets->parent_or_size != NULL && element >= 0 &&
           (size_t)element < sets->count;
}

// 功能：不压缩路径地查找元素所属集合的根。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int FindWithoutCompression(const DisjointSet *sets, int element, int *root) {
    if (root == NULL || !IsValidElement(sets, element)) {
        return 0;
    }
    while (sets->parent_or_size[element] >= 0) {
        element = sets->parent_or_size[element];
        if (element < 0 || (size_t)element >= sets->count) {
            return 0;
        }
    }
    *root = element;
    return 1;
}

// 功能：查找集合根并将路径上的元素直接连接到根。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196–197页；书页第184–185页。
int Find(DisjointSet *sets, int element, int *root) {
    int current;
    int next;
    if (root == NULL || !FindWithoutCompression(sets, element, &current)) {
        return 0;
    }
    while (element != current) {
        next = sets->parent_or_size[element];
        sets->parent_or_size[element] = current;
        element = next;
    }
    *root = current;
    return 1;
}

static int AreDistinctRoots(const DisjointSet *sets, int root1, int root2) {
    return IsValidElement(sets, root1) && IsValidElement(sets, root2) &&
           root1 != root2 && sets->parent_or_size[root1] < 0 &&
           sets->parent_or_size[root2] < 0;
}

// 功能：把第二个根连接到第一个根并合并根结点记录的集合规模。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int UnionRoots(DisjointSet *sets, int root1, int root2) {
    if (!AreDistinctRoots(sets, root1, root2)) {
        return 0;
    }
    sets->parent_or_size[root1] += sets->parent_or_size[root2];
    sets->parent_or_size[root2] = root1;
    return 1;
}

// 功能：按负数规模比较根结点，使较小集合并入较大集合。
// 来源：《2027数据结构》第5章 5.5.2；PDF第196页；书页第184页。
int UnionBySize(DisjointSet *sets, int root1, int root2) {
    int temporary;
    if (!AreDistinctRoots(sets, root1, root2)) {
        return 0;
    }
    if (sets->parent_or_size[root1] > sets->parent_or_size[root2]) {
        temporary = root1;
        root1 = root2;
        root2 = temporary;
    }
    sets->parent_or_size[root1] += sets->parent_or_size[root2];
    sets->parent_or_size[root2] = root1;
    return 1;
}

// 功能：查找两个元素的代表元并按集合规模合并其集合。
int Union(DisjointSet *sets, int element1, int element2) {
    int root1;
    int root2;
    if (!Find(sets, element1, &root1) || !Find(sets, element2, &root2)) {
        return 0;
    }
    return UnionBySize(sets, root1, root2);
}

size_t DisjointSetSize(const DisjointSet *sets) {
    return sets == NULL ? 0 : sets->count;
}
