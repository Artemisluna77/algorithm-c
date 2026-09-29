#include "circular_queue.h"
#include "linked_queue.h"
#include "linked_stack_node.h"
#include "recursion.h"
#include "sequential_stack.h"
#include "summary_stack.h"
#include "test_harness.h"

#include <stddef.h>

DS_TEST_FUNCTION(seq_stack_init) {
    SequentialStack stack = {{0}, 7};
    InitStack(&stack);
    DS_CHECK(stack.top == -1);
    DS_CHECK(StackEmpty(&stack));
}

DS_TEST_FUNCTION(seq_stack_empty) {
    SequentialStack stack = {{0}, -1};
    DS_CHECK(StackEmpty(&stack));
    DS_CHECK(Push(&stack, 9));
    DS_CHECK(!StackEmpty(&stack));
}

DS_TEST_FUNCTION(seq_stack_push) {
    SequentialStack stack = {{0}, -1};
    InitStack(&stack);
    DS_CHECK(Push(&stack, 10));
    DS_CHECK(Push(&stack, 20));
    DS_CHECK(stack.data[stack.top] == 20);
    for (int i = 2; i < SEQUENTIAL_STACK_MAX_SIZE; ++i) {
        DS_CHECK(Push(&stack, i));
    }
    DS_CHECK(!Push(&stack, 99));
    DS_CHECK(stack.top == SEQUENTIAL_STACK_MAX_SIZE - 1);
}

DS_TEST_FUNCTION(seq_stack_pop) {
    SequentialStack stack = {{0}, -1};
    int value = -1;
    InitStack(&stack);
    DS_CHECK(!Pop(&stack, &value));
    DS_CHECK(value == -1);
    DS_CHECK(Push(&stack, 3));
    DS_CHECK(Push(&stack, 8));
    DS_CHECK(Pop(&stack, &value));
    DS_CHECK(value == 8);
    DS_CHECK(Pop(&stack, &value));
    DS_CHECK(value == 3);
    DS_CHECK(StackEmpty(&stack));
}

DS_TEST_FUNCTION(seq_stack_get_top) {
    SequentialStack stack = {{0}, -1};
    int value = 77;
    InitStack(&stack);
    DS_CHECK(!GetTop(&stack, &value));
    DS_CHECK(value == 77);
    DS_CHECK(Push(&stack, 5));
    DS_CHECK(GetTop(&stack, &value));
    DS_CHECK(value == 5);
    DS_CHECK(!StackEmpty(&stack));
}

DS_TEST_FUNCTION(link_stack_node) {
    LinkStackNode tail = {24, NULL};
    LinkStackNode node = {42, &tail};
    DS_CHECK(node.data == 42);
    DS_CHECK(node.next->data == 24);
}

DS_TEST_FUNCTION(circular_queue_init) {
    CircularQueue queue = {{0}, 3, 7};
    InitQueue(&queue);
    DS_CHECK(queue.front == 0);
    DS_CHECK(queue.rear == 0);
    DS_CHECK(QueueEmpty(&queue));
}

DS_TEST_FUNCTION(circular_queue_enqueue) {
    CircularQueue queue = {{0}, 0, 0};
    InitQueue(&queue);
    for (int i = 0; i < CIRCULAR_QUEUE_MAX_SIZE - 1; ++i) {
        DS_CHECK(EnQueue(&queue, i));
    }
    DS_CHECK(!EnQueue(&queue, 99));
    int value = -1;
    DS_CHECK(DeQueue(&queue, &value));
    DS_CHECK(value == 0);
    DS_CHECK(EnQueue(&queue, 99));
    DS_CHECK(queue.rear == 0);

    queue.front = -1;
    DS_CHECK(!EnQueue(&queue, 100));
}

DS_TEST_FUNCTION(circular_queue_dequeue) {
    CircularQueue queue = {{0}, 0, 0};
    int value = -1;
    InitQueue(&queue);
    DS_CHECK(!DeQueue(&queue, &value));
    DS_CHECK(EnQueue(&queue, 7));
    DS_CHECK(EnQueue(&queue, 8));
    DS_CHECK(DeQueue(&queue, &value));
    DS_CHECK(value == 7);
    DS_CHECK(DeQueue(&queue, &value));
    DS_CHECK(value == 8);
    DS_CHECK(QueueEmpty(&queue));

    queue.rear = CIRCULAR_QUEUE_MAX_SIZE;
    DS_CHECK(!DeQueue(&queue, &value));
    DS_CHECK(QueueEmpty(&queue));
}

