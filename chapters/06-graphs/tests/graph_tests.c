#include "graph_algorithms.h"
#include "graph_answers.h"
#include "graph_question_types.h"
#include "graph_source_types.h"
#include "routing_types.h"
#include "test_harness.h"

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static bool vertex_list_equals(const VertexList *actual,
                               const size_t *expected, size_t count) {
    if (actual == NULL || actual->size != count) return false;
    for (size_t i = 0; i < count; ++i) {
        if (actual->items[i] != expected[i]) return false;
    }
    return true;
}

static bool int_list_equals(const IntList *actual,
                            const int *expected, size_t count) {
    if (actual == NULL || actual->size != count) return false;
    for (size_t i = 0; i < count; ++i) {
        if (actual->items[i] != expected[i]) return false;
    }
    return true;
}

static bool char_list_equals(const CharList *actual,
                             const char *expected, size_t count) {
    if (actual == NULL || actual->size != count) return false;
    for (size_t i = 0; i < count; ++i) {
        if (actual->items[i] != expected[i]) return false;
    }
    return true;
}

static bool graph_path_equals(const GraphPath *actual,
                              const size_t *expected, size_t count) {
    if (actual == NULL || actual->length != count) return false;
    for (size_t i = 0; i < count; ++i) {
        if (actual->vertices[i] != expected[i]) return false;
    }
    return true;
}

DS_TEST_FUNCTION(graph_conversion) {
    const char labels[] = {'A', 'B', 'C'};
    ListGraph graph = {0};
    MatrixGraph matrix = {0};
    char label = '\0';

    DS_CHECK(ListGraphInitWithLabels(&graph, labels, 3, true));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 1));
    DS_CHECK(ListGraphAddEdge(&graph, 2, 0));
    DS_CHECK(convertAdjacencyListToMatrix(&graph, &matrix));
    DS_CHECK(MatrixGraphVertexCount(&matrix) == 3);
    DS_CHECK(MatrixGraphLabel(&matrix, 0, &label) && label == 'A');
    DS_CHECK(MatrixGraphHasEdge(&matrix, 0, 1));
    DS_CHECK(MatrixGraphHasEdge(&matrix, 2, 0));
    DS_CHECK(!MatrixGraphHasEdge(&matrix, 1, 0));

    MatrixGraphDestroy(&matrix);
    ListGraphDestroy(&graph);
}

DS_TEST_FUNCTION(graph_conversion_boundaries) {
    ListGraph empty = {0};
    MatrixGraph matrix = {0};
    ListGraph undirected = {0};
    const char labels[] = {'x', 'y'};

    DS_CHECK(ListGraphInit(&empty, 0, true));
    DS_CHECK(convertAdjacencyListToMatrix(&empty, &matrix));
    DS_CHECK(MatrixGraphVertexCount(&matrix) == 0);
    MatrixGraphDestroy(&matrix);

    DS_CHECK(ListGraphInitWithLabels(&undirected, labels, 2, false));
    DS_CHECK(ListGraphAddEdge(&undirected, 0, 1));
    DS_CHECK(convertAdjacencyListToMatrix(&undirected, &matrix));
    DS_CHECK(!MatrixGraphIsDirected(&matrix));
    DS_CHECK(MatrixGraphHasEdge(&matrix, 0, 1));
    DS_CHECK(MatrixGraphHasEdge(&matrix, 1, 0));

    MatrixGraphDestroy(&matrix);
    ListGraphDestroy(&undirected);
    ListGraphDestroy(&empty);
}

