#include "graph_algorithms.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static bool product_size(size_t left, size_t right, size_t *product) {
    if (product == NULL || (right != 0 && left > (size_t)-1 / right)) {
        return false;
    }
    *product = left * right;
    return true;
}

static bool matrix_allocate(MatrixGraph *graph, size_t vertex_count,
                            bool directed) {
    size_t cell_count;
    if (graph == NULL || !product_size(vertex_count, vertex_count, &cell_count) ||
        cell_count > (size_t)-1 / sizeof(*graph->edges)) {
        return false;
    }
    graph->vertex_count = vertex_count;
    graph->directed = directed;
    graph->initialized = true;
    if (vertex_count == 0) {
        return true;
    }
    graph->labels = (char *)malloc(vertex_count * sizeof(*graph->labels));
    graph->edges = (int *)calloc(cell_count, sizeof(*graph->edges));
    if (graph->labels == NULL || graph->edges == NULL) {
        MatrixGraphDestroy(graph);
        return false;
    }
    return true;
}

bool MatrixGraphInit(MatrixGraph *graph, size_t vertex_count, bool directed) {
    MatrixGraph fresh = {0};
    if (graph == NULL || !matrix_allocate(&fresh, vertex_count, directed)) {
        MatrixGraphDestroy(&fresh);
        return false;
    }
    for (size_t i = 0; i < vertex_count; ++i) {
        fresh.labels[i] = (char)('a' + i % 26);
    }
    MatrixGraphDestroy(graph);
    *graph = fresh;
    return true;
}

bool MatrixGraphInitWithLabels(MatrixGraph *graph, const char *labels,
                               size_t vertex_count, bool directed) {
    MatrixGraph fresh = {0};
    if (graph == NULL || (vertex_count != 0 && labels == NULL) ||
        !matrix_allocate(&fresh, vertex_count, directed)) {
        MatrixGraphDestroy(&fresh);
        return false;
    }
    if (vertex_count != 0) {
        memcpy(fresh.labels, labels, vertex_count * sizeof(*labels));
    }
    MatrixGraphDestroy(graph);
    *graph = fresh;
    return true;
}

void MatrixGraphDestroy(MatrixGraph *graph) {
    if (graph == NULL) {
        return;
    }
    if (graph->initialized) {
        free(graph->labels);
        free(graph->edges);
    }
    graph->labels = NULL;
    graph->edges = NULL;
    graph->vertex_count = 0;
    graph->directed = false;
    graph->initialized = false;
}

size_t MatrixGraphVertexCount(const MatrixGraph *graph) {
    return graph != NULL && graph->initialized ? graph->vertex_count : 0;
}

bool MatrixGraphIsDirected(const MatrixGraph *graph) {
    return graph != NULL && graph->initialized && graph->directed;
}

bool MatrixGraphLabel(const MatrixGraph *graph, size_t vertex, char *label) {
    if (graph == NULL || !graph->initialized || label == NULL ||
        vertex >= graph->vertex_count) {
        return false;
    }
    *label = graph->labels[vertex];
    return true;
}

bool MatrixGraphAddEdge(MatrixGraph *graph, size_t from, size_t to, int weight) {
    if (graph == NULL || !graph->initialized || from >= graph->vertex_count ||
        to >= graph->vertex_count) {
        return false;
    }
    graph->edges[from * graph->vertex_count + to] = weight;
    if (!graph->directed) {
        graph->edges[to * graph->vertex_count + from] = weight;
    }
    return true;
}

bool MatrixGraphHasEdge(const MatrixGraph *graph, size_t from, size_t to) {
    return graph != NULL && graph->initialized && from < graph->vertex_count &&
           to < graph->vertex_count &&
           graph->edges[from * graph->vertex_count + to] != 0;
}

bool MatrixGraphEdgeWeight(const MatrixGraph *graph, size_t from, size_t to,
                           int *weight) {
    if (graph == NULL || !graph->initialized || weight == NULL ||
        from >= graph->vertex_count || to >= graph->vertex_count) {
        return false;
    }
    *weight = graph->edges[from * graph->vertex_count + to];
    return true;
}

