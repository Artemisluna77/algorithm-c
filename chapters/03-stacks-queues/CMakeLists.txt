add_ds_test_executable(ch03_body_tests
        tests/body_tests.c
        body/init_stack.c
        body/stack_empty.c
        body/push.c
        body/pop.c
        body/get_top.c
        body/init_circular_queue.c
        body/circular_queue_empty.c
        body/circular_enqueue.c
        body/circular_dequeue.c
        body/linked_queue_init.c
        body/linked_queue_empty.c
        body/linked_enqueue.c
        body/linked_dequeue.c
        body/fibonacci.c
        body/summary_stack_init.c
        body/summary_stack_push.c
        body/summary_stack_pop.c
)
target_include_directories(ch03_body_tests PRIVATE body)
foreach(CASE_NAME IN ITEMS seq_stack_init seq_stack_empty seq_stack_push seq_stack_pop
        seq_stack_get_top link_stack_node circular_queue_init circular_queue_enqueue
        circular_queue_dequeue linked_queue_init linked_queue_enqueue linked_queue_dequeue
        fibonacci summary_stack_init summary_stack_push summary_stack_pop)
    add_ds_test_case(ch03_body_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch03_answer_tests
        tests/answer_tests.c
        answers/shared_stack_init.c
        answers/shared_stack_push.c
        answers/shared_stack_pop.c
        answers/judge_stack_sequence.c
        answers/list_palindrome.c
        answers/tagged_queue_enqueue.c
        answers/tagged_queue_dequeue.c
        answers/inverse_queue.c
        answers/two_stack_queue_enqueue.c
        answers/two_stack_queue_dequeue.c
        answers/two_stack_queue_empty.c
        answers/brackets_check.c
)
target_include_directories(ch03_answer_tests PRIVATE answers)
foreach(CASE_NAME IN ITEMS shared_stack_init shared_stack_push shared_stack_pop
        judge_stack_sequence list_palindrome inverse_queue tagged_queue_enqueue
        tagged_queue_dequeue two_stack_enqueue two_stack_dequeue two_stack_empty
        brackets_check)
    add_ds_test_case(ch03_answer_tests ${CASE_NAME})
endforeach()

add_ds_test_executable(ch03_question_tests
        tests/question_tests.c
        questions/q05_recursive_expression.c
        questions/q06_recursive_calls.c
        questions/q07_recursive_order.c
        questions/q15_recursive_sum.c
)
target_include_directories(ch03_question_tests PRIVATE questions)
foreach(CASE_NAME IN ITEMS q05_recursive_expression q06_recursive_calls
        q07_recursive_order q15_recursive_sum provided_stack_queue_interfaces)
    add_ds_test_case(ch03_question_tests ${CASE_NAME})
endforeach()