DS_TEST_FUNCTION(euler_trail_degree) {
    MatrixGraph path = {0};
    MatrixGraph cycle = {0};
    MatrixGraph star = {0};
    MatrixGraph with_isolate = {0};
    MatrixGraph empty = {0};
    MatrixGraph singleton = {0};
    MatrixGraph directed = {0};

    DS_CHECK(MatrixGraphInit(&path, 4, false));
    DS_CHECK(MatrixGraphAddEdge(&path, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&path, 1, 2, 1));
    DS_CHECK(MatrixGraphAddEdge(&path, 2, 3, 1));
    DS_CHECK(hasEulerTrailByDegreeParity(&path));

    DS_CHECK(MatrixGraphInit(&cycle, 3, false));
    DS_CHECK(MatrixGraphAddEdge(&cycle, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&cycle, 1, 2, 1));
    DS_CHECK(MatrixGraphAddEdge(&cycle, 2, 0, 1));
    DS_CHECK(hasEulerTrailByDegreeParity(&cycle));

    DS_CHECK(MatrixGraphInit(&star, 5, false));
    for (size_t vertex = 1; vertex < 5; ++vertex) {
        DS_CHECK(MatrixGraphAddEdge(&star, 0, vertex, 1));
    }
    DS_CHECK(!hasEulerTrailByDegreeParity(&star));

    DS_CHECK(MatrixGraphInit(&with_isolate, 4, false));
    DS_CHECK(MatrixGraphAddEdge(&with_isolate, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&with_isolate, 1, 2, 1));
    DS_CHECK(!hasEulerTrailByDegreeParity(&with_isolate));

    DS_CHECK(MatrixGraphInit(&empty, 0, false));
    DS_CHECK(!hasEulerTrailByDegreeParity(&empty));
    DS_CHECK(MatrixGraphInit(&singleton, 1, false));
    DS_CHECK(hasEulerTrailByDegreeParity(&singleton));
    DS_CHECK(MatrixGraphAddEdge(&singleton, 0, 0, 1));
    DS_CHECK(hasEulerTrailByDegreeParity(&singleton));
    DS_CHECK(MatrixGraphInit(&directed, 2, true));
    DS_CHECK(!hasEulerTrailByDegreeParity(&directed));

    MatrixGraphDestroy(&directed);
    MatrixGraphDestroy(&singleton);
    MatrixGraphDestroy(&empty);
    MatrixGraphDestroy(&with_isolate);
    MatrixGraphDestroy(&star);
    MatrixGraphDestroy(&cycle);
    MatrixGraphDestroy(&path);
}

DS_TEST_FUNCTION(vertices_by_degree) {
    const char labels[] = {'a', 'b', 'c'};
    const char expected[] = {'a'};
    MatrixGraph graph = {0};
    MatrixGraph empty = {0};
    CharList selected = {0};

    DS_CHECK(MatrixGraphInitWithLabels(&graph, labels, 3, true));
    DS_CHECK(MatrixGraphAddEdge(&graph, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&graph, 0, 2, 1));
    DS_CHECK(MatrixGraphAddEdge(&graph, 1, 2, 1));
    DS_CHECK(verticesWithMoreOutgoingThanIncoming(&graph, &selected));
    DS_CHECK(char_list_equals(&selected, expected, 1));

    DS_CHECK(MatrixGraphInit(&empty, 0, true));
    DS_CHECK(verticesWithMoreOutgoingThanIncoming(&empty, &selected));
    DS_CHECK(selected.size == 0);

    CharListDestroy(&selected);
    MatrixGraphDestroy(&empty);
    MatrixGraphDestroy(&graph);
}

DS_TEST_FUNCTION(bfs_traversal) {
    const size_t list_from_expected[] = {0, 1, 2};
    const size_t list_all_expected[] = {0, 1, 2, 3, 4, 5};
    const size_t matrix_from_expected[] = {0, 1, 2, 3};
    ListGraph list = {0};
    MatrixGraph matrix = {0};
    VertexList order = {0};

    DS_CHECK(ListGraphInit(&list, 6, false));
    DS_CHECK(ListGraphAddEdge(&list, 0, 1));
    DS_CHECK(ListGraphAddEdge(&list, 0, 2));
    DS_CHECK(ListGraphAddEdge(&list, 3, 4));
    DS_CHECK(breadthFirstFromList(&list, 0, &order));
    DS_CHECK(vertex_list_equals(&order, list_from_expected, 3));
    DS_CHECK(breadthFirstTraverseList(&list, &order));
    DS_CHECK(vertex_list_equals(&order, list_all_expected, 6));

    DS_CHECK(MatrixGraphInit(&matrix, 4, false));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 2, 1));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 2, 3, 1));
    DS_CHECK(breadthFirstFromMatrix(&matrix, 0, &order));
    DS_CHECK(vertex_list_equals(&order, matrix_from_expected, 4));
    DS_CHECK(breadthFirstTraverseMatrix(&matrix, &order));
    DS_CHECK(vertex_list_equals(&order, matrix_from_expected, 4));

    VertexListDestroy(&order);
    MatrixGraphDestroy(&matrix);
    ListGraphDestroy(&list);
}