static bool neighbor_reserve(GraphNeighborList *neighbors, size_t needed) {
    size_t capacity;
    size_t *items;
    if (neighbors == NULL) {
        return false;
    }
    if (needed <= neighbors->capacity) {
        return true;
    }
    capacity = neighbors->capacity == 0 ? 4 : neighbors->capacity;
    while (capacity < needed) {
        if (capacity > (size_t)-1 / 2) {
            capacity = needed;
            break;
        }
        capacity *= 2;
    }
    if (capacity > (size_t)-1 / sizeof(*items)) {
        return false;
    }
    items = (size_t *)realloc(neighbors->items, capacity * sizeof(*items));
    if (items == NULL) {
        return false;
    }
    neighbors->items = items;
    neighbors->capacity = capacity;
    return true;
}

static bool list_allocate(ListGraph *graph, size_t vertex_count, bool directed) {
    if (graph == NULL || vertex_count > (size_t)-1 / sizeof(*graph->adjacency)) {
        return false;
    }
    graph->vertex_count = vertex_count;
    graph->directed = directed;
    graph->initialized = true;
    if (vertex_count == 0) {
        return true;
    }
    graph->labels = (char *)malloc(vertex_count * sizeof(*graph->labels));
    graph->adjacency = (GraphNeighborList *)calloc(
        vertex_count, sizeof(*graph->adjacency));
    if (graph->labels == NULL || graph->adjacency == NULL) {
        ListGraphDestroy(graph);
        return false;
    }
    return true;
}

bool ListGraphInit(ListGraph *graph, size_t vertex_count, bool directed) {
    ListGraph fresh = {0};
    if (graph == NULL || !list_allocate(&fresh, vertex_count, directed)) {
        ListGraphDestroy(&fresh);
        return false;
    }
    for (size_t i = 0; i < vertex_count; ++i) {
        fresh.labels[i] = (char)('a' + i % 26);
    }
    ListGraphDestroy(graph);
    *graph = fresh;
    return true;
}

bool ListGraphInitWithLabels(ListGraph *graph, const char *labels,
                             size_t vertex_count, bool directed) {
    ListGraph fresh = {0};
    if (graph == NULL || (vertex_count != 0 && labels == NULL) ||
        !list_allocate(&fresh, vertex_count, directed)) {
        ListGraphDestroy(&fresh);
        return false;
    }
    if (vertex_count != 0) {
        memcpy(fresh.labels, labels, vertex_count * sizeof(*labels));
    }
    ListGraphDestroy(graph);
    *graph = fresh;
    return true;
}

void ListGraphDestroy(ListGraph *graph) {
    if (graph == NULL) {
        return;
    }
    if (graph->initialized) {
        if (graph->adjacency != NULL) {
            for (size_t i = 0; i < graph->vertex_count; ++i) {
                free(graph->adjacency[i].items);
            }
        }
        free(graph->adjacency);
        free(graph->labels);
    }
    graph->labels = NULL;
    graph->adjacency = NULL;
    graph->vertex_count = 0;
    graph->directed = false;
    graph->initialized = false;
}

size_t ListGraphVertexCount(const ListGraph *graph) {
    return graph != NULL && graph->initialized ? graph->vertex_count : 0;
}

bool ListGraphIsDirected(const ListGraph *graph) {
    return graph != NULL && graph->initialized && graph->directed;
}

bool ListGraphLabel(const ListGraph *graph, size_t vertex, char *label) {
    if (graph == NULL || !graph->initialized || label == NULL ||
        vertex >= graph->vertex_count) {
        return false;
    }
    *label = graph->labels[vertex];
    return true;
}

size_t ListGraphNeighborCount(const ListGraph *graph, size_t vertex) {
    if (graph == NULL || !graph->initialized || vertex >= graph->vertex_count) {
        return 0;
    }
    return graph->adjacency[vertex].size;
}

bool ListGraphNeighborAt(const ListGraph *graph, size_t vertex, size_t index,
                         size_t *neighbor) {
    if (graph == NULL || !graph->initialized || neighbor == NULL ||
        vertex >= graph->vertex_count ||
        index >= graph->adjacency[vertex].size) {
        return false;
    }
    *neighbor = graph->adjacency[vertex].items[index];
    return true;
}

