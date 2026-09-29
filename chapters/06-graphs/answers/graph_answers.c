#include "graph_answers.h"

#include <limits.h>
#include <stdlib.h>

static bool graph_paths_append(GraphPaths *paths, const size_t *vertices,
                               size_t length) {
    size_t *copy;
    size_t needed;
    if (length > (size_t)-1 / sizeof(*copy)) {
        return false;
    }
    copy = (size_t *)malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return false;
    }
    for (size_t i = 0; i < length; ++i) copy[i] = vertices[i];
    if (paths->size == (size_t)-1) {
        free(copy);
        return false;
    }
    needed = paths->size + 1;
    if (paths->size == paths->capacity) {
        size_t capacity = paths->capacity == 0 ? 4 : paths->capacity;
        GraphPath *items;
        while (capacity < needed) {
            if (capacity > (size_t)-1 / 2) {
                capacity = needed;
                break;
            }
            capacity *= 2;
        }
        if (capacity > (size_t)-1 / sizeof(*items)) {
            free(copy);
            return false;
        }
        items = (GraphPath *)realloc(paths->items, capacity * sizeof(*items));
        if (items == NULL) {
            free(copy);
            return false;
        }
        paths->items = items;
        paths->capacity = capacity;
    }
    paths->items[paths->size++] = (GraphPath){copy, length};
    return true;
}

// 功能：将邻接表逐边转换为邻接矩阵，保留顶点标签和有向/无向属性。
// 来源：《2027数据结构》第6章 6.2.2 试题05答案；PDF第225页；书页第213页。
bool convertAdjacencyListToMatrix(const ListGraph *graph, MatrixGraph *matrix) {
    char *labels = NULL;
    const size_t count = ListGraphVertexCount(graph);
    if (graph == NULL || !graph->initialized || matrix == NULL ||
        count > (size_t)-1 / sizeof(*labels)) {
        return false;
    }
    if (count != 0) {
        labels = (char *)malloc(count * sizeof(*labels));
        if (labels == NULL) return false;
        for (size_t vertex = 0; vertex < count; ++vertex) {
            if (!ListGraphLabel(graph, vertex, &labels[vertex])) {
                free(labels);
                return false;
            }
        }
    }
    if (!MatrixGraphInitWithLabels(matrix, labels, count, graph->directed)) {
        free(labels);
        return false;
    }
    free(labels);
    for (size_t from = 0; from < count; ++from) {
        const size_t neighbor_count = ListGraphNeighborCount(graph, from);
        for (size_t i = 0; i < neighbor_count; ++i) {
            size_t to;
            if (!ListGraphNeighborAt(graph, from, i, &to) ||
                !MatrixGraphAddEdge(matrix, from, to, 1)) {
                MatrixGraphDestroy(matrix);
                return false;
            }
        }
    }
    return true;
}

// 功能：按各顶点度数的奇偶性判断连通无向图是否有欧拉回路或欧拉通路。
// 来源：《2027数据结构》第6章 6.2.4 试题07答案；PDF第225页；书页第213页。
bool hasEulerTrailByDegreeParity(const MatrixGraph *graph) {
    const size_t count = MatrixGraphVertexCount(graph);
    unsigned char *visited = NULL;
    size_t *pending = NULL;
    size_t pending_size = 0;
    size_t odd_degrees = 0;
    if (graph == NULL || !graph->initialized || graph->directed || count == 0 ||
        count > (size_t)-1 / sizeof(*pending)) {
        return false;
    }
    visited = (unsigned char *)calloc(count, sizeof(*visited));
    pending = (size_t *)malloc(count * sizeof(*pending));
    if (visited == NULL || pending == NULL) {
        free(visited);
        free(pending);
        return false;
    }
    visited[0] = 1;
    pending[pending_size++] = 0;
    while (pending_size > 0) {
        const size_t vertex = pending[--pending_size];
        for (size_t next = 0; next < count; ++next) {
            if (MatrixGraphHasEdge(graph, vertex, next) && !visited[next]) {
                visited[next] = 1;
                pending[pending_size++] = next;
            }
        }
    }
    for (size_t vertex = 0; vertex < count; ++vertex) {
        size_t degree = 0;
        for (size_t neighbor = 0; neighbor < count; ++neighbor) {
            if (MatrixGraphHasEdge(graph, vertex, neighbor)) {
                degree += vertex == neighbor ? 2 : 1;
            }
        }
        if (degree % 2 != 0) ++odd_degrees;
        // 题干将输入限定为连通图；这里对一般调用者验证该前提，包含孤立顶点的多点图拒绝。
        if (!visited[vertex]) {
            free(visited);
            free(pending);
            return false;
        }
    }
    free(visited);
    free(pending);
    return odd_degrees == 0 || odd_degrees == 2;
}

