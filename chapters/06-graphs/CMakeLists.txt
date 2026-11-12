add_ds_test_executable(ch06_graph_tests
        tests/graph_tests.c
        body/graph_algorithms.c
        answers/graph_answers.c
        answers/routing_types.c
)
target_include_directories(ch06_graph_tests PRIVATE body answers questions)

foreach(CASE_NAME IN ITEMS graph_conversion graph_conversion_boundaries euler_trail_degree
        vertices_by_degree bfs_traversal bfs_boundaries bfs_shortest_distances dfs_traversal
        tree_detection reachability paths mst_framework prim_mst kruskal_mst topological_sort
        dfs_topological_sort unique_topological_order next_neighbors source_types)
    add_ds_test_case(ch06_graph_tests ${CASE_NAME})
endforeach()
