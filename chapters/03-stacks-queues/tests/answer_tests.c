#include "brackets_check.h"
#include "shared_stack.h"
#include "stack_algorithms.h"
#include "test_harness.h"

#include <stddef.h>
#include <stdlib.h>

DS_TEST_FUNCTION(shared_stack_init) {
    SharedStack stacks = {{0}, {4, 5}};
    InitSharedStack(&stacks);
    DS_CHECK(stacks.top[0] == -1);
    DS_CHECK(stacks.top[1] == SHARED_STACK_MAX_SIZE);
}

DS_TEST_FUNCTION(shared_stack_push) {
    SharedStack stacks = {{0}, {0, 0}};
    InitSharedStack(&stacks);
    DS_CHECK(SharedPush(&stacks, 0, 10));
    DS_CHECK(SharedPush(&stacks, 1, 20));
    DS_CHECK(stacks.data[0] == 10);
    DS_CHECK(stacks.data[SHARED_STACK_MAX_SIZE - 1] == 20);
    for (int i = 0; i < SHARED_STACK_MAX_SIZE - 2; ++i) {
        DS_CHECK(SharedPush(&stacks, i % 2, i));
    }
    DS_CHECK(!SharedPush(&stacks, 0, 99));
    DS_CHECK(!SharedPush(&stacks, 2, 99));
}

DS_TEST_FUNCTION(shared_stack_pop) {
    SharedStack stacks = {{0}, {0, 0}};
    int value = -1;
    InitSharedStack(&stacks);
    DS_CHECK(!SharedPop(&stacks, 0, &value));
    DS_CHECK(!SharedPop(&stacks, 1, &value));
    DS_CHECK(SharedPush(&stacks, 0, 1));
    DS_CHECK(SharedPush(&stacks, 0, 2));
    DS_CHECK(SharedPush(&stacks, 1, 7));
    DS_CHECK(SharedPop(&stacks, 0, &value) && value == 2);
    DS_CHECK(SharedPop(&stacks, 1, &value) && value == 7);
    DS_CHECK(SharedPop(&stacks, 0, &value) && value == 1);
    DS_CHECK(!SharedPop(&stacks, 8, &value));
}

DS_TEST_FUNCTION(judge_stack_sequence) {
    DS_CHECK(JudgeStackSequence("IIOO"));
    DS_CHECK(JudgeStackSequence("IO"));
    DS_CHECK(!JudgeStackSequence("IOO"));
    DS_CHECK(!JudgeStackSequence("IXO"));
    DS_CHECK(!JudgeStackSequence(NULL));
}

DS_TEST_FUNCTION(list_palindrome) {
    const char odd[] = {'r', 'a', 'd', 'a', 'r'};
    const char even[] = {'n', 'o', 'o', 'n'};
    const char mismatch[] = {'a', 'b', 'c'};
    DS_CHECK(IsLinkedListPalindrome(odd, sizeof(odd)));
    DS_CHECK(IsLinkedListPalindrome(even, sizeof(even)));
    DS_CHECK(!IsLinkedListPalindrome(mismatch, sizeof(mismatch)));
    DS_CHECK(IsLinkedListPalindrome(NULL, 0));
    DS_CHECK(!IsLinkedListPalindrome(NULL, 1));
}

DS_TEST_FUNCTION(inverse_queue) {
    int values[] = {1, 2, 3};
    DS_CHECK(InverseQueue(NULL, 0));
    DS_CHECK(InverseQueue(values, sizeof(values) / sizeof(values[0])));
    DS_CHECK(values[0] == 3 && values[1] == 2 && values[2] == 1);
    DS_CHECK(!InverseQueue(NULL, 1));
}

DS_TEST_FUNCTION(tagged_queue_enqueue) {
    TaggedCircularQueue queue = {{0}, 0, 0, 0};
    for (int i = 0; i < TAGGED_CIRCULAR_QUEUE_MAX_SIZE; ++i) {
        DS_CHECK(TaggedEnQueue(&queue, i));
    }
    DS_CHECK(!TaggedEnQueue(&queue, 99));
    int value = -1;
    DS_CHECK(TaggedDeQueue(&queue, &value));
    DS_CHECK(value == 0);
    DS_CHECK(TaggedEnQueue(&queue, 99));
    DS_CHECK(queue.front == 1);
    DS_CHECK(queue.rear == 1);
    DS_CHECK(!TaggedEnQueue(&queue, 100));
}