DS_TEST_FUNCTION(bfs_boundaries) {
    const size_t isolated_expected[] = {0, 1, 2};
    ListGraph empty = {0};
    ListGraph isolated = {0};
    MatrixGraph matrix_empty = {0};
    VertexList order = {0};

    DS_CHECK(ListGraphInit(&empty, 0, false));
    DS_CHECK(breadthFirstTraverseList(&empty, &order));
    DS_CHECK(order.size == 0);
    DS_CHECK(MatrixGraphInit(&matrix_empty, 0, false));
    DS_CHECK(breadthFirstTraverseMatrix(&matrix_empty, &order));
    DS_CHECK(order.size == 0);

    DS_CHECK(ListGraphInit(&isolated, 3, false));
    DS_CHECK(breadthFirstTraverseList(&isolated, &order));
    DS_CHECK(vertex_list_equals(&order, isolated_expected, 3));
    DS_CHECK(!breadthFirstFromList(&isolated, 3, &order));
    DS_CHECK(order.size == 0);

    VertexListDestroy(&order);
    MatrixGraphDestroy(&matrix_empty);
    ListGraphDestroy(&isolated);
    ListGraphDestroy(&empty);
}

DS_TEST_FUNCTION(bfs_shortest_distances) {
    const int expected[] = {0, 1, 1, 2, -1};
    const int singleton_expected[] = {0};
    ListGraph graph = {0};
    ListGraph singleton = {0};
    IntList distances = {0};

    DS_CHECK(ListGraphInit(&graph, 5, true));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 1));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 2));
    DS_CHECK(ListGraphAddEdge(&graph, 1, 3));
    DS_CHECK(ListGraphAddEdge(&graph, 2, 3));
    DS_CHECK(breadthFirstShortestDistances(&graph, 0, &distances));
    DS_CHECK(int_list_equals(&distances, expected, 5));

    DS_CHECK(ListGraphInit(&singleton, 1, true));
    DS_CHECK(breadthFirstShortestDistances(&singleton, 0, &distances));
    DS_CHECK(int_list_equals(&distances, singleton_expected, 1));
    DS_CHECK(!breadthFirstShortestDistances(&singleton, 1, &distances));
    DS_CHECK(distances.size == 0);

    IntListDestroy(&distances);
    ListGraphDestroy(&singleton);
    ListGraphDestroy(&graph);
}

DS_TEST_FUNCTION(dfs_traversal) {
    const size_t list_expected[] = {0, 1, 3, 2, 4};
    const size_t matrix_expected[] = {0, 1, 2, 3};
    ListGraph list = {0};
    ListGraph empty = {0};
    MatrixGraph matrix = {0};
    VertexList order = {0};

    DS_CHECK(ListGraphInit(&list, 5, false));
    DS_CHECK(ListGraphAddEdge(&list, 0, 1));
    DS_CHECK(ListGraphAddEdge(&list, 0, 2));
    DS_CHECK(ListGraphAddEdge(&list, 1, 3));
    DS_CHECK(depthFirstTraverseList(&list, &order));
    DS_CHECK(vertex_list_equals(&order, list_expected, 5));

    DS_CHECK(MatrixGraphInit(&matrix, 4, false));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 2, 1));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 2, 3, 1));
    DS_CHECK(depthFirstTraverseMatrix(&matrix, &order));
    DS_CHECK(vertex_list_equals(&order, matrix_expected, 4));

    DS_CHECK(ListGraphInit(&empty, 0, false));
    DS_CHECK(depthFirstTraverseList(&empty, &order));
    DS_CHECK(order.size == 0);

    VertexListDestroy(&order);
    MatrixGraphDestroy(&matrix);
    ListGraphDestroy(&empty);
    ListGraphDestroy(&list);
}