bool ListGraphAddEdge(ListGraph *graph, size_t from, size_t to) {
    GraphNeighborList *left;
    GraphNeighborList *right;
    if (graph == NULL || !graph->initialized || from >= graph->vertex_count ||
        to >= graph->vertex_count) {
        return false;
    }
    left = &graph->adjacency[from];
    right = &graph->adjacency[to];
    if (left->size == (size_t)-1 ||
        (!graph->directed && from != to && right->size == (size_t)-1) ||
        !neighbor_reserve(left, left->size + 1) ||
        (!graph->directed && from != to &&
         !neighbor_reserve(right, right->size + 1))) {
        return false;
    }
    left->items[left->size++] = to;
    if (!graph->directed && from != to) {
        right->items[right->size++] = from;
    }
    return true;
}

static bool weighted_allocate(WeightedGraph *graph, size_t vertex_count) {
    size_t cell_count;
    if (graph == NULL || !product_size(vertex_count, vertex_count, &cell_count) ||
        cell_count > (size_t)-1 / sizeof(*graph->weights)) {
        return false;
    }
    graph->vertex_count = vertex_count;
    graph->initialized = true;
    if (vertex_count == 0) {
        return true;
    }
    graph->weights = (int *)calloc(cell_count, sizeof(*graph->weights));
    graph->present = (unsigned char *)calloc(cell_count, sizeof(*graph->present));
    if (graph->weights == NULL || graph->present == NULL) {
        WeightedGraphDestroy(graph);
        return false;
    }
    return true;
}

bool WeightedGraphInit(WeightedGraph *graph, size_t vertex_count) {
    WeightedGraph fresh = {0};
    if (graph == NULL || !weighted_allocate(&fresh, vertex_count)) {
        WeightedGraphDestroy(&fresh);
        return false;
    }
    WeightedGraphDestroy(graph);
    *graph = fresh;
    return true;
}

void WeightedGraphDestroy(WeightedGraph *graph) {
    if (graph == NULL) {
        return;
    }
    if (graph->initialized) {
        free(graph->weights);
        free(graph->present);
    }
    graph->weights = NULL;
    graph->present = NULL;
    graph->vertex_count = 0;
    graph->initialized = false;
}

size_t WeightedGraphVertexCount(const WeightedGraph *graph) {
    return graph != NULL && graph->initialized ? graph->vertex_count : 0;
}

bool WeightedGraphAddEdge(WeightedGraph *graph, size_t from, size_t to, int weight) {
    size_t forward;
    size_t reverse;
    if (graph == NULL || !graph->initialized || from >= graph->vertex_count ||
        to >= graph->vertex_count) {
        return false;
    }
    forward = from * graph->vertex_count + to;
    reverse = to * graph->vertex_count + from;
    graph->weights[forward] = weight;
    graph->weights[reverse] = weight;
    graph->present[forward] = 1;
    graph->present[reverse] = 1;
    return true;
}

bool WeightedGraphGetEdge(const WeightedGraph *graph, size_t from, size_t to,
                          int *weight) {
    const size_t index = graph != NULL && graph->initialized &&
                         from < graph->vertex_count && to < graph->vertex_count
                             ? from * graph->vertex_count + to
                             : 0;
    if (graph == NULL || !graph->initialized || weight == NULL ||
        from >= graph->vertex_count || to >= graph->vertex_count ||
        !graph->present[index]) {
        return false;
    }
    *weight = graph->weights[index];
    return true;
}

void VertexListDestroy(VertexList *list) {
    if (list == NULL) return;
    if (list->initialized) free(list->items);
    list->items = NULL;
    list->size = 0;
    list->initialized = false;
}

void IntListDestroy(IntList *list) {
    if (list == NULL) return;
    if (list->initialized) free(list->items);
    list->items = NULL;
    list->size = 0;
    list->initialized = false;
}

void CharListDestroy(CharList *list) {
    if (list == NULL) return;
    if (list->initialized) free(list->items);
    list->items = NULL;
    list->size = 0;
    list->initialized = false;
}

void GraphPathsDestroy(GraphPaths *paths) {
    if (paths == NULL) return;
    if (paths->initialized) {
        for (size_t i = 0; i < paths->size; ++i) {
            free(paths->items[i].vertices);
        }
        free(paths->items);
    }
    paths->items = NULL;
    paths->size = 0;
    paths->capacity = 0;
    paths->initialized = false;
}

