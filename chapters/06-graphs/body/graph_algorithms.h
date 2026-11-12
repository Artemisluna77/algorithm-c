#ifndef CH06_GRAPH_ALGORITHMS_H
#define CH06_GRAPH_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

// 功能：为本章印刷算法提供可直接调用的动态邻接矩阵测试接口；书中固定数组结构另列于 graph_source_types.h。
// 以下动态结构是编译/测试上下文，不是新增的印刷代码块。
// 来源：适配第6章图算法；原文位置见各算法实现前的注释。
typedef struct {
    char *labels;
    int *edges;
    size_t vertex_count;
    bool directed;
    bool initialized;
} MatrixGraph;

// 功能：为本章印刷算法提供可直接调用的动态邻接表测试接口；邻接弧由 ListGraph 独占并释放。
// 来源：适配第6章图算法；原文位置见各算法实现前的注释。
typedef struct {
    size_t *items;
    size_t size;
    size_t capacity;
} GraphNeighborList;

typedef struct {
    char *labels;
    GraphNeighborList *adjacency;
    size_t vertex_count;
    bool directed;
    bool initialized;
} ListGraph;

// 功能：将本章加权无向图表示为便于公开操作的权值矩阵，作为最小生成树算法的测试上下文。
// 来源：适配第6章 6.4.1 的图输入；算法原文位置见最小生成树实现前的注释。
typedef struct {
    int *weights;
    unsigned char *present;
    size_t vertex_count;
    bool initialized;
} WeightedGraph;

typedef struct {
    size_t *items;
    size_t size;
    bool initialized;
} VertexList;

typedef struct {
    int *items;
    size_t size;
    bool initialized;
} IntList;

typedef struct {
    char *items;
    size_t size;
    bool initialized;
} CharList;

typedef struct {
    size_t *vertices;
    size_t length;
} GraphPath;

typedef struct {
    GraphPath *items;
    size_t size;
    size_t capacity;
    bool initialized;
} GraphPaths;

// 功能：记录生成树中的一条加权边；为算法接口返回值。
typedef struct {
    size_t from;
    size_t to;
    int weight;
} WeightedEdge;

// 功能：收集生成树边、总权值和连通性结果；边数组由结果对象拥有。
// 来源：适配第6章 6.4.1 的生成树算法。
typedef struct {
    WeightedEdge *edges;
    size_t edge_count;
    long long total_weight;
    bool complete;
    bool initialized;
} SpanningTree;

// 所有动态结构须在首次传给 Init、算法输出函数或 Destroy 前零初始化；结构体拥有的指针不得浅拷贝后重复销毁。
// 算法输出对象也须零初始化；每次调用会先释放其原有内容，成功或失败后均可调用对应 Destroy。
// 功能：初始化动态邻接矩阵；重复初始化会先释放旧数据。
bool MatrixGraphInit(MatrixGraph *graph, size_t vertex_count, bool directed);
bool MatrixGraphInitWithLabels(MatrixGraph *graph, const char *labels,
                               size_t vertex_count, bool directed);
void MatrixGraphDestroy(MatrixGraph *graph);
bool MatrixGraphAddEdge(MatrixGraph *graph, size_t from, size_t to, int weight);
bool MatrixGraphHasEdge(const MatrixGraph *graph, size_t from, size_t to);
bool MatrixGraphEdgeWeight(const MatrixGraph *graph, size_t from, size_t to, int *weight);
size_t MatrixGraphVertexCount(const MatrixGraph *graph);
bool MatrixGraphIsDirected(const MatrixGraph *graph);
bool MatrixGraphLabel(const MatrixGraph *graph, size_t vertex, char *label);

// 功能：初始化动态邻接表；首次调用前 graph 须零初始化，重复初始化会先释放旧数据。
bool ListGraphInit(ListGraph *graph, size_t vertex_count, bool directed);
bool ListGraphInitWithLabels(ListGraph *graph, const char *labels,
                             size_t vertex_count, bool directed);