DS_TEST_FUNCTION(tree_detection) {
    ListGraph tree = {0};
    ListGraph cycle = {0};
    ListGraph disconnected = {0};
    ListGraph singleton = {0};
    ListGraph empty = {0};

    DS_CHECK(ListGraphInit(&tree, 4, false));
    DS_CHECK(ListGraphAddEdge(&tree, 0, 1));
    DS_CHECK(ListGraphAddEdge(&tree, 1, 2));
    DS_CHECK(ListGraphAddEdge(&tree, 1, 3));
    DS_CHECK(isUndirectedTree(&tree));

    DS_CHECK(ListGraphInit(&cycle, 3, false));
    DS_CHECK(ListGraphAddEdge(&cycle, 0, 1));
    DS_CHECK(ListGraphAddEdge(&cycle, 1, 2));
    DS_CHECK(ListGraphAddEdge(&cycle, 2, 0));
    DS_CHECK(!isUndirectedTree(&cycle));

    DS_CHECK(ListGraphInit(&disconnected, 3, false));
    DS_CHECK(ListGraphAddEdge(&disconnected, 0, 1));
    DS_CHECK(!isUndirectedTree(&disconnected));
    DS_CHECK(ListGraphInit(&singleton, 1, false));
    DS_CHECK(isUndirectedTree(&singleton));
    DS_CHECK(ListGraphInit(&empty, 0, false));
    DS_CHECK(!isUndirectedTree(&empty));

    ListGraphDestroy(&empty);
    ListGraphDestroy(&singleton);
    ListGraphDestroy(&disconnected);
    ListGraphDestroy(&cycle);
    ListGraphDestroy(&tree);
}

DS_TEST_FUNCTION(reachability) {
    ListGraph graph = {0};
    ListGraph empty = {0};

    DS_CHECK(ListGraphInit(&graph, 4, true));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 1));
    DS_CHECK(ListGraphAddEdge(&graph, 1, 2));
    DS_CHECK(depthFirstReachable(&graph, 0, 2));
    DS_CHECK(breadthFirstReachable(&graph, 0, 2));
    DS_CHECK(!depthFirstReachable(&graph, 2, 0));
    DS_CHECK(!breadthFirstReachable(&graph, 2, 0));
    DS_CHECK(depthFirstReachable(&graph, 2, 2));
    DS_CHECK(!breadthFirstReachable(&empty, 0, 0));

    ListGraphDestroy(&empty);
    ListGraphDestroy(&graph);
}

DS_TEST_FUNCTION(paths) {
    const size_t first[] = {0, 1, 3};
    const size_t second[] = {0, 1, 2, 3};
    const size_t third[] = {0, 2, 3};
    ListGraph graph = {0};
    ListGraph no_path = {0};
    ListGraph empty = {0};
    GraphPaths paths = {0};

    DS_CHECK(ListGraphInit(&graph, 4, true));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 1));
    DS_CHECK(ListGraphAddEdge(&graph, 0, 2));
    DS_CHECK(ListGraphAddEdge(&graph, 1, 3));
    DS_CHECK(ListGraphAddEdge(&graph, 2, 3));
    DS_CHECK(ListGraphAddEdge(&graph, 1, 2));
    DS_CHECK(findAllSimplePaths(&graph, 0, 3, &paths));
    DS_CHECK(paths.size == 3);
    if (paths.size == 3) {
        DS_CHECK(graph_path_equals(&paths.items[0], first, 3));
        DS_CHECK(graph_path_equals(&paths.items[1], second, 4));
        DS_CHECK(graph_path_equals(&paths.items[2], third, 3));
    }

    DS_CHECK(ListGraphInit(&no_path, 2, true));
    DS_CHECK(findAllSimplePaths(&no_path, 0, 1, &paths));
    DS_CHECK(paths.size == 0);
    DS_CHECK(ListGraphInit(&empty, 0, true));
    DS_CHECK(!findAllSimplePaths(&empty, 0, 0, &paths));
    DS_CHECK(paths.size == 0);

    GraphPathsDestroy(&paths);
    ListGraphDestroy(&empty);
    ListGraphDestroy(&no_path);
    ListGraphDestroy(&graph);
}

static bool init_sample_weighted_graph(WeightedGraph *graph) {
    return WeightedGraphInit(graph, 4) &&
           WeightedGraphAddEdge(graph, 0, 1, 1) &&
           WeightedGraphAddEdge(graph, 1, 2, 2) &&
           WeightedGraphAddEdge(graph, 0, 2, 4) &&
           WeightedGraphAddEdge(graph, 2, 3, 1) &&
           WeightedGraphAddEdge(graph, 1, 3, 5);
}