// 功能：在有向图的邻接矩阵中找出出度大于入度的顶点并返回顶点标签。
// 来源：《2027数据结构》第6章 6.2.4 试题08答案；PDF第226页；书页第214页。
bool verticesWithMoreOutgoingThanIncoming(const MatrixGraph *graph, CharList *labels) {
    const size_t count = MatrixGraphVertexCount(graph);
    if (labels == NULL) return false;
    CharListDestroy(labels);
    labels->initialized = true;
    if (graph == NULL || !graph->initialized) {
        CharListDestroy(labels);
        return false;
    }
    if (count == 0) return true;
    labels->items = (char *)malloc(count * sizeof(*labels->items));
    if (labels->items == NULL) {
        CharListDestroy(labels);
        return false;
    }
    for (size_t vertex = 0; vertex < count; ++vertex) {
        size_t outgoing = 0;
        size_t incoming = 0;
        char label;
        for (size_t other = 0; other < count; ++other) {
            if (MatrixGraphHasEdge(graph, vertex, other)) ++outgoing;
            if (MatrixGraphHasEdge(graph, other, vertex)) ++incoming;
        }
        if (outgoing > incoming && MatrixGraphLabel(graph, vertex, &label)) {
            labels->items[labels->size++] = label;
        }
    }
    return true;
}

// 功能：用一次深度优先遍历统计可达顶点数和邻接表边数，据此判断无向图是否为树。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题03答案；PDF第236页；书页第224页。
bool isUndirectedTree(const ListGraph *graph) {
    VertexList order = {0};
    size_t adjacency_entries = 0;
    const size_t count = ListGraphVertexCount(graph);
    bool is_tree;
    if (graph == NULL || !graph->initialized || graph->directed || count == 0 ||
        !depthFirstTraverseList(graph, &order)) {
        VertexListDestroy(&order);
        return false;
    }
    for (size_t vertex = 0; vertex < count; ++vertex) {
        const size_t degree = ListGraphNeighborCount(graph, vertex);
        if (adjacency_entries > (size_t)-1 - degree) {
            VertexListDestroy(&order);
            return false;
        }
        adjacency_entries += degree;
    }
    is_tree = order.size == count && count - 1 <= (size_t)-1 / 2 &&
              adjacency_entries == 2 * (count - 1);
    VertexListDestroy(&order);
    return is_tree;
}

// 功能：用深度优先搜索判断有向或无向图中两顶点间是否存在路径。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题04答案；PDF第236页；书页第224页。
bool depthFirstReachable(const ListGraph *graph, size_t from, size_t to) {
    unsigned char *visited = NULL;
    size_t *stack = NULL;
    size_t stack_size = 0;
    const size_t count = ListGraphVertexCount(graph);
    if (graph == NULL || !graph->initialized || from >= count || to >= count ||
        count > (size_t)-1 / sizeof(*stack)) {
        return false;
    }
    if (from == to) return true;
    visited = (unsigned char *)calloc(count, sizeof(*visited));
    stack = (size_t *)malloc(count * sizeof(*stack));
    if (visited == NULL || stack == NULL) {
        free(visited);
        free(stack);
        return false;
    }
    visited[from] = 1;
    stack[stack_size++] = from;
    while (stack_size > 0) {
        const size_t vertex = stack[--stack_size];
        const size_t neighbor_count = ListGraphNeighborCount(graph, vertex);
        for (size_t i = 0; i < neighbor_count; ++i) {
            size_t next;
            if (!ListGraphNeighborAt(graph, vertex, i, &next)) continue;
            if (next == to) {
                free(visited);
                free(stack);
                return true;
            }
            if (next < count && !visited[next]) {
                visited[next] = 1;
                stack[stack_size++] = next;
            }
        }
    }
    free(visited);
    free(stack);
    return false;
}