void ListGraphDestroy(ListGraph *graph);
bool ListGraphAddEdge(ListGraph *graph, size_t from, size_t to);
size_t ListGraphVertexCount(const ListGraph *graph);
bool ListGraphIsDirected(const ListGraph *graph);
bool ListGraphLabel(const ListGraph *graph, size_t vertex, char *label);
size_t ListGraphNeighborCount(const ListGraph *graph, size_t vertex);
bool ListGraphNeighborAt(const ListGraph *graph, size_t vertex, size_t index,
                         size_t *neighbor);

// 功能：初始化加权无向图；首次调用前 graph 须零初始化，重复初始化会先释放旧数据。
bool WeightedGraphInit(WeightedGraph *graph, size_t vertex_count);
void WeightedGraphDestroy(WeightedGraph *graph);
bool WeightedGraphAddEdge(WeightedGraph *graph, size_t from, size_t to, int weight);
size_t WeightedGraphVertexCount(const WeightedGraph *graph);
bool WeightedGraphGetEdge(const WeightedGraph *graph, size_t from, size_t to,
                          int *weight);

// 功能：释放算法返回的顶点、整数、标签或路径列表。
// 来源：C17 动态返回值所有权辅助接口。
void VertexListDestroy(VertexList *list);
void IntListDestroy(IntList *list);
void CharListDestroy(CharList *list);
void GraphPathsDestroy(GraphPaths *paths);
void SpanningTreeDestroy(SpanningTree *tree);

// 功能：以邻接表和邻接矩阵分别遍历所有连通分量。
// 来源：《2027数据结构》第6章 6.3.1；PDF第227页；书页第215页。
bool breadthFirstTraverseList(const ListGraph *graph, VertexList *order);
bool breadthFirstTraverseMatrix(const MatrixGraph *graph, VertexList *order);

// 功能：以邻接表和邻接矩阵分别从指定顶点执行一次广度优先搜索。
bool breadthFirstFromList(const ListGraph *graph, size_t start, VertexList *order);
bool breadthFirstFromMatrix(const MatrixGraph *graph, size_t start, VertexList *order);

// 功能：求无权邻接表图从源点到各顶点的最短路径边数；不可达顶点记为 -1。
// 来源：《2027数据结构》第6章 6.3.1；PDF第228页；书页第216页。
bool breadthFirstShortestDistances(const ListGraph *graph, size_t start,
                                   IntList *distances);

// 功能：以邻接表和邻接矩阵分别遍历所有连通分量，返回先序访问顺序。
// 来源：《2027数据结构》第6章 6.3.2；PDF第229页；书页第217页。
bool depthFirstTraverseList(const ListGraph *graph, VertexList *order);
bool depthFirstTraverseMatrix(const MatrixGraph *graph, VertexList *order);

// 功能：用通用框架、Prim 或 Kruskal 算法构造最小生成树。
// 来源：《2027数据结构》第6章 6.4.1；PDF第238–240页；书页第226–228页。
bool genericMstFramework(const WeightedGraph *graph, SpanningTree *tree);
bool primMinimumSpanningTree(const WeightedGraph *graph, size_t start,
                             SpanningTree *tree);
bool kruskalMinimumSpanningTree(const WeightedGraph *graph, SpanningTree *tree);

// 功能：以 Kahn 算法执行邻接表图拓扑排序；遇到环、无效输入或内存不足时返回 false。
// 来源：《2027数据结构》第6章 6.4.4；PDF第245–246页；书页第233–234页。
bool topologicalSort(const ListGraph *graph, VertexList *order);

// 功能：在邻接矩阵或邻接表中查找顶点 after 之后的下一个邻接点；不存在时返回 -1。
// 来源：《2027数据结构》第6章 归纳总结；PDF第274页；书页第262页。
int nextNeighborMatrix(const MatrixGraph *graph, int vertex, int after);
int nextNeighborList(const ListGraph *graph, int vertex, int after);

#endif