DS_TEST_FUNCTION(mst_framework) {
    WeightedGraph graph = {0};
    WeightedGraph empty = {0};
    WeightedGraph disconnected = {0};
    WeightedGraph wide_total = {0};
    SpanningTree tree = {0};

    DS_CHECK(init_sample_weighted_graph(&graph));
    DS_CHECK(genericMstFramework(&graph, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 3);
    DS_CHECK(tree.total_weight == 4);

    DS_CHECK(WeightedGraphInit(&empty, 0));
    DS_CHECK(genericMstFramework(&empty, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 0);

    DS_CHECK(WeightedGraphInit(&disconnected, 3));
    DS_CHECK(WeightedGraphAddEdge(&disconnected, 0, 1, 2));
    DS_CHECK(genericMstFramework(&disconnected, &tree));
    DS_CHECK(!tree.complete);

    DS_CHECK(WeightedGraphInit(&wide_total, 3));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 0, 1, INT_MAX));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 1, 2, 1));
    DS_CHECK(genericMstFramework(&wide_total, &tree));
    DS_CHECK(tree.total_weight == (long long)INT_MAX + 1);

    SpanningTreeDestroy(&tree);
    WeightedGraphDestroy(&wide_total);
    WeightedGraphDestroy(&disconnected);
    WeightedGraphDestroy(&empty);
    WeightedGraphDestroy(&graph);
}

DS_TEST_FUNCTION(prim_mst) {
    WeightedGraph graph = {0};
    WeightedGraph empty = {0};
    WeightedGraph disconnected = {0};
    WeightedGraph singleton = {0};
    WeightedGraph wide_total = {0};
    SpanningTree tree = {0};

    DS_CHECK(init_sample_weighted_graph(&graph));
    DS_CHECK(primMinimumSpanningTree(&graph, 0, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 3);
    DS_CHECK(tree.total_weight == 4);

    DS_CHECK(WeightedGraphInit(&empty, 0));
    DS_CHECK(primMinimumSpanningTree(&empty, 0, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 0);

    DS_CHECK(WeightedGraphInit(&disconnected, 3));
    DS_CHECK(WeightedGraphAddEdge(&disconnected, 0, 1, 2));
    DS_CHECK(primMinimumSpanningTree(&disconnected, 0, &tree));
    DS_CHECK(!tree.complete);

    DS_CHECK(WeightedGraphInit(&singleton, 1));
    DS_CHECK(primMinimumSpanningTree(&singleton, 0, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 0);
    DS_CHECK(!primMinimumSpanningTree(&singleton, 1, &tree));

    DS_CHECK(WeightedGraphInit(&wide_total, 3));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 0, 1, INT_MAX));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 1, 2, 1));
    DS_CHECK(primMinimumSpanningTree(&wide_total, 0, &tree));
    DS_CHECK(tree.total_weight == (long long)INT_MAX + 1);
    DS_CHECK(!primMinimumSpanningTree(&graph, 4, &tree));

    SpanningTreeDestroy(&tree);
    WeightedGraphDestroy(&wide_total);
    WeightedGraphDestroy(&singleton);
    WeightedGraphDestroy(&disconnected);
    WeightedGraphDestroy(&empty);
    WeightedGraphDestroy(&graph);
}

DS_TEST_FUNCTION(kruskal_mst) {
    WeightedGraph graph = {0};
    WeightedGraph empty = {0};
    WeightedGraph disconnected = {0};
    WeightedGraph wide_total = {0};
    SpanningTree tree = {0};

    DS_CHECK(init_sample_weighted_graph(&graph));
    DS_CHECK(kruskalMinimumSpanningTree(&graph, &tree));
    DS_CHECK(tree.complete);
    DS_CHECK(tree.edge_count == 3);
    DS_CHECK(tree.total_weight == 4);

    DS_CHECK(WeightedGraphInit(&empty, 0));
    DS_CHECK(kruskalMinimumSpanningTree(&empty, &tree));
    DS_CHECK(tree.complete);

    DS_CHECK(WeightedGraphInit(&disconnected, 3));
    DS_CHECK(WeightedGraphAddEdge(&disconnected, 0, 1, 2));
    DS_CHECK(kruskalMinimumSpanningTree(&disconnected, &tree));
    DS_CHECK(!tree.complete);

    DS_CHECK(WeightedGraphInit(&wide_total, 3));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 0, 1, INT_MAX));
    DS_CHECK(WeightedGraphAddEdge(&wide_total, 1, 2, 1));
    DS_CHECK(kruskalMinimumSpanningTree(&wide_total, &tree));
    DS_CHECK(tree.total_weight == (long long)INT_MAX + 1);

    SpanningTreeDestroy(&tree);
    WeightedGraphDestroy(&wide_total);
    WeightedGraphDestroy(&disconnected);
    WeightedGraphDestroy(&empty);
    WeightedGraphDestroy(&graph);
}

