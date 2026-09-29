#include "linked_lists.h"
#include "q20_node.h"
#include "test_harness.h"

static int expect_list(const SinglyLinkedList *list, const int *expected, size_t length) {
    size_t i = 0;
    LNode *node = SinglyLinkedListFirst(list);
    while (node != NULL && i < length) {
        if (node->data != expected[i]) return 0;
        ++i;
        node = node->next;
    }
    return node == NULL && i == length;
}

DS_TEST_FUNCTION(init_list_forms) {
    SinglyLinkedList list = {0};
    DS_CHECK(SinglyLinkedListInit(&list, false));
    DS_CHECK(!list.with_header && list.head == NULL);
    DS_CHECK(SinglyLinkedListLength(&list) == 0);
    DS_CHECK(SinglyLinkedListAppend(&list, 9));
    DS_CHECK(SinglyLinkedListLength(&list) == 1);
    SinglyLinkedListDestroy(&list);
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(list.with_header && list.head != NULL && list.head->next == NULL);
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(length) {
    SinglyLinkedList list = {0};
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(SinglyLinkedListLength(&list) == 0);
    DS_CHECK(SinglyLinkedListAppend(&list, 3));
    DS_CHECK(SinglyLinkedListAppend(&list, 5));
    DS_CHECK(SinglyLinkedListAppend(&list, 8));
    DS_CHECK(SinglyLinkedListLength(&list) == 3);
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(get_by_index) {
    SinglyLinkedList list = {0};
    SinglyLinkedList without_header = {0};
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(SinglyLinkedListAppend(&list, 10));
    DS_CHECK(SinglyLinkedListAppend(&list, 20));
    DS_CHECK(GetElem(&list, 0) == list.head);
    DS_CHECK(GetElem(&list, 1)->data == 10);
    DS_CHECK(GetElem(&list, 2)->data == 20);
    DS_CHECK(GetElem(&list, 3) == NULL);
    DS_CHECK(SinglyLinkedListInit(&without_header, false));
    DS_CHECK(SinglyLinkedListAppend(&without_header, 30));
    DS_CHECK(SinglyLinkedListAppend(&without_header, 40));
    DS_CHECK(GetElem(&without_header, 0)->data == 30);
    DS_CHECK(GetElem(&without_header, 1)->data == 40);
    DS_CHECK(GetElem(&without_header, 2) == NULL);
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&without_header);
}

DS_TEST_FUNCTION(locate_value) {
    SinglyLinkedList list = {0};
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(LocateElemLinked(&list, 4) == NULL);
    DS_CHECK(SinglyLinkedListAppend(&list, 4));
    DS_CHECK(SinglyLinkedListAppend(&list, 7));
    DS_CHECK(SinglyLinkedListAppend(&list, 4));
    DS_CHECK(LocateElemLinked(&list, 7)->data == 7);
    DS_CHECK(LocateElemLinked(&list, 4) == list.head->next);
    DS_CHECK(LocateElemLinked(&list, 99) == NULL);
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(insert_delete) {
    const int expected[] = {10, 20, 30};
    SinglyLinkedList list = {0};
    int removed = -1;
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(LinkedListInsert(&list, 1, 20));
    DS_CHECK(LinkedListInsert(&list, 1, 10));
    DS_CHECK(LinkedListInsert(&list, 3, 30));
    DS_CHECK(expect_list(&list, expected, 3));
    DS_CHECK(LinkedListDelete(&list, 1, &removed) && removed == 10);
    DS_CHECK(LinkedListDelete(&list, 2, &removed) && removed == 30);
    DS_CHECK(LinkedListDelete(&list, 1, &removed) && removed == 20);
    DS_CHECK(SinglyLinkedListLength(&list) == 0);
    SinglyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(operation_boundaries) {
    const int expected[] = {5};
    SinglyLinkedList list = {0};
    SinglyLinkedList plain = {0};
    int removed = 42;
    DS_CHECK(SinglyLinkedListInit(&list, true));
    DS_CHECK(!LinkedListInsert(&list, 0, 5));
    DS_CHECK(!LinkedListInsert(&list, 2, 5));
    DS_CHECK(!LinkedListDelete(&list, 1, &removed));
    DS_CHECK(removed == 42);
    DS_CHECK(LinkedListInsert(&list, 1, 5));
    DS_CHECK(!LinkedListDelete(&list, 0, &removed));
    DS_CHECK(!LinkedListDelete(&list, 2, &removed));
    DS_CHECK(expect_list(&list, expected, 1));
    DS_CHECK(SinglyLinkedListInit(&plain, false));
    DS_CHECK(SinglyLinkedListAppend(&plain, 9));
    DS_CHECK(!LinkedListInsert(&plain, 1, 3));
    DS_CHECK(!LinkedListDelete(&plain, 1, &removed));
    SinglyLinkedListDestroy(&list);
    SinglyLinkedListDestroy(&plain);
}

DS_TEST_FUNCTION(build_head_tail) {
    const int input[] = {1, 2, 3, 9999, 4};
    const int reversed[] = {3, 2, 1};
    const int forward[] = {1, 2, 3};
    const int empty_input[] = {9999};
    SinglyLinkedList head = {0}, tail = {0}, empty_head = {0}, empty_tail = {0};
    DS_CHECK(List_HeadInsert(&head, input, 5, 9999));
    DS_CHECK(List_TailInsert(&tail, input, 5, 9999));
    DS_CHECK(List_HeadInsert(&empty_head, empty_input, 1, 9999));
    DS_CHECK(List_TailInsert(&empty_tail, NULL, 0, 9999));
    DS_CHECK(expect_list(&head, reversed, 3));
    DS_CHECK(expect_list(&tail, forward, 3));
    DS_CHECK(SinglyLinkedListLength(&empty_head) == 0);
    DS_CHECK(SinglyLinkedListLength(&empty_tail) == 0);
    SinglyLinkedListDestroy(&head);
    SinglyLinkedListDestroy(&tail);
    SinglyLinkedListDestroy(&empty_head);
    SinglyLinkedListDestroy(&empty_tail);
}

DS_TEST_FUNCTION(doubly_link_operations) {
    DoublyLinkedList list = {0};
    DNode *one;
    DNode *three;
    DNode *two;
    int removed = -1;
    DS_CHECK(DoublyLinkedListInit(&list));
    one = DoublyLinkedListAppend(&list, 1);
    three = DoublyLinkedListAppend(&list, 3);
    two = DoublyLinkedListInsertAfter(one, 2);
    DS_CHECK(two != NULL);
    DS_CHECK(two->prior == one && two->next == three);
    DS_CHECK(three->prior == two);
    DS_CHECK(list.head->next->data == 1 && list.head->next->next->data == 2 &&
             list.head->next->next->next->data == 3);
    DS_CHECK(DoublyLinkedListEraseAfter(one, &removed) && removed == 2);
    DS_CHECK(list.head->next->next->data == 3);
    DS_CHECK(three->prior == one);
    DS_CHECK(!DoublyLinkedListEraseAfter(three, &removed));
    DS_CHECK(DoublyLinkedListInsertAfter(NULL, 8) == NULL);
    DoublyLinkedListDestroy(&list);
}

DS_TEST_FUNCTION(static_and_question_types) {
    StaticLinkedList list = {{0, 0}};
    Question20Node node = {7, NULL};
    list[0].data = 11;
    list[0].next = 1;
    list[1].data = 22;
    list[1].next = -1;
    DS_CHECK(list[0].next == 1);
    DS_CHECK(list[1].next == -1);
    DS_CHECK(node.data == 7 && node.next == NULL);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(init_list_forms), DS_TEST_CASE(length),
        DS_TEST_CASE(get_by_index), DS_TEST_CASE(locate_value),
        DS_TEST_CASE(insert_delete), DS_TEST_CASE(operation_boundaries),
        DS_TEST_CASE(build_head_tail), DS_TEST_CASE(doubly_link_operations),
        DS_TEST_CASE(static_and_question_types),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