void SpanningTreeDestroy(SpanningTree *tree) {
    if (tree == NULL) return;
    if (tree->initialized) free(tree->edges);
    tree->edges = NULL;
    tree->edge_count = 0;
    tree->total_weight = 0;
    tree->complete = false;
    tree->initialized = false;
}

typedef struct {
    const MatrixGraph *matrix;
    const ListGraph *list;
    size_t count;
} GraphView;

static GraphView matrix_view(const MatrixGraph *graph) {
    GraphView view = {NULL, NULL, 0};
    if (graph != NULL && graph->initialized) {
        view.matrix = graph;
        view.count = graph->vertex_count;
    }
    return view;
}

static GraphView list_view(const ListGraph *graph) {
    GraphView view = {NULL, NULL, 0};
    if (graph != NULL && graph->initialized) {
        view.list = graph;
        view.count = graph->vertex_count;
    }
    return view;
}

static bool graph_view_valid(const GraphView *view) {
    return view != NULL && (view->matrix != NULL || view->list != NULL);
}

static bool graph_view_next(const GraphView *view, size_t vertex,
                            size_t *cursor, size_t *neighbor) {
    if (!graph_view_valid(view) || cursor == NULL || neighbor == NULL ||
        vertex >= view->count) {
        return false;
    }
    if (view->list != NULL) {
        if (*cursor >= ListGraphNeighborCount(view->list, vertex)) {
            return false;
        }
        if (!ListGraphNeighborAt(view->list, vertex, *cursor, neighbor)) {
            return false;
        }
        ++*cursor;
        return true;
    }
    while (*cursor < view->count) {
        const size_t candidate = (*cursor)++;
        if (MatrixGraphHasEdge(view->matrix, vertex, candidate)) {
            *neighbor = candidate;
            return true;
        }
    }
    return false;
}

static bool prepare_vertex_list(VertexList *list) {
    if (list == NULL) return false;
    VertexListDestroy(list);
    list->initialized = true;
    return true;
}

static bool bfs_view(const GraphView *view, bool all_components, size_t start,
                     VertexList *order) {
    unsigned char *visited = NULL;
    size_t *queue = NULL;
    if (!prepare_vertex_list(order) || !graph_view_valid(view)) {
        if (order != NULL) VertexListDestroy(order);
        return false;
    }
    if (!all_components && start >= view->count) {
        VertexListDestroy(order);
        return false;
    }
    if (view->count == 0) return all_components;
    if (view->count > (size_t)-1 / sizeof(*queue)) {
        VertexListDestroy(order);
        return false;
    }
    visited = (unsigned char *)calloc(view->count, sizeof(*visited));
    queue = (size_t *)malloc(view->count * sizeof(*queue));
    order->items = (size_t *)malloc(view->count * sizeof(*order->items));
    if (visited == NULL || queue == NULL || order->items == NULL) {
        free(visited);
        free(queue);
        VertexListDestroy(order);
        return false;
    }
    if (!all_components) {
        size_t head = 0;
        size_t tail = 0;
        visited[start] = 1;
        queue[tail++] = start;
        while (head < tail) {
            const size_t vertex = queue[head++];
            size_t cursor = 0;
            size_t neighbor;
            order->items[order->size++] = vertex;
            while (graph_view_next(view, vertex, &cursor, &neighbor)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    queue[tail++] = neighbor;
                }
            }
        }
    } else {
        for (size_t root = 0; root < view->count; ++root) {
            size_t head;
            size_t tail;
            if (visited[root]) continue;
            head = 0;
            tail = 0;
            visited[root] = 1;
            queue[tail++] = root;
            while (head < tail) {
                const size_t vertex = queue[head++];
                size_t cursor = 0;
                size_t neighbor;
                order->items[order->size++] = vertex;
                while (graph_view_next(view, vertex, &cursor, &neighbor)) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = 1;
                        queue[tail++] = neighbor;
                    }
                }
            }
        }
    }
    free(visited);
    free(queue);
    return true;
}

// 功能：以邻接表表示的图为输入，遍历所有连通分量并合并访问顺序。
// 来源：《2027数据结构》第6章 6.3.1；PDF第227页；书页第215页。
bool breadthFirstTraverseList(const ListGraph *graph, VertexList *order) {
    const GraphView view = list_view(graph);
    return bfs_view(&view, true, 0, order);
}