DS_TEST_FUNCTION(topological_sort) {
    ListGraph dag = {0};
    ListGraph cycle = {0};
    ListGraph empty = {0};
    VertexList order = {0};
    size_t position[4] = {0};

    DS_CHECK(ListGraphInit(&dag, 4, true));
    DS_CHECK(ListGraphAddEdge(&dag, 0, 1));
    DS_CHECK(ListGraphAddEdge(&dag, 0, 2));
    DS_CHECK(ListGraphAddEdge(&dag, 1, 3));
    DS_CHECK(ListGraphAddEdge(&dag, 2, 3));
    DS_CHECK(topologicalSort(&dag, &order));
    DS_CHECK(order.size == 4);
    if (order.size == 4) {
        for (size_t i = 0; i < order.size; ++i) position[order.items[i]] = i;
        DS_CHECK(position[0] < position[1]);
        DS_CHECK(position[0] < position[2]);
        DS_CHECK(position[1] < position[3]);
        DS_CHECK(position[2] < position[3]);
    }

    DS_CHECK(ListGraphInit(&cycle, 2, true));
    DS_CHECK(ListGraphAddEdge(&cycle, 0, 1));
    DS_CHECK(ListGraphAddEdge(&cycle, 1, 0));
    DS_CHECK(!topologicalSort(&cycle, &order));
    DS_CHECK(ListGraphInit(&empty, 0, true));
    DS_CHECK(topologicalSort(&empty, &order));
    DS_CHECK(order.size == 0);

    VertexListDestroy(&order);
    ListGraphDestroy(&empty);
    ListGraphDestroy(&cycle);
    ListGraphDestroy(&dag);
}

DS_TEST_FUNCTION(dfs_topological_sort) {
    ListGraph dag = {0};
    ListGraph empty = {0};
    VertexList order = {0};
    size_t position[4] = {0};

    DS_CHECK(ListGraphInit(&dag, 4, true));
    DS_CHECK(ListGraphAddEdge(&dag, 0, 1));
    DS_CHECK(ListGraphAddEdge(&dag, 0, 2));
    DS_CHECK(ListGraphAddEdge(&dag, 1, 3));
    DS_CHECK(ListGraphAddEdge(&dag, 2, 3));
    DS_CHECK(depthFirstFinishOrder(&dag, &order));
    DS_CHECK(order.size == 4);
    if (order.size == 4) {
        for (size_t i = 0; i < order.size; ++i) position[order.items[i]] = i;
        DS_CHECK(position[0] < position[1]);
        DS_CHECK(position[0] < position[2]);
        DS_CHECK(position[1] < position[3]);
        DS_CHECK(position[2] < position[3]);
    }
    DS_CHECK(ListGraphInit(&empty, 0, true));
    DS_CHECK(depthFirstFinishOrder(&empty, &order));
    DS_CHECK(order.size == 0);

    VertexListDestroy(&order);
    ListGraphDestroy(&empty);
    ListGraphDestroy(&dag);
}

DS_TEST_FUNCTION(unique_topological_order) {
    MatrixGraph chain = {0};
    MatrixGraph ambiguous = {0};
    MatrixGraph cycle = {0};
    MatrixGraph empty = {0};

    DS_CHECK(MatrixGraphInit(&chain, 3, true));
    DS_CHECK(MatrixGraphAddEdge(&chain, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&chain, 1, 2, 1));
    DS_CHECK(hasUniqueTopologicalOrder(&chain));

    DS_CHECK(MatrixGraphInit(&ambiguous, 3, true));
    DS_CHECK(MatrixGraphAddEdge(&ambiguous, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&ambiguous, 0, 2, 1));
    DS_CHECK(!hasUniqueTopologicalOrder(&ambiguous));

    DS_CHECK(MatrixGraphInit(&cycle, 2, true));
    DS_CHECK(MatrixGraphAddEdge(&cycle, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&cycle, 1, 0, 1));
    DS_CHECK(!hasUniqueTopologicalOrder(&cycle));
    DS_CHECK(MatrixGraphInit(&empty, 0, true));
    DS_CHECK(hasUniqueTopologicalOrder(&empty));

    MatrixGraphDestroy(&empty);
    MatrixGraphDestroy(&cycle);
    MatrixGraphDestroy(&ambiguous);
    MatrixGraphDestroy(&chain);
}