// 功能：用广度优先搜索判断图中两顶点间是否存在路径。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题04答案；PDF第237页；书页第225页。
bool breadthFirstReachable(const ListGraph *graph, size_t from, size_t to) {
    VertexList order = {0};
    bool found = false;
    if (!breadthFirstFromList(graph, from, &order)) return false;
    for (size_t i = 0; i < order.size; ++i) {
        if (order.items[i] == to) {
            found = true;
            break;
        }
    }
    VertexListDestroy(&order);
    return found;
}

// 功能：用回溯深度优先搜索输出两顶点之间的所有简单路径。
// 来源：《2027数据结构》第6章 6.3.4 综合应用题05答案；PDF第237页；书页第225页。
bool findAllSimplePaths(const ListGraph *graph, size_t from, size_t to,
                        GraphPaths *paths) {
    typedef struct {
        size_t vertex;
        size_t cursor;
    } PathFrame;
    unsigned char *visited = NULL;
    size_t *path = NULL;
    PathFrame *frames = NULL;
    size_t depth = 0;
    size_t path_length = 0;
    const size_t count = ListGraphVertexCount(graph);
    if (paths == NULL) return false;
    GraphPathsDestroy(paths);
    paths->initialized = true;
    if (graph == NULL || !graph->initialized || from >= count || to >= count ||
        count > (size_t)-1 / sizeof(*path) ||
        count > (size_t)-1 / sizeof(*frames)) {
        GraphPathsDestroy(paths);
        return false;
    }
    visited = (unsigned char *)calloc(count, sizeof(*visited));
    path = (size_t *)malloc(count * sizeof(*path));
    frames = (PathFrame *)malloc(count * sizeof(*frames));
    if (visited == NULL || path == NULL || frames == NULL) {
        free(visited);
        free(path);
        free(frames);
        GraphPathsDestroy(paths);
        return false;
    }
    visited[from] = 1;
    path[path_length++] = from;
    frames[depth++] = (PathFrame){from, 0};
    while (depth > 0) {
        PathFrame *frame = &frames[depth - 1];
        if (frame->vertex == to) {
            if (!graph_paths_append(paths, path, path_length)) {
                free(visited);
                free(path);
                free(frames);
                GraphPathsDestroy(paths);
                return false;
            }
            visited[frame->vertex] = 0;
            --depth;
            --path_length;
            continue;
        }
        const size_t neighbor_count = ListGraphNeighborCount(graph, frame->vertex);
        bool descended = false;
        while (frame->cursor < neighbor_count) {
            size_t next;
            const size_t index = frame->cursor++;
            if (!ListGraphNeighborAt(graph, frame->vertex, index, &next) ||
                next >= count || visited[next]) {
                continue;
            }
            visited[next] = 1;
            path[path_length++] = next;
            frames[depth++] = (PathFrame){next, 0};
            descended = true;
            break;
        }
        if (!descended && frame->cursor >= neighbor_count) {
            visited[frame->vertex] = 0;
            --depth;
            --path_length;
        }
    }
    free(visited);
    free(path);
    free(frames);
    return true;
}