// 功能：以邻接矩阵表示的图为输入，按顶点编号遍历所有连通分量。
// 来源：《2027数据结构》第6章 6.3.1；PDF第227页；书页第215页。
bool breadthFirstTraverseMatrix(const MatrixGraph *graph, VertexList *order) {
    const GraphView view = matrix_view(graph);
    return bfs_view(&view, true, 0, order);
}

// 功能：从邻接表图的指定顶点执行一次广度优先搜索。
// 来源：《2027数据结构》第6章 6.3.1；PDF第227页；书页第215页。
bool breadthFirstFromList(const ListGraph *graph, size_t start, VertexList *order) {
    const GraphView view = list_view(graph);
    return bfs_view(&view, false, start, order);
}

// 功能：从邻接矩阵图的指定顶点执行一次广度优先搜索。
// 来源：《2027数据结构》第6章 6.3.1；PDF第227页；书页第215页。
bool breadthFirstFromMatrix(const MatrixGraph *graph, size_t start, VertexList *order) {
    const GraphView view = matrix_view(graph);
    return bfs_view(&view, false, start, order);
}

// 功能：借助队列求无权图从源点到各顶点的最短路径边数。
// 来源：《2027数据结构》第6章 6.3.1；PDF第228页；书页第216页。
bool breadthFirstShortestDistances(const ListGraph *graph, size_t start,
                                   IntList *distances) {
    size_t *queue = NULL;
    const size_t count = ListGraphVertexCount(graph);
    if (distances == NULL) return false;
    IntListDestroy(distances);
    distances->initialized = true;
    if (graph == NULL || !graph->initialized || start >= count ||
        count > (size_t)INT_MAX ||
        count > (size_t)-1 / sizeof(*distances->items) ||
        count > (size_t)-1 / sizeof(*queue)) {
        IntListDestroy(distances);
        return false;
    }
    distances->items = (int *)malloc(count * sizeof(*distances->items));
    queue = (size_t *)malloc(count * sizeof(*queue));
    if (distances->items == NULL || queue == NULL) {
        free(queue);
        IntListDestroy(distances);
        return false;
    }
    distances->size = count;
    for (size_t i = 0; i < count; ++i) distances->items[i] = -1;
    distances->items[start] = 0;
    size_t head = 0;
    size_t tail = 0;
    queue[tail++] = start;
    while (head < tail) {
        const size_t vertex = queue[head++];
        const GraphNeighborList *neighbors = &graph->adjacency[vertex];
        for (size_t i = 0; i < neighbors->size; ++i) {
            const size_t next = neighbors->items[i];
            if (distances->items[next] == -1) {
                distances->items[next] = distances->items[vertex] + 1;
                queue[tail++] = next;
            }
        }
    }
    free(queue);
    return true;
}

typedef struct {
    size_t vertex;
    size_t cursor;
} DfsFrame;

static bool dfs_traverse_view(const GraphView *view, VertexList *order) {
    unsigned char *visited = NULL;
    DfsFrame *frames = NULL;
    size_t depth = 0;
    if (!prepare_vertex_list(order) || !graph_view_valid(view)) {
        if (order != NULL) VertexListDestroy(order);
        return false;
    }
    if (view->count == 0) return true;
    if (view->count > (size_t)-1 / sizeof(*frames) ||
        view->count > (size_t)-1 / sizeof(*order->items)) {
        VertexListDestroy(order);
        return false;
    }
    visited = (unsigned char *)calloc(view->count, sizeof(*visited));
    frames = (DfsFrame *)malloc(view->count * sizeof(*frames));
    order->items = (size_t *)malloc(view->count * sizeof(*order->items));
    if (visited == NULL || frames == NULL || order->items == NULL) {
        free(visited);
        free(frames);
        VertexListDestroy(order);
        return false;
    }
    for (size_t root = 0; root < view->count; ++root) {
        if (visited[root]) continue;
        visited[root] = 1;
        order->items[order->size++] = root;
        frames[depth++] = (DfsFrame){root, 0};
        while (depth > 0) {
            DfsFrame *frame = &frames[depth - 1];
            size_t next;
            if (graph_view_next(view, frame->vertex, &frame->cursor, &next)) {
                if (!visited[next]) {
                    visited[next] = 1;
                    order->items[order->size++] = next;
                    frames[depth++] = (DfsFrame){next, 0};
                }
            } else {
                --depth;
            }
        }
    }
    free(visited);
    free(frames);
    return true;
}

