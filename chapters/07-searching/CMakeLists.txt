add_ds_test_executable(ch07_search_tests
        tests/search_tests.c
        body/search_algorithms.c
        questions/search_question_snippets.c
        answers/search_answers.c
)
target_include_directories(ch07_search_tests PRIVATE body answers questions)

foreach(CASE_NAME IN ITEMS sequential_search sequential_boundaries binary_search stride_search
        recursive_binary_search self_organizing_search sorted_matrix_search bst_search bst_insert_build
        judge_bst search_level judge_avl minmax output_threshold kth_smallest source_types)
    add_ds_test_case(ch07_search_tests ${CASE_NAME})
endforeach()
