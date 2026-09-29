#ifndef CH06_GRAPH_QUESTION_TYPES_H
#define CH06_GRAPH_QUESTION_TYPES_H

#define CH06_QUESTION_MAX_VERTEX_NUM 100

// 同构结构体按题目分别保留，避免把一道题的原始类型改成另一题的共享别名，便于逐题溯源。

// 功能：保留 2021 年欧拉路径题中给出的邻接矩阵图类型定义。
// 来源：《2027数据结构》第6章 6.2.4 试题07；PDF第221页；书页第209页。
typedef struct {
    int numVertices;
    int numEdges;
    char VerticesList[CH06_QUESTION_MAX_VERTEX_NUM];
    int Edge[CH06_QUESTION_MAX_VERTEX_NUM][CH06_QUESTION_MAX_VERTEX_NUM];
} EulerTrail2021MGraph;

// 功能：保留 2023 年 K 顶点题中给出的邻接矩阵图类型定义。
// 来源：《2027数据结构》第6章 6.2.4 试题08；PDF第221页；书页第209页。
typedef struct {
    int numVertices;
    int numEdges;
    char VerticesList[CH06_QUESTION_MAX_VERTEX_NUM];
    int Edge[CH06_QUESTION_MAX_VERTEX_NUM][CH06_QUESTION_MAX_VERTEX_NUM];
} KVertices2023MGraph;

// 功能：保留拓扑序唯一性题中给出的邻接矩阵图类型定义。
// 来源：《2027数据结构》第6章 6.4.4 试题13；PDF第257页；书页第245页。
typedef struct {
    int numVertices;
    int numEdges;
    char VerticesList[CH06_QUESTION_MAX_VERTEX_NUM];
    int Edge[CH06_QUESTION_MAX_VERTEX_NUM][CH06_QUESTION_MAX_VERTEX_NUM];
} UniqueTopologicalOrderMGraph;

#endif