// 功能：从每个尚未访问顶点出发，按递归 DFS 的先序顺序遍历邻接表图。
// 来源：《2027数据结构》第6章 6.3.2；PDF第229页；书页第217页。
bool depthFirstTraverseList(const ListGraph *graph, VertexList *order) {
    const GraphView view = list_view(graph);
    return dfs_traverse_view(&view, order);
}

// 功能：从每个尚未访问顶点出发，按递归 DFS 的先序顺序遍历邻接矩阵图。
// 来源：《2027数据结构》第6章 6.3.2；PDF第229页；书页第217页。
bool depthFirstTraverseMatrix(const MatrixGraph *graph, VertexList *order) {
    const GraphView view = matrix_view(graph);
    return dfs_traverse_view(&view, order);
}

// 功能：以栈保存当前入度为零的顶点，执行邻接表图拓扑排序。
// 来源：《2027数据结构》第6章 6.4.4；PDF第245–246页；书页第233–234页。
bool topologicalSort(const ListGraph *graph, VertexList *order) {
    size_t *indegree = NULL;
    size_t *stack = NULL;
    size_t count;
    size_t stack_size = 0;
    if (order == NULL) return false;
    VertexListDestroy(order);
    order->initialized = true;
    if (graph == NULL || !graph->initialized) {
        VertexListDestroy(order);
        return false;
    }
    count = graph->vertex_count;
    if (count == 0) return true;
    if (count > (size_t)-1 / sizeof(*indegree) ||
        count > (size_t)-1 / sizeof(*order->items)) {
        VertexListDestroy(order);
        return false;
    }
    indegree = (size_t *)calloc(count, sizeof(*indegree));
    stack = (size_t *)malloc(count * sizeof(*stack));
    order->items = (size_t *)malloc(count * sizeof(*order->items));
    if (indegree == NULL || stack == NULL || order->items == NULL) {
        free(indegree);
        free(stack);
        VertexListDestroy(order);
        return false;
    }
    for (size_t from = 0; from < count; ++from) {
        const GraphNeighborList *neighbors = &graph->adjacency[from];
        for (size_t i = 0; i < neighbors->size; ++i) {
            const size_t to = neighbors->items[i];
            if (to >= count || indegree[to] == (size_t)-1) {
                free(indegree);
                free(stack);
                VertexListDestroy(order);
                return false;
            }
            ++indegree[to];
        }
    }
    for (size_t vertex = 0; vertex < count; ++vertex) {
        if (indegree[vertex] == 0) stack[stack_size++] = vertex;
    }
    while (stack_size > 0) {
        const size_t vertex = stack[--stack_size];
        order->items[order->size++] = vertex;
        const GraphNeighborList *neighbors = &graph->adjacency[vertex];
        for (size_t i = 0; i < neighbors->size; ++i) {
            const size_t to = neighbors->items[i];
            if (--indegree[to] == 0) stack[stack_size++] = to;
        }
    }
    free(indegree);
    free(stack);
    if (order->size != count) {
        VertexListDestroy(order);
        return false;
    }
    return true;
}

static bool prepare_tree(SpanningTree *tree) {
    if (tree == NULL) return false;
    SpanningTreeDestroy(tree);
    tree->initialized = true;
    return true;
}

static bool add_weight_to_total(SpanningTree *tree, int weight) {
    if ((weight > 0 && tree->total_weight > LLONG_MAX - weight) ||
        (weight < 0 && tree->total_weight < LLONG_MIN - weight)) {
        return false;
    }
    tree->total_weight += weight;
    return true;
}

static int compare_edges(const void *left_pointer, const void *right_pointer) {
    const WeightedEdge *left = (const WeightedEdge *)left_pointer;
    const WeightedEdge *right = (const WeightedEdge *)right_pointer;
    if (left->weight < right->weight) return -1;
    if (left->weight > right->weight) return 1;
    if (left->from < right->from) return -1;
    if (left->from > right->from) return 1;
    if (left->to < right->to) return -1;
    if (left->to > right->to) return 1;
    return 0;
}

typedef struct {
    size_t *parent;
    unsigned char *rank;
    size_t count;
} DisjointSet;