DS_TEST_FUNCTION(linked_queue_init) {
    LinkedQueue queue = {0};
    InitLinkedQueue(&queue);
    DS_CHECK(queue.rear == &queue.header);
    DS_CHECK(LinkedQueueEmpty(&queue));
    DS_CHECK(LinkedEnQueue(&queue, 9));
    InitLinkedQueue(&queue);
    DS_CHECK(LinkedQueueEmpty(&queue));
    DestroyLinkedQueue(&queue);
}

DS_TEST_FUNCTION(linked_queue_enqueue) {
    LinkedQueue queue = {0};
    InitLinkedQueue(&queue);
    DS_CHECK(LinkedEnQueue(&queue, 4));
    DS_CHECK(LinkedEnQueue(&queue, 6));
    DS_CHECK(!LinkedQueueEmpty(&queue));
    DS_CHECK(queue.header.next->data == 4);
    DS_CHECK(queue.rear->data == 6);
    DestroyLinkedQueue(&queue);
    DS_CHECK(LinkedQueueEmpty(&queue));
}

DS_TEST_FUNCTION(linked_queue_dequeue) {
    LinkedQueue queue = {0};
    int value = -1;
    InitLinkedQueue(&queue);
    DS_CHECK(!LinkedDeQueue(&queue, &value));
    DS_CHECK(LinkedEnQueue(&queue, 4));
    DS_CHECK(LinkedEnQueue(&queue, 6));
    DS_CHECK(LinkedDeQueue(&queue, &value));
    DS_CHECK(value == 4);
    DS_CHECK(LinkedDeQueue(&queue, &value));
    DS_CHECK(value == 6);
    DS_CHECK(LinkedQueueEmpty(&queue));
    DS_CHECK(queue.rear == &queue.header);
    DestroyLinkedQueue(&queue);
}

DS_TEST_FUNCTION(fibonacci) {
    int value = -1;
    DS_CHECK(Fibonacci(0, &value) && value == 0);
    DS_CHECK(Fibonacci(1, &value) && value == 1);
    DS_CHECK(Fibonacci(10, &value) && value == 55);
    DS_CHECK(Fibonacci(46, &value) && value == 1836311903);
    DS_CHECK(!Fibonacci(-1, &value));
    DS_CHECK(!Fibonacci(47, &value));
    DS_CHECK(!Fibonacci(10, NULL));
}

DS_TEST_FUNCTION(summary_stack_init) {
    SummaryStack stack = {{0}, 10};
    InitSummaryStack(&stack);
    DS_CHECK(stack.top == -1);
}

DS_TEST_FUNCTION(summary_stack_push) {
    SummaryStack stack = {{0}, -1};
    InitSummaryStack(&stack);
    DS_CHECK(SummaryPush(&stack, 5));
    DS_CHECK(stack.top == 0);
    DS_CHECK(stack.data[0] == 5);
    for (int i = 1; i < SUMMARY_STACK_MAX_SIZE; ++i) {
        DS_CHECK(SummaryPush(&stack, i));
    }
    DS_CHECK(!SummaryPush(&stack, 99));
}

DS_TEST_FUNCTION(summary_stack_pop) {
    SummaryStack stack = {{0}, -1};
    int value = -1;
    InitSummaryStack(&stack);
    DS_CHECK(!SummaryPop(&stack, &value));
    DS_CHECK(SummaryPush(&stack, 11));
    DS_CHECK(SummaryPop(&stack, &value));
    DS_CHECK(value == 11);
    DS_CHECK(stack.top == -1);
}

int main(int argc, char **argv) {
    static const DsTestCase cases[] = {
        DS_TEST_CASE(seq_stack_init),
        DS_TEST_CASE(seq_stack_empty),
        DS_TEST_CASE(seq_stack_push),
        DS_TEST_CASE(seq_stack_pop),
        DS_TEST_CASE(seq_stack_get_top),
        DS_TEST_CASE(link_stack_node),
        DS_TEST_CASE(circular_queue_init),
        DS_TEST_CASE(circular_queue_enqueue),
        DS_TEST_CASE(circular_queue_dequeue),
        DS_TEST_CASE(linked_queue_init),
        DS_TEST_CASE(linked_queue_enqueue),
        DS_TEST_CASE(linked_queue_dequeue),
        DS_TEST_CASE(fibonacci),
        DS_TEST_CASE(summary_stack_init),
        DS_TEST_CASE(summary_stack_push),
        DS_TEST_CASE(summary_stack_pop),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
