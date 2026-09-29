#include "sequential_list.h"
#include "test_harness.h"

#include <stddef.h>

DS_TEST_FUNCTION(init_static) {
    SeqList list = {0};
    list.length = 7;
    SeqListInit(&list);
    DS_CHECK(list.length == 0);
}

DS_TEST_FUNCTION(init_dynamic) {
    DynamicSeqList list = {0};
    DS_CHECK(InitDynamicList(&list, 8));
    DS_CHECK(list.data != NULL);
    DS_CHECK(list.MaxSize == 8);
    DS_CHECK(list.length == 0);
    DS_CHECK(InitDynamicList(&list, 0));
    DS_CHECK(list.data == NULL);
    DS_CHECK(list.MaxSize == 0);
    DynamicSeqListDestroy(&list);
}

DS_TEST_FUNCTION(allocation_examples) {
    DynamicSeqList malloc_example = {0};
    DynamicSeqList new_example = {0};
    DS_CHECK(InitDynamicListFromMallocExample(&malloc_example, 5));
    DS_CHECK(malloc_example.data != NULL);
    DS_CHECK(malloc_example.MaxSize == 5);
    DS_CHECK(malloc_example.length == 0);
    DS_CHECK(InitDynamicListFromNewExample(&new_example, 6));
    DS_CHECK(new_example.data != NULL);
    DS_CHECK(new_example.MaxSize == 6);
    DS_CHECK(new_example.length == 0);
    DynamicSeqListDestroy(&malloc_example);
    DynamicSeqListDestroy(&new_example);
}

DS_TEST_FUNCTION(insert_positions) {
    SeqList list = {0};
    SeqListInit(&list);
    DS_CHECK(SeqListInsert(&list, 1, 20));
    DS_CHECK(SeqListInsert(&list, 1, 10));
    DS_CHECK(SeqListInsert(&list, 3, 30));
    DS_CHECK(list.length == 3);
    DS_CHECK(list.data[0] == 10 && list.data[1] == 20 && list.data[2] == 30);
}

DS_TEST_FUNCTION(insert_boundaries) {
    SeqList list = {0};
    size_t i;
    SeqListInit(&list);
    DS_CHECK(!SeqListInsert(&list, 0, 1));
    DS_CHECK(!SeqListInsert(&list, 2, 1));
    DS_CHECK(list.length == 0);
    for (i = 1; i <= SEQ_LIST_MAX_SIZE; ++i) DS_CHECK(SeqListInsert(&list, i, (int)i));
    DS_CHECK(!SeqListInsert(&list, SEQ_LIST_MAX_SIZE + 1, 999));
    DS_CHECK(list.length == SEQ_LIST_MAX_SIZE);
    DS_CHECK(list.data[SEQ_LIST_MAX_SIZE - 1] == (int)SEQ_LIST_MAX_SIZE);
}

DS_TEST_FUNCTION(delete_positions) {
    SeqList list = {0};
    int removed = -1;
    SeqListInit(&list);
    DS_CHECK(SeqListInsert(&list, 1, 10));
    DS_CHECK(SeqListInsert(&list, 2, 20));
    DS_CHECK(SeqListInsert(&list, 3, 30));
    DS_CHECK(SeqListDelete(&list, 1, &removed) && removed == 10);
    DS_CHECK(SeqListDelete(&list, 2, &removed) && removed == 30);
    DS_CHECK(SeqListDelete(&list, 1, &removed) && removed == 20);
    DS_CHECK(list.length == 0);
}

DS_TEST_FUNCTION(delete_boundaries) {
    SeqList list = {0};
    int removed = 77;
    SeqListInit(&list);
    DS_CHECK(!SeqListDelete(&list, 1, &removed));
    DS_CHECK(removed == 77);
    DS_CHECK(SeqListInsert(&list, 1, 10));
    DS_CHECK(!SeqListDelete(&list, 0, &removed));
    DS_CHECK(!SeqListDelete(&list, 2, &removed));
    DS_CHECK(list.length == 1);
}

DS_TEST_FUNCTION(locate) {
    SeqList list = {0};
    SeqList empty = {0};
    SeqListInit(&list);
    DS_CHECK(SeqListInsert(&list, 1, 7));
    DS_CHECK(SeqListInsert(&list, 2, 9));
    DS_CHECK(SeqListInsert(&list, 3, 7));
    DS_CHECK(SeqListLocate(&list, 7) == 1);
    DS_CHECK(SeqListLocate(&list, 9) == 2);
    DS_CHECK(SeqListLocate(&list, 11) == 0);
    SeqListInit(&empty);
    DS_CHECK(SeqListLocate(&empty, 7) == 0);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(init_static), DS_TEST_CASE(init_dynamic),
        DS_TEST_CASE(allocation_examples), DS_TEST_CASE(insert_positions),
        DS_TEST_CASE(insert_boundaries), DS_TEST_CASE(delete_positions),
        DS_TEST_CASE(delete_boundaries), DS_TEST_CASE(locate),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
