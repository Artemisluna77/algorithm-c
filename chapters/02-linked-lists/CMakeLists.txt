add_ds_test_executable(ch02_sequential_list_tests
        tests/sequential_list_tests.c
        body/sequential_list.c
)
target_include_directories(ch02_sequential_list_tests PRIVATE body)

foreach(CASE_NAME IN ITEMS init_static init_dynamic allocation_examples insert_positions
        insert_boundaries delete_positions delete_boundaries locate)
    add_ds_test_case(ch02_sequential_list_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch02_sequential_algorithms_tests
        tests/sequential_algorithms_tests.c
        body/sequential_list.c
        answers/sequential_algorithms.c
)
target_include_directories(ch02_sequential_algorithms_tests PRIVATE body answers)

foreach(CASE_NAME IN ITEMS delete_minimum reverse_sequence erase_value delete_same_sequence erase_range merge_sequence
        reverse_blocks search_exchange_insert common_three rotate_left median_two_sorted majority
        missing_positive minimum_three_distance suffix_extreme_product)
    add_ds_test_case(ch02_sequential_algorithms_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch02_linked_list_tests
        tests/linked_list_tests.c
        body/linked_lists.c
)
target_include_directories(ch02_linked_list_tests PRIVATE body questions)

foreach(CASE_NAME IN ITEMS init_list_forms length get_by_index locate_value insert_delete
        operation_boundaries build_head_tail doubly_link_operations static_and_question_types)
    add_ds_test_case(ch02_linked_list_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch02_linked_list_algorithms_tests
        tests/linked_list_algorithms_tests.c
        body/linked_lists.c
        answers/linked_list_algorithms.c
)
target_include_directories(ch02_linked_list_algorithms_tests PRIVATE body answers)

foreach(CASE_NAME IN ITEMS delete_value_methods delete_minimum reverse_methods delete_open_range
        split_alternating_positions erase_adjacent_duplicates sorted_intersections
        contiguous_pattern circular_singly_link circular_doubly_symmetry frequency_locate
        rotate_right symmetric_pair_sum find_loop_start kth_from_end common_suffix
        absolute_value_deduplication reorder_first_last)
    add_ds_test_case(ch02_linked_list_algorithms_tests ${CASE_NAME})
endforeach()
