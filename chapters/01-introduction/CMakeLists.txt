add_ds_test_executable(ch01_reverse_search_tests
        tests/reverse_search_tests.c
        body/reverse_search.c
)
target_include_directories(ch01_reverse_search_tests PRIVATE body)
add_ds_test_case(ch01_reverse_search_tests reverse_search)

add_ds_test_executable(ch01_body_complexity_tests
        tests/body_complexity_tests.c
        body/additive_block_example.c
        body/multiplicative_block_example.c
        body/summary_doubling_loop.c
        body/summary_square_root_loop.c
)
target_include_directories(ch01_body_complexity_tests PRIVATE body)
foreach(CASE_NAME IN ITEMS additive_blocks multiplicative_blocks summary_doubling
        summary_square_root)
    add_ds_test_case(ch01_body_complexity_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch01_complexity_question_tests
        tests/complexity_questions_tests.c
        questions/q06_double_loop.c
        questions/q07_cube_loop.c
        questions/q08_bubble_frequency.c
        questions/q09_branch_loops.c
        questions/q10_triangular_loop.c
        questions/q11_recurrence.c
        questions/q12_doubling.c
        questions/q13_factorial.c
        questions/q14_geometric_outer.c
        questions/q15_triangular_sum.c
        questions/q16_integer_sqrt.c
        questions/q17_geometric_nested.c
        questions/q18_sqrt_triangular.c
        questions/application_01_linear.c
        questions/application_02_integer_sqrt.c
        questions/application_03_zero_matrix.c
)
target_include_directories(ch01_complexity_question_tests PRIVATE questions)
foreach(CASE_NAME IN ITEMS q06 q07 q08 q09 q10 q11 q12 q13 q14 q15 q16 q17 q18
        application_01 application_02 application_03)
    add_ds_test_case(ch01_complexity_question_tests ${CASE_NAME})
endforeach()
