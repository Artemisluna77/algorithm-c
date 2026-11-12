#include "q03_stack_queue_api.h"
#include "recursion_snippets.h"
#include "test_harness.h"

typedef bool (*Q03PushSignature)(Q03Stack *, int);
typedef bool (*Q03PopSignature)(Q03Stack *, int *);
typedef bool (*Q03StackPredicateSignature)(const Q03Stack *);
typedef bool (*Q03EnqueueSignature)(Q03Queue *, int);
typedef bool (*Q03DequeueSignature)(Q03Queue *, int *);
typedef bool (*Q03QueuePredicateSignature)(const Q03Queue *);

_Static_assert(_Generic(&Push, Q03PushSignature: 1, default: 0), "Push C17 signature");
_Static_assert(_Generic(&Pop, Q03PopSignature: 1, default: 0), "Pop C17 signature");
_Static_assert(_Generic(&StackEmpty, Q03StackPredicateSignature: 1, default: 0), "StackEmpty C17 signature");
_Static_assert(_Generic(&StackOverflow, Q03StackPredicateSignature: 1, default: 0), "StackOverflow C17 signature");
_Static_assert(_Generic(&Enqueue, Q03EnqueueSignature: 1, default: 0), "Enqueue C17 signature");
_Static_assert(_Generic(&Dequeue, Q03DequeueSignature: 1, default: 0), "Dequeue C17 signature");
_Static_assert(_Generic(&QueueEmpty, Q03QueuePredicateSignature: 1, default: 0), "QueueEmpty C17 signature");

// 功能：编译期检查题目给定的栈/队列操作接口具备明确的 C17 类型。
DS_TEST_FUNCTION(provided_stack_queue_interfaces) {
    DS_CHECK(sizeof(Q03Stack *) == sizeof(void *));
    DS_CHECK(sizeof(Q03Queue *) == sizeof(void *));
}

DS_TEST_FUNCTION(q05_recursive_expression) {
    DS_CHECK(Q05RecursiveExpression() == 4);
}

DS_TEST_FUNCTION(q06_recursive_calls) {
    DS_CHECK(Q06RecursiveCallCount(0) == 1);
    DS_CHECK(Q06RecursiveCallCount(8) == 9);
    DS_CHECK(Q06RecursiveCallCount(87) == 1402817465);
    DS_CHECK(Q06RecursiveCallCount(88) == -1);
}

DS_TEST_FUNCTION(q07_recursive_order) {
    DS_CHECK(Q07FourthRecursiveCall() == 4);
}

DS_TEST_FUNCTION(q15_recursive_sum) {
    DS_CHECK(Q15RecursiveSum(0) == 20);
    DS_CHECK(Q15RecursiveSum(-2) == 20);
    DS_CHECK(Q15RecursiveSum(3) == 26);
    DS_CHECK(Q15RecursiveSum(65535) == 2147450900);
    DS_CHECK(Q15RecursiveSum(65536) == -1);
}

int main(int argc, char **argv) {
    static const DsTestCase cases[] = {
        DS_TEST_CASE(provided_stack_queue_interfaces),
        DS_TEST_CASE(q05_recursive_expression),
        DS_TEST_CASE(q06_recursive_calls),
        DS_TEST_CASE(q07_recursive_order),
        DS_TEST_CASE(q15_recursive_sum),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