DS_TEST_FUNCTION(next_neighbors) {
    MatrixGraph matrix = {0};
    ListGraph list = {0};

    DS_CHECK(MatrixGraphInit(&matrix, 4, true));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 1, 1));
    DS_CHECK(MatrixGraphAddEdge(&matrix, 0, 3, -7));
    DS_CHECK(nextNeighborMatrix(&matrix, 0, 1) == 3);
    DS_CHECK(nextNeighborMatrix(&matrix, 0, 3) == -1);
    DS_CHECK(nextNeighborMatrix(&matrix, -1, 0) == -1);

    DS_CHECK(ListGraphInit(&list, 4, true));
    DS_CHECK(ListGraphAddEdge(&list, 0, 2));
    DS_CHECK(ListGraphAddEdge(&list, 0, 1));
    DS_CHECK(ListGraphAddEdge(&list, 0, 3));
    DS_CHECK(nextNeighborList(&list, 0, 2) == 1);
    DS_CHECK(nextNeighborList(&list, 0, 3) == -1);
    DS_CHECK(nextNeighborList(&list, 1, 0) == -1);

    ListGraphDestroy(&list);
    MatrixGraphDestroy(&matrix);
}

DS_TEST_FUNCTION(source_types) {
    SourceMatrixGraph matrix = {0};
    SourceAdjListGraph list = {0};
    EulerTrail2021MGraph question_euler = {0};
    KVertices2023MGraph question_k = {0};
    UniqueTopologicalOrderMGraph question_topology = {0};
    RouterNode router = {0};
    SourceArcNode *first = (SourceArcNode *)calloc(1, sizeof(*first));
    SourceArcNode *second = (SourceArcNode *)calloc(1, sizeof(*second));
    RouterNode *router_list = (RouterNode *)calloc(1, sizeof(*router_list));
    RouteArc *route = (RouteArc *)calloc(1, sizeof(*route));

    matrix.vexnum = 1;
    matrix.vex[0] = 'A';
    DS_CHECK(matrix.vexnum == 1 && matrix.vex[0] == 'A');
    list.vexnum = 1;
    list.vertices[0].data = 'B';
    DS_CHECK(list.vexnum == 1 && list.vertices[0].data == 'B');
    question_euler.numVertices = 1;
    question_k.numVertices = 1;
    question_topology.numVertices = 1;
    DS_CHECK(question_euler.numVertices == 1 && question_k.numVertices == 1 &&
             question_topology.numVertices == 1);
    DS_CHECK(router.IN_link == NULL && router.next == NULL);

    if (first != NULL && second != NULL) {
        first->nextarc = second;
        list.vertices[0].firstarc = first;
    } else {
        free(first);
        free(second);
    }
    SourceAdjListGraphDestroy(&list);
    DS_CHECK(list.vertices[0].firstarc == NULL);

    if (router_list != NULL && route != NULL) {
        router_list->IN_link = route;
        RoutingRouterListDestroy(router_list);
    } else {
        free(router_list);
        free(route);
    }
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(graph_conversion),
        DS_TEST_CASE(graph_conversion_boundaries),
        DS_TEST_CASE(euler_trail_degree),
        DS_TEST_CASE(vertices_by_degree),
        DS_TEST_CASE(bfs_traversal),
        DS_TEST_CASE(bfs_boundaries),
        DS_TEST_CASE(bfs_shortest_distances),
        DS_TEST_CASE(dfs_traversal),
        DS_TEST_CASE(tree_detection),
        DS_TEST_CASE(reachability),
        DS_TEST_CASE(paths),
        DS_TEST_CASE(mst_framework),
        DS_TEST_CASE(prim_mst),
        DS_TEST_CASE(kruskal_mst),
        DS_TEST_CASE(topological_sort),
        DS_TEST_CASE(dfs_topological_sort),
        DS_TEST_CASE(unique_topological_order),
        DS_TEST_CASE(next_neighbors),
        DS_TEST_CASE(source_types),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