DS_TEST_FUNCTION(tagged_queue_dequeue) {
    TaggedCircularQueue queue = {{0}, 0, 0, 0};
    int value = -1;
    DS_CHECK(!TaggedDeQueue(&queue, &value));
    DS_CHECK(TaggedEnQueue(&queue, 6));
    DS_CHECK(TaggedDeQueue(&queue, &value));
    DS_CHECK(value == 6);
    DS_CHECK(!TaggedDeQueue(&queue, &value));
}

DS_TEST_FUNCTION(two_stack_enqueue) {
    TwoStackQueue queue = {0};
    TwoStackQueue zero_capacity_queue = {0};
    DS_CHECK(TwoStackQueueInit(&queue, 2));
    DS_CHECK(TwoStackQueueInit(&zero_capacity_queue, 0));
    DS_CHECK(!TwoStackQueueInit(&zero_capacity_queue, (size_t)-1));
    DS_CHECK(TwoStackQueueEmpty(&zero_capacity_queue));
    DS_CHECK(!TwoStackQueueEnQueue(&zero_capacity_queue, 1));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 1));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 2));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 3));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 4));
    DS_CHECK(!TwoStackQueueEnQueue(&queue, 5));
    int value = 0;
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value) && value == 1);
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value) && value == 2);
    DS_CHECK(TwoStackQueueEnQueue(&queue, 5));
    DS_CHECK(!TwoStackQueueEmpty(&queue));
    TwoStackQueueDestroy(&queue);
    TwoStackQueueDestroy(&zero_capacity_queue);
    DS_CHECK(TwoStackQueueEmpty(&queue));
}

DS_TEST_FUNCTION(two_stack_dequeue) {
    TwoStackQueue queue = {0};
    int value = -1;
    DS_CHECK(TwoStackQueueInit(&queue, 3));
    DS_CHECK(!TwoStackQueueDeQueue(&queue, &value));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 4));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 5));
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value) && value == 4);
    DS_CHECK(TwoStackQueueEnQueue(&queue, 6));
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value) && value == 5);
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value) && value == 6);
    DS_CHECK(!TwoStackQueueDeQueue(&queue, &value));
    TwoStackQueueDestroy(&queue);
}

DS_TEST_FUNCTION(two_stack_empty) {
    TwoStackQueue queue = {0};
    DS_CHECK(TwoStackQueueInit(&queue, 2));
    DS_CHECK(TwoStackQueueEmpty(&queue));
    DS_CHECK(TwoStackQueueEnQueue(&queue, 1));
    DS_CHECK(!TwoStackQueueEmpty(&queue));
    int value = 0;
    DS_CHECK(TwoStackQueueDeQueue(&queue, &value));
    DS_CHECK(TwoStackQueueEmpty(&queue));
    TwoStackQueueDestroy(&queue);
}

DS_TEST_FUNCTION(brackets_check) {
    DS_CHECK(BracketsCheck("([{}])"));
    DS_CHECK(BracketsCheck(""));
    DS_CHECK(!BracketsCheck("([)]"));
    DS_CHECK(!BracketsCheck("(()"));
    DS_CHECK(!BracketsCheck(")"));
    DS_CHECK(!BracketsCheck(NULL));
}

int main(int argc, char **argv) {
    static const DsTestCase cases[] = {
        DS_TEST_CASE(shared_stack_init),
        DS_TEST_CASE(shared_stack_push),
        DS_TEST_CASE(shared_stack_pop),
        DS_TEST_CASE(judge_stack_sequence),
        DS_TEST_CASE(list_palindrome),
        DS_TEST_CASE(inverse_queue),
        DS_TEST_CASE(tagged_queue_enqueue),
        DS_TEST_CASE(tagged_queue_dequeue),
        DS_TEST_CASE(two_stack_enqueue),
        DS_TEST_CASE(two_stack_dequeue),
        DS_TEST_CASE(two_stack_empty),
        DS_TEST_CASE(brackets_check),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
