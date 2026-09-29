add_ds_test_executable(ch05_tree_tests
        tests/tree_tests.c
        body/binary_tree.c
        body/threaded_tree.c
        body/tree_forest.c
        body/disjoint_set.c
        answers/tree_solutions.c
)
target_include_directories(ch05_tree_tests PRIVATE body questions answers)

foreach(CASE_NAME IN ITEMS question_types traversals traversal_boundaries threaded_tree
        binary_tree_answers binary_tree_edges deletion ancestor_lca width
        full_tree_conversion leaf_list similarity weighted_path expression_tree
        sequential_lca sequential_bst tree_forest_roundtrip forest_algorithms
        disjoint_set_operations disjoint_set_boundaries generic_traversal)
    add_ds_test_case(ch05_tree_tests ${CASE_NAME})
endforeach()
