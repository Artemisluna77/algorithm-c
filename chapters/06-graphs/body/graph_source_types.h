#ifndef CH06_GRAPH_SOURCE_TYPES_H
#define CH06_GRAPH_SOURCE_TYPES_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define CH06_SOURCE_MAX_VERTEX_NUM 100

// 功能：定义书中邻接矩阵图的顶点表、边矩阵和当前顶点/边数。
// 来源：《2027数据结构》第6章 6.2.2；PDF第214页；书页第202页。
typedef char SourceVertexType;
typedef int SourceEdgeType;
typedef struct {
    SourceVertexType vex[CH06_SOURCE_MAX_VERTEX_NUM];
    SourceEdgeType edge[CH06_SOURCE_MAX_VERTEX_NUM][CH06_SOURCE_MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
} SourceMatrixGraph;

// 功能：定义书中邻接表图的弧结点、顶点结点及顶点/边计数。
// 来源：《2027数据结构》第6章 6.2.2；PDF第216页；书页第204页。
typedef struct SourceArcNode {
    int adjvex;
    struct SourceArcNode *nextarc;
} SourceArcNode;

typedef struct {
    SourceVertexType data;
    SourceArcNode *firstarc;
} SourceVNode;

typedef struct {
    SourceVNode vertices[CH06_SOURCE_MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
} SourceAdjListGraph;

// 功能：释放已零初始化的书中邻接表类型中的所有弧结点；顶点数组本身不动态分配。
// 来源：C17 动态内存所有权辅助接口。
static inline void SourceAdjListGraphDestroy(SourceAdjListGraph *graph) {
    if (graph == NULL) {
        return;
    }
    for (size_t vertex = 0; vertex < CH06_SOURCE_MAX_VERTEX_NUM; ++vertex) {
        SourceArcNode *arc = graph->vertices[vertex].firstarc;
        while (arc != NULL) {
            SourceArcNode *next = arc->nextarc;
            free(arc);
            arc = next;
        }
        graph->vertices[vertex].firstarc = NULL;
    }
    graph->vexnum = 0;
    graph->arcnum = 0;
}

#endif