static bool disjoint_set_init(DisjointSet *set, size_t count) {
    if (set == NULL || count > (size_t)-1 / sizeof(*set->parent)) return false;
    set->parent = NULL;
    set->rank = NULL;
    set->count = count;
    if (count == 0) return true;
    set->parent = (size_t *)malloc(count * sizeof(*set->parent));
    set->rank = (unsigned char *)calloc(count, sizeof(*set->rank));
    if (set->parent == NULL || set->rank == NULL) {
        free(set->parent);
        free(set->rank);
        set->parent = NULL;
        set->rank = NULL;
        return false;
    }
    for (size_t i = 0; i < count; ++i) set->parent[i] = i;
    return true;
}

static void disjoint_set_destroy(DisjointSet *set) {
    if (set != NULL) {
        free(set->parent);
        free(set->rank);
        set->parent = NULL;
        set->rank = NULL;
        set->count = 0;
    }
}

static size_t disjoint_set_find(DisjointSet *set, size_t value) {
    size_t root = value;
    while (set->parent[root] != root) root = set->parent[root];
    while (set->parent[value] != value) {
        const size_t parent = set->parent[value];
        set->parent[value] = root;
        value = parent;
    }
    return root;
}

static bool disjoint_set_unite(DisjointSet *set, size_t left, size_t right) {
    left = disjoint_set_find(set, left);
    right = disjoint_set_find(set, right);
    if (left == right) return false;
    if (set->rank[left] < set->rank[right]) {
        const size_t temporary = left;
        left = right;
        right = temporary;
    }
    set->parent[right] = left;
    if (set->rank[left] == set->rank[right] && set->rank[left] < UCHAR_MAX) {
        ++set->rank[left];
    }
    return true;
}

static bool kruskal_mst(const WeightedGraph *graph, SpanningTree *tree) {
    size_t edge_capacity;
    size_t edge_count = 0;
    WeightedEdge *edges = NULL;
    DisjointSet set = {NULL, NULL, 0};
    const size_t count = graph->vertex_count;
    if (count < 2) {
        tree->complete = true;
        return true;
    }
    if (count > (size_t)-1 / (count - 1)) return false;
    edge_capacity = count * (count - 1) / 2;
    if (edge_capacity > (size_t)-1 / sizeof(*edges) ||
        count - 1 > (size_t)-1 / sizeof(*tree->edges)) {
        return false;
    }
    edges = (WeightedEdge *)malloc(edge_capacity * sizeof(*edges));
    tree->edges = (WeightedEdge *)malloc((count - 1) * sizeof(*tree->edges));
    if (edges == NULL || tree->edges == NULL ||
        !disjoint_set_init(&set, count)) {
        free(edges);
        disjoint_set_destroy(&set);
        SpanningTreeDestroy(tree);
        return false;
    }
    for (size_t from = 0; from < count; ++from) {
        for (size_t to = from + 1; to < count; ++to) {
            const size_t index = from * count + to;
            if (graph->present[index]) {
                edges[edge_count++] = (WeightedEdge){from, to, graph->weights[index]};
            }
        }
    }
    qsort(edges, edge_count, sizeof(*edges), compare_edges);
    for (size_t i = 0; i < edge_count; ++i) {
        if (disjoint_set_unite(&set, edges[i].from, edges[i].to)) {
            if (!add_weight_to_total(tree, edges[i].weight)) {
                free(edges);
                disjoint_set_destroy(&set);
                SpanningTreeDestroy(tree);
                return false;
            }
            tree->edges[tree->edge_count++] = edges[i];
            if (tree->edge_count + 1 == count) break;
        }
    }
    tree->complete = tree->edge_count + 1 == count;
    free(edges);
    disjoint_set_destroy(&set);
    return true;
}

// 功能：按通用选边框架构造最小生成树，按权值和端点编号稳定地处理并列边。
// 来源：《2027数据结构》第6章 6.4.1；PDF第238页；书页第226页。
bool genericMstFramework(const WeightedGraph *graph, SpanningTree *tree) {
    if (!prepare_tree(tree) || graph == NULL || !graph->initialized) {
        if (tree != NULL) SpanningTreeDestroy(tree);
        return false;
    }
    return kruskal_mst(graph, tree);
}

