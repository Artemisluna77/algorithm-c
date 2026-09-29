#ifndef CH06_GRAPH_ANSWERS_H
#define CH06_GRAPH_ANSWERS_H

#include "graph_algorithms.h"

// 功能：将邻接表逐边转换为邻接矩阵，保留顶点标签和有向/无向属性。
// 来源：《2027数据结构》第6章 6.2.2 试题05答案；PDF第225页；书页第213页。
bool convertAdjacencyListToMatrix(const ListGraph *graph, MatrixGraph *matrix);

// 功能：按各顶点度数的奇偶性判断连通无向图是否有欧拉回路或欧拉通路。
// 来源：《2027数据结构》第6章 6.2.4 试题07答案；PDF第225页；书页第213页。
bool hasEulerTrailByDegreeParity(const MatrixGraph *graph);

// 功能：找出出度大于入度的顶点并返回顶点标签。
// 来源：《2027数据结构》第6章 6.2.4 试题08答案；PDF第226页；书页第214页。
bool verticesWithMoreOutgoingThanIncoming(const MatrixGraph *graph, CharList *labels);

// 功能：判断无向邻接表图是否为树。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题03答案；PDF第236页；书页第224页。
bool isUndirectedTree(const ListGraph *graph);

// 功能：用深度优先搜索或广度优先搜索判断两顶点间是否存在路径。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题04答案；PDF第236–237页；书页第224–225页。
bool depthFirstReachable(const ListGraph *graph, size_t from, size_t to);
bool breadthFirstReachable(const ListGraph *graph, size_t from, size_t to);

// 功能：用回溯深度优先搜索输出两顶点之间的所有简单路径。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题05答案；PDF第237页；书页第225页。
bool findAllSimplePaths(const ListGraph *graph, size_t from, size_t to,
                        GraphPaths *paths);

// 功能：根据 DFS 完成时间递减顺序生成邻接表图的拓扑序列。
// 来源：《2027数据结构》第6章 6.4.4 试题07答案；PDF第269页；书页第257页。
bool depthFirstFinishOrder(const ListGraph *graph, VertexList *order);

// 功能：判断邻接矩阵表示的有向图是否只有唯一的拓扑序列。
// 来源：《2027数据结构》第6章 6.4.4 试题13答案；PDF第272–273页；书页第260–261页。
bool hasUniqueTopologicalOrder(const MatrixGraph *graph);

#endif
