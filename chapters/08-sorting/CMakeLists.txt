add_ds_test_executable(ch08_sort_tests
        tests/sorting_tests.c
        body/sorting_algorithms.c
        questions/comparison_count_sort.c
        answers/sorting_answers.c
        answers/sorting_exploration.c
)
target_include_directories(ch08_sort_tests PRIVATE body answers questions)

foreach(CASE_NAME IN ITEMS
        swap_values insertion_sort binary_insertion_sort shell_sort bubble_sort quick_sort
        first_pivot_partition selection_sort heap_adjust build_max_heap heap_sort
        merge_ranges merge_sort counting_sort move_even_before_odd kth_element
        arrange_flag balanced_partition linked_list_selection_sort is_min_heap
        priority_queue_operations insertion_sort_suffix last_pivot_partition
        comparison_count_sort stable_pair_count_fragment range_frequency_sort)
    add_ds_test_case(ch08_sort_tests ${CASE_NAME})
endforeach()