// 功能：根据 DFS 完成时间递减顺序生成有向无环图的拓扑序列。
// 来源：《2027数据结构》第6章 6.4.4 试题07答案；PDF第269页；书页第257页。
bool depthFirstFinishOrder(const ListGraph *graph, VertexList *order) {
    typedef struct {
        size_t vertex;
        size_t cursor;
    } FinishFrame;
    unsigned char *visited = NULL;
    FinishFrame *frames = NULL;
    size_t depth = 0;
    const size_t count = ListGraphVertexCount(graph);
    if (order == NULL) return false;
    VertexListDestroy(order);
    order->initialized = true;
    if (graph == NULL || !graph->initialized ||
        count > (size_t)-1 / sizeof(*frames) ||
        count > (size_t)-1 / sizeof(*order->items)) {
        VertexListDestroy(order);
        return false;
    }
    if (count == 0) return true;
    visited = (unsigned char *)calloc(count, sizeof(*visited));
    frames = (FinishFrame *)malloc(count * sizeof(*frames));
    order->items = (size_t *)malloc(count * sizeof(*order->items));
    if (visited == NULL || frames == NULL || order->items == NULL) {
        free(visited);
        free(frames);
        VertexListDestroy(order);
        return false;
    }
    for (size_t root = 0; root < count; ++root) {
        if (visited[root]) continue;
        visited[root] = 1;
        frames[depth++] = (FinishFrame){root, 0};
        while (depth > 0) {
            FinishFrame *frame = &frames[depth - 1];
            const size_t neighbor_count = ListGraphNeighborCount(graph, frame->vertex);
            bool descended = false;
            while (frame->cursor < neighbor_count) {
                size_t next;
                const size_t index = frame->cursor++;
                if (!ListGraphNeighborAt(graph, frame->vertex, index, &next) ||
                    next >= count || visited[next]) {
                    continue;
                }
                visited[next] = 1;
                frames[depth++] = (FinishFrame){next, 0};
                descended = true;
                break;
            }
            if (!descended && frame->cursor >= neighbor_count) {
                order->items[order->size++] = frame->vertex;
                --depth;
            }
        }
    }
    {
        size_t left = 0;
        size_t right = order->size;
        while (left < right) {
            size_t temporary;
            --right;
            if (left >= right) break;
            temporary = order->items[left];
            order->items[left] = order->items[right];
            order->items[right] = temporary;
            ++left;
        }
    }
    free(visited);
    free(frames);
    return true;
}

// 功能：判断邻接矩阵表示的有向图是否只有唯一的拓扑序列。
// 来源：《2027数据结构》第6章 6.4.4 试题13答案；PDF第272–273页；书页第260–261页。
bool hasUniqueTopologicalOrder(const MatrixGraph *graph) {
    size_t *indegree = NULL;
    size_t *available = NULL;
    size_t available_size = 0;
    size_t processed = 0;
    const size_t count = MatrixGraphVertexCount(graph);
    if (graph == NULL || !graph->initialized ||
        count > (size_t)-1 / sizeof(*indegree)) {
        return false;
    }
    if (count == 0) return true;
    indegree = (size_t *)calloc(count, sizeof(*indegree));
    available = (size_t *)malloc(count * sizeof(*available));
    if (indegree == NULL || available == NULL) {
        free(indegree);
        free(available);
        return false;
    }
    for (size_t from = 0; from < count; ++from) {
        for (size_t to = 0; to < count; ++to) {
            if (MatrixGraphHasEdge(graph, from, to)) {
                if (indegree[to] == (size_t)-1) {
                    free(indegree);
                    free(available);
                    return false;
                }
                ++indegree[to];
            }
        }
    }
    for (size_t vertex = 0; vertex < count; ++vertex) {
        if (indegree[vertex] == 0) available[available_size++] = vertex;
    }
    while (available_size > 0) {
        if (available_size != 1) {
            free(indegree);
            free(available);
            return false;
        }
        const size_t vertex = available[--available_size];
        ++processed;
        for (size_t to = 0; to < count; ++to) {
            if (MatrixGraphHasEdge(graph, vertex, to) && --indegree[to] == 0) {
                available[available_size++] = to;
            }
        }
    }
    free(indegree);
    free(available);
    return processed == count;
}