// 功能：从指定起点逐步扩展当前树，选择跨越割的最小权值边。
// 来源：《2027数据结构》第6章 6.4.1；PDF第239页；书页第227页。
bool primMinimumSpanningTree(const WeightedGraph *graph, size_t start,
                             SpanningTree *tree) {
    unsigned char *in_tree = NULL;
    const size_t count = graph != NULL && graph->initialized
                             ? graph->vertex_count
                             : 0;
    if (!prepare_tree(tree) || graph == NULL || !graph->initialized) {
        if (tree != NULL) SpanningTreeDestroy(tree);
        return false;
    }
    if (count == 0) {
        tree->complete = true;
        return true;
    }
    if (start >= count) {
        SpanningTreeDestroy(tree);
        return false;
    }
    if (count == 1) {
        tree->complete = true;
        return true;
    }
    if (count - 1 > (size_t)-1 / sizeof(*tree->edges)) {
        SpanningTreeDestroy(tree);
        return false;
    }
    if (count > (size_t)-1 / sizeof(*in_tree)) {
        SpanningTreeDestroy(tree);
        return false;
    }
    in_tree = (unsigned char *)calloc(count, sizeof(*in_tree));
    tree->edges = (WeightedEdge *)malloc((count - 1) * sizeof(*tree->edges));
    if (in_tree == NULL || tree->edges == NULL) {
        free(in_tree);
        SpanningTreeDestroy(tree);
        return false;
    }
    in_tree[start] = 1;
    while (tree->edge_count + 1 < count) {
        bool found = false;
        WeightedEdge best = {0, 0, 0};
        for (size_t from = 0; from < count; ++from) {
            if (!in_tree[from]) continue;
            for (size_t to = 0; to < count; ++to) {
                const size_t index = from * count + to;
                if (in_tree[to] || !graph->present[index]) continue;
                const WeightedEdge candidate = {from, to, graph->weights[index]};
                if (!found || compare_edges(&candidate, &best) < 0) {
                    best = candidate;
                    found = true;
                }
            }
        }
        if (!found) break;
        if (!add_weight_to_total(tree, best.weight)) {
            free(in_tree);
            SpanningTreeDestroy(tree);
            return false;
        }
        tree->edges[tree->edge_count++] = best;
        in_tree[best.to] = 1;
    }
    tree->complete = tree->edge_count + 1 == count;
    free(in_tree);
    return true;
}

// 功能：按权值递增选边，使用并查集排除成环边以构造最小生成树。
// 来源：《2027数据结构》第6章 6.4.1；PDF第240页；书页第228页。
bool kruskalMinimumSpanningTree(const WeightedGraph *graph, SpanningTree *tree) {
    return genericMstFramework(graph, tree);
}

// 功能：在邻接矩阵行中返回顶点 after 之后的下一个相邻顶点。
// 来源：《2027数据结构》第6章 归纳总结；PDF第274页；书页第262页。
int nextNeighborMatrix(const MatrixGraph *graph, int vertex, int after) {
    const size_t count = MatrixGraphVertexCount(graph);
    if (vertex < 0 || after < 0 || (size_t)vertex >= count ||
        (size_t)after >= count) {
        return -1;
    }
    for (size_t next = (size_t)after + 1; next < count; ++next) {
        if (MatrixGraphHasEdge(graph, (size_t)vertex, next) && next <= INT_MAX) {
            return (int)next;
        }
    }
    return -1;
}

// 功能：在邻接表链中找到顶点 after 并返回其后的下一个邻接点。
// 来源：《2027数据结构》第6章 归纳总结；PDF第274页；书页第262页。
int nextNeighborList(const ListGraph *graph, int vertex, int after) {
    size_t count = ListGraphVertexCount(graph);
    size_t neighbor;
    if (vertex < 0 || after < 0 || (size_t)vertex >= count ||
        (size_t)after >= count) {
        return -1;
    }
    const size_t neighbor_count = ListGraphNeighborCount(graph, (size_t)vertex);
    for (size_t i = 0; i < neighbor_count; ++i) {
        if (ListGraphNeighborAt(graph, (size_t)vertex, i, &neighbor) &&
            neighbor == (size_t)after && i + 1 < neighbor_count &&
            ListGraphNeighborAt(graph, (size_t)vertex, i + 1, &neighbor) &&
            neighbor <= INT_MAX) {
            return (int)neighbor;
        }
    }
    return -1;
}
