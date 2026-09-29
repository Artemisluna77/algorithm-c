#include "binary_tree.h"
#include "disjoint_set.h"
#include "problem_types.h"
#include "test_harness.h"
#include "threaded_tree.h"
#include "tree_forest.h"
#include "tree_solutions.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void SampleTree(BinaryNode nodes[6]) {
    nodes[0] = (BinaryNode){1, &nodes[1], &nodes[2]};
    nodes[1] = (BinaryNode){2, &nodes[3], &nodes[4]};
    nodes[2] = (BinaryNode){3, &nodes[5], NULL};
    nodes[3] = (BinaryNode){4, NULL, NULL};
    nodes[4] = (BinaryNode){5, NULL, NULL};
    nodes[5] = (BinaryNode){6, NULL, NULL};
}

static int IntArrayEquals(const IntArray *actual, const int *expected,
                          size_t expected_length) {
    return actual != NULL && actual->ok && actual->length == expected_length &&
           (expected_length == 0 ||
            (actual->data != NULL &&
             memcmp(actual->data, expected, expected_length * sizeof(int)) == 0));
}

static BinaryNode *NewNode(int data) {
    BinaryNode *node = (BinaryNode *)malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static int SameGeneralTree(const GeneralTreeNode *first,
                           const GeneralTreeNode *second) {
    size_t i;
    if (first == NULL || second == NULL) {
        return first == NULL && second == NULL;
    }
    if (first->data != second->data || first->child_count != second->child_count) {
        return 0;
    }
    for (i = 0; i < first->child_count; ++i) {
        if (!SameGeneralTree(first->children[i], second->children[i])) {
            return 0;
        }
    }
    return 1;
}

DS_TEST_FUNCTION(question_types) {
    ExpressionNode leaf = {{0}, NULL, NULL};
    ExpressionNode root = {{0}, &leaf, NULL};
    SequentialTree tree = {{0}, 0};
    ParentTree parent_tree = {{{0, 0}}, 0};
    leaf.data[0] = 'x';
    root.data[0] = '+';
    DS_CHECK(root.data[0] == '+');
    DS_CHECK(root.left->data[0] == 'x');
    DS_CHECK(root.right == NULL);

    tree.nodes[0] = 7;
    tree.nodes[1] = 4;
    tree.elementCount = 2;
    DS_CHECK(tree.nodes[0] == 7);
    DS_CHECK(tree.elementCount == 2);

    parent_tree.nodes[0] = (ParentTreeNode){10, -1};
    parent_tree.nodes[1] = (ParentTreeNode){5, 0};
    parent_tree.count = 2;
    DS_CHECK(parent_tree.nodes[1].parent == 0);
    DS_CHECK(parent_tree.count == 2);
}

DS_TEST_FUNCTION(traversals) {
    BinaryNode nodes[6] = {{0}};
    const int preorder[] = {1, 2, 4, 5, 3, 6};
    const int inorder[] = {4, 2, 5, 1, 6, 3};
    const int postorder[] = {4, 5, 2, 6, 3, 1};
    const int levelorder[] = {1, 2, 3, 4, 5, 6};
    IntArray values;
    SampleTree(nodes);
    values = PreOrder(&nodes[0]);
    DS_CHECK(IntArrayEquals(&values, preorder, 6));
    IntArrayDestroy(&values);
    values = InOrder(&nodes[0]);
    DS_CHECK(IntArrayEquals(&values, inorder, 6));
    IntArrayDestroy(&values);
    values = PostOrder(&nodes[0]);
    DS_CHECK(IntArrayEquals(&values, postorder, 6));
    IntArrayDestroy(&values);
    values = LevelOrder(&nodes[0]);
    DS_CHECK(IntArrayEquals(&values, levelorder, 6));
    IntArrayDestroy(&values);
}

DS_TEST_FUNCTION(traversal_boundaries) {
    BinaryNode only = {9, NULL, NULL};
    IntArray values = PreOrder(NULL);
    DS_CHECK(values.ok && values.length == 0);
    IntArrayDestroy(&values);
    values = InOrder(NULL);
    DS_CHECK(values.ok && values.length == 0);
    IntArrayDestroy(&values);
    values = PostOrder(NULL);
    DS_CHECK(values.ok && values.length == 0);
    IntArrayDestroy(&values);
    values = LevelOrder(NULL);
    DS_CHECK(values.ok && values.length == 0);
    IntArrayDestroy(&values);
    values = PreOrder(&only);
    DS_CHECK(IntArrayEquals(&values, (int[]){9}, 1));
    IntArrayDestroy(&values);
    values = LevelOrder(&only);
    DS_CHECK(IntArrayEquals(&values, (int[]){9}, 1));
    IntArrayDestroy(&values);
}

DS_TEST_FUNCTION(threaded_tree) {
    ThreadNode b = {'B', NULL, NULL, 0, 0};
    ThreadNode a = {'A', NULL, NULL, 0, 0};
    ThreadNode d = {'D', NULL, NULL, 0, 0};
    ThreadNode c = {'C', NULL, NULL, 0, 0};
    ThreadNode e = {'E', NULL, NULL, 0, 0};
    ThreadNode isolated = {'X', NULL, NULL, 0, 0};
    ThreadNode *predecessor = NULL;
    char *ordered;
    b.left = &a;
    b.right = &d;
    d.left = &c;
    d.right = &e;
    CreateInThread(&b);
    DS_CHECK(FirstNode(&b) == &a);
    DS_CHECK(NextNode(&a) == &b);
    DS_CHECK(NextNode(&b) == &c);
    DS_CHECK(NextNode(&c) == &d);
    DS_CHECK(NextNode(&d) == &e);
    DS_CHECK(NextNode(&e) == NULL);
    ordered = ThreadedInOrder(&b);
    DS_CHECK(ordered != NULL && strcmp(ordered, "ABCDE") == 0);
    free(ordered);
    DS_CHECK(FirstNode(NULL) == NULL);
    DS_CHECK(NextNode(NULL) == NULL);
    ordered = ThreadedInOrder(NULL);
    DS_CHECK(ordered != NULL && strcmp(ordered, "") == 0);
    free(ordered);
    CreateInThread(NULL);

    InThread(&isolated, &predecessor);
    DS_CHECK(predecessor == &isolated);
    DS_CHECK(isolated.leftTag == 1);
}

DS_TEST_FUNCTION(binary_tree_answers) {
    BinaryNode nodes[6] = {{0}};
    BinaryNode one = {1, NULL, NULL};
    BinaryNode gap_root = {1, NULL, NULL};
    BinaryNode gap_right = {3, NULL, NULL};
    SampleTree(nodes);
    DS_CHECK(BinaryTreeHeightByLevel(&nodes[0]) == 3);
    DS_CHECK(BinaryTreeHeightRecursive(&nodes[0]) == 3);
    DS_CHECK(IsCompleteBinaryTree(&nodes[0]) == 1);
    DS_CHECK(CountTwoChildNodes(&nodes[0]) == 2);
    DS_CHECK(BinaryTreeHeightByLevel(NULL) == 0);
    DS_CHECK(BinaryTreeHeightRecursive(NULL) == 0);
    DS_CHECK(IsCompleteBinaryTree(NULL) == 1);
    DS_CHECK(CountTwoChildNodes(NULL) == 0);
    DS_CHECK(BinaryTreeHeightByLevel(&one) == 1);
    DS_CHECK(BinaryTreeHeightRecursive(&one) == 1);
    gap_root.right = &gap_right;
    DS_CHECK(IsCompleteBinaryTree(&gap_root) == 0);
}

DS_TEST_FUNCTION(binary_tree_edges) {
    BinaryNode nodes[6] = {{0}};
    int value = -1;
    BinaryNode *null_root = NULL;
    BinaryNode leaf = {42, NULL, NULL};
    BinaryNode mirror_nodes[6] = {{0}};
    IntArray values;
    SampleTree(nodes);
    DS_CHECK(KthPreorderValue(&nodes[0], 1, &value) && value == 1);
    DS_CHECK(KthPreorderValue(&nodes[0], 6, &value) && value == 6);
    DS_CHECK(!KthPreorderValue(&nodes[0], 0, &value));
    DS_CHECK(!KthPreorderValue(&nodes[0], 7, &value));
    DS_CHECK(!KthPreorderValue(NULL, 1, &value));
    MirrorBinaryTree(null_root);
    MirrorBinaryTree(&leaf);
    DS_CHECK(leaf.data == 42);

    SampleTree(mirror_nodes);
    MirrorBinaryTree(&mirror_nodes[0]);
    DS_CHECK(mirror_nodes[0].left->data == 3);
    DS_CHECK(mirror_nodes[0].left->right->data == 6);
    DS_CHECK(mirror_nodes[0].right->data == 2);
    DS_CHECK(mirror_nodes[0].right->left->data == 5);
    DS_CHECK(mirror_nodes[0].right->right->data == 4);
    MirrorBinaryTree(&mirror_nodes[0]);
    values = PreOrder(&mirror_nodes[0]);
    DS_CHECK(IntArrayEquals(&values, (int[]){1, 2, 4, 5, 3, 6}, 6));
    IntArrayDestroy(&values);
}

DS_TEST_FUNCTION(deletion) {
    BinaryNode *root = NewNode(1);
    BinaryNode *matching_root;
    if (root == NULL) {
        DS_CHECK(0);
        return;
    }
    root->left = NewNode(2);
    root->right = NewNode(3);
    if (root->left == NULL || root->right == NULL) {
        DeleteSubtree(&root);
        DS_CHECK(0);
        return;
    }
    root->left->left = NewNode(7);
    root->right->right = NewNode(7);
    if (root->left->left == NULL || root->right->right == NULL) {
        DeleteSubtree(&root);
        DS_CHECK(0);
        return;
    }
    root->left->left->right = NewNode(8);
    DS_CHECK(DeleteSubtreesWithValue(&root, 7));
    DS_CHECK(root != NULL);
    DS_CHECK(root->left->left == NULL);
    DS_CHECK(root->right->right == NULL);
    DS_CHECK(DeleteSubtreesWithValue(&root, 99));
    DS_CHECK(root->left->data == 2);
    DeleteSubtree(&root);
    DS_CHECK(root == NULL);
    DS_CHECK(DeleteSubtreesWithValue(&root, 1));

    matching_root = NewNode(5);
    if (matching_root == NULL) {
        DS_CHECK(0);
        return;
    }
    matching_root->left = NewNode(6);
    DS_CHECK(matching_root->left != NULL);
    DS_CHECK(DeleteSubtreesWithValue(&matching_root, 5));
    DS_CHECK(matching_root == NULL);
}

DS_TEST_FUNCTION(ancestor_lca) {
    BinaryNode nodes[6] = {{0}};
    BinaryNode outside = {7, NULL, NULL};
    IntArray ancestors;
    SampleTree(nodes);
    ancestors = AncestorsOfValue(&nodes[0], 6);
    DS_CHECK(IntArrayEquals(&ancestors, (int[]){1, 3}, 2));
    IntArrayDestroy(&ancestors);
    ancestors = AncestorsOfValue(&nodes[0], 1);
    DS_CHECK(ancestors.ok && ancestors.length == 0);
    IntArrayDestroy(&ancestors);
    ancestors = AncestorsOfValue(&nodes[0], 99);
    DS_CHECK(ancestors.ok && ancestors.length == 0);
    IntArrayDestroy(&ancestors);
    DS_CHECK(LowestCommonAncestor(&nodes[0], &nodes[3], &nodes[4]) == &nodes[1]);
    DS_CHECK(LowestCommonAncestor(&nodes[0], &nodes[3], &nodes[5]) == &nodes[0]);
    DS_CHECK(LowestCommonAncestor(&nodes[0], &nodes[3], &nodes[3]) == &nodes[3]);
    DS_CHECK(LowestCommonAncestor(&nodes[0], &nodes[3], &outside) == NULL);
    DS_CHECK(LowestCommonAncestor(&nodes[0], NULL, &nodes[3]) == NULL);
}

DS_TEST_FUNCTION(sequential_lca) {
    SequentialTree tree = {{0}, 7};
    SequentialTree sparse = {{0}, 4};
    int value = -1;
    const int values[] = {10, 5, 15, 2, 7, 12, 18};
    const int sparse_values[] = {10, SEQUENTIAL_TREE_EMPTY_NODE, 15, 20};
    memcpy(tree.nodes, values, sizeof(values));
    memcpy(sparse.nodes, sparse_values, sizeof(sparse_values));
    DS_CHECK(SequentialLowestCommonAncestor(&tree, 3, 4, &value) && value == 5);
    DS_CHECK(SequentialLowestCommonAncestor(&tree, 1, 4, &value) && value == 5);
    DS_CHECK(SequentialLowestCommonAncestor(&tree, 3, 6, &value) && value == 10);
    DS_CHECK(SequentialLowestCommonAncestor(&tree, 0, 6, &value) && value == 10);
    DS_CHECK(SequentialLowestCommonAncestor(&tree, 2, 2, &value) && value == 15);
    DS_CHECK(!SequentialLowestCommonAncestor(&tree, 3, 7, &value));
    DS_CHECK(!SequentialLowestCommonAncestor(&sparse, 0, 2, &value));
}

DS_TEST_FUNCTION(width) {
    BinaryNode nodes[6] = {{0}};
    BinaryNode leaf = {3, NULL, NULL};
    SampleTree(nodes);
    DS_CHECK(BinaryTreeWidth(&nodes[0]) == 3);
    DS_CHECK(BinaryTreeWidth(NULL) == 0);
    DS_CHECK(BinaryTreeWidth(&leaf) == 1);
}

DS_TEST_FUNCTION(full_tree_conversion) {
    const int expected[] = {'C', 'D', 'B', 'F', 'G', 'E', 'A'};
    const int one[] = {1};
    const int even[] = {1, 2};
    IntArray converted = PreorderToPostorderExample();
    DS_CHECK(IntArrayEquals(&converted, expected, 7));
    IntArrayDestroy(&converted);
    converted = FullTreePreorderToPostorder(one, 1);
    DS_CHECK(IntArrayEquals(&converted, one, 1));
    IntArrayDestroy(&converted);
    converted = FullTreePreorderToPostorder(NULL, 0);
    DS_CHECK(converted.ok && converted.length == 0);
    IntArrayDestroy(&converted);
    converted = FullTreePreorderToPostorder(even, 2);
    DS_CHECK(!converted.ok);
    IntArrayDestroy(&converted);
}

DS_TEST_FUNCTION(leaf_list) {
    BinaryNode root = {1, NULL, NULL};
    BinaryNode left = {2, NULL, NULL};
    BinaryNode right = {3, NULL, NULL};
    BinaryNode a = {4, NULL, NULL};
    BinaryNode b = {5, NULL, NULL};
    BinaryNode c = {6, NULL, NULL};
    BinaryNode d = {7, NULL, NULL};
    BinaryNode only = {8, NULL, NULL};
    BinaryNode *head;
    root.left = &left;
    root.right = &right;
    left.left = &a;
    left.right = &b;
    right.left = &c;
    right.right = &d;
    head = LinkLeavesInorder(&root);
    DS_CHECK(head == &a);
    DS_CHECK(head->right == &b);
    DS_CHECK(head->right->right == &c);
    DS_CHECK(head->right->right->right == &d);
    DS_CHECK(head->right->right->right->right == NULL);
    DS_CHECK(LinkLeavesInorder(NULL) == NULL);
    DS_CHECK(LinkLeavesInorder(&only) == &only);
    DS_CHECK(only.right == NULL);
}

DS_TEST_FUNCTION(similarity) {
    BinaryNode first = {1, NULL, NULL};
    BinaryNode first_left = {2, NULL, NULL};
    BinaryNode first_right = {3, NULL, NULL};
    BinaryNode second = {99, NULL, NULL};
    BinaryNode second_left = {88, NULL, NULL};
    BinaryNode second_right = {77, NULL, NULL};
    BinaryNode right_only = {1, NULL, NULL};
    first.left = &first_left;
    first.right = &first_right;
    second.left = &second_left;
    second.right = &second_right;
    right_only.right = &second_left;
    DS_CHECK(AreStructurallySimilar(&first, &second));
    DS_CHECK(AreStructurallySimilar(NULL, NULL));
    DS_CHECK(!AreStructurallySimilar(&first, NULL));
    DS_CHECK(!AreStructurallySimilar(&first, &right_only));
}

DS_TEST_FUNCTION(weighted_path) {
    WeightedNode root = {0, NULL, NULL};
    WeightedNode left = {3, NULL, NULL};
    WeightedNode right = {0, NULL, NULL};
    WeightedNode right_left = {2, NULL, NULL};
    WeightedNode right_right = {1, NULL, NULL};
    WeightedNode leaf = {9, NULL, NULL};
    WeightedNode overflow_root = {123, NULL, NULL};
    WeightedNode overflow_left = {INT_MAX, NULL, NULL};
    WeightedNode overflow_right = {1, NULL, NULL};
    int64_t result = -1;
    root.left = &left;
    root.right = &right;
    right.left = &right_left;
    right.right = &right_right;
    DS_CHECK(WeightedPathLength(&root, &result) && result == 9);
    DS_CHECK(WeightedPathLengthPostorder(&root, &result) && result == 9);
    DS_CHECK(root.weight == 6);
    DS_CHECK(right.weight == 3);
    DS_CHECK(WeightedPathLength(NULL, &result) && result == 0);
    DS_CHECK(WeightedPathLengthPostorder(NULL, &result) && result == 0);
    DS_CHECK(WeightedPathLength(&leaf, &result) && result == 0);
    DS_CHECK(WeightedPathLengthPostorder(&leaf, &result) && result == 0);
    overflow_root.left = &overflow_left;
    overflow_root.right = &overflow_right;
    DS_CHECK(!WeightedPathLengthPostorder(&overflow_root, &result));
    DS_CHECK(overflow_root.weight == 123);
}

DS_TEST_FUNCTION(expression_tree) {
    ExpressionNode a = {{0}, NULL, NULL};
    ExpressionNode b = {{0}, NULL, NULL};
    ExpressionNode c = {{0}, NULL, NULL};
    ExpressionNode multiply = {{0}, NULL, NULL};
    ExpressionNode add = {{0}, NULL, NULL};
    ExpressionNode plus = {{0}, NULL, NULL};
    ExpressionNode multiply_root = {{0}, NULL, NULL};
    char *expression;
    a.data[0] = 'a';
    b.data[0] = 'b';
    c.data[0] = 'c';
    multiply.data[0] = '*';
    multiply.left = &b;
    multiply.right = &c;
    add.data[0] = '+';
    add.left = &a;
    add.right = &multiply;
    expression = ExpressionToInfix(&add);
    DS_CHECK(expression != NULL && strcmp(expression, "a+(b*c)") == 0);
    free(expression);

    plus.data[0] = '+';
    plus.left = &a;
    plus.right = &b;
    multiply_root.data[0] = '*';
    multiply_root.left = &plus;
    multiply_root.right = &c;
    expression = ExpressionToInfix(&multiply_root);
    DS_CHECK(expression != NULL && strcmp(expression, "(a+b)*c") == 0);
    free(expression);
    expression = ExpressionToInfix(&a);
    DS_CHECK(expression != NULL && strcmp(expression, "a") == 0);
    free(expression);
    expression = ExpressionToInfix(NULL);
    DS_CHECK(expression != NULL && strcmp(expression, "") == 0);
    free(expression);
}

DS_TEST_FUNCTION(sequential_bst) {
    SequentialTree valid = {{0}, 7};
    SequentialTree violation = {{0}, 5};
    SequentialTree duplicate = {{0}, 2};
    SequentialTree malformed = {{0}, 4};
    SequentialTree empty = {{0}, 0};
    const int valid_values[] = {8, 4, 12, 2, 6, 10, 14};
    const int violation_values[] = {10, 5, 15, SEQUENTIAL_TREE_EMPTY_NODE, 12};
    const int duplicate_values[] = {10, 10};
    const int malformed_values[] = {10, SEQUENTIAL_TREE_EMPTY_NODE, 14, 20};
    memcpy(valid.nodes, valid_values, sizeof(valid_values));
    memcpy(violation.nodes, violation_values, sizeof(violation_values));
    memcpy(duplicate.nodes, duplicate_values, sizeof(duplicate_values));
    memcpy(malformed.nodes, malformed_values, sizeof(malformed_values));
    DS_CHECK(IsBinarySearchTreeInorder(&valid));
    DS_CHECK(IsBinarySearchTreeBySubtreeBounds(&valid));
    DS_CHECK(!IsBinarySearchTreeInorder(&violation));
    DS_CHECK(!IsBinarySearchTreeBySubtreeBounds(&violation));
    DS_CHECK(!IsBinarySearchTreeInorder(&duplicate));
    DS_CHECK(!IsBinarySearchTreeBySubtreeBounds(&duplicate));
    DS_CHECK(!IsBinarySearchTreeInorder(&malformed));
    DS_CHECK(!IsBinarySearchTreeBySubtreeBounds(&malformed));
    DS_CHECK(IsBinarySearchTreeInorder(&empty));
    DS_CHECK(IsBinarySearchTreeBySubtreeBounds(&empty));
}

DS_TEST_FUNCTION(tree_forest_roundtrip) {
    GeneralTreeNode n4 = {4, NULL, 0};
    GeneralTreeNode n5 = {5, NULL, 0};
    GeneralTreeNode n6 = {6, NULL, 0};
    GeneralTreeNode *n2_children[] = {&n4, &n5};
    GeneralTreeNode *n3_children[] = {&n6};
    GeneralTreeNode n2 = {2, n2_children, 2};
    GeneralTreeNode n3 = {3, n3_children, 1};
    GeneralTreeNode *root_children[] = {&n2, &n3};
    GeneralTreeNode source = {1, root_children, 2};
    GeneralTreeNode empty_source = {9, NULL, 0};
    ChildSiblingNode *encoded = TreeToChildSibling(&source);
    GeneralTreeNode *decoded = ChildSiblingToTree(encoded);
    ChildSiblingNode *empty = TreeToChildSibling(&empty_source);
    GeneralTreeNode *empty_decoded;
    DS_CHECK(decoded != NULL);
    DS_CHECK(SameGeneralTree(&source, decoded));
    DS_CHECK(CountLeaves(encoded) == 3);
    DS_CHECK(ChildSiblingHeight(encoded) == 3);
    DestroyGeneralTree(decoded);
    DestroyChildSibling(encoded);
    DS_CHECK(CountLeaves(empty) == 1);
    DS_CHECK(ChildSiblingHeight(empty) == 1);
    empty_decoded = ChildSiblingToTree(NULL);
    DS_CHECK(empty_decoded == NULL);
    DestroyChildSibling(empty);
    DestroyGeneralTree(empty_decoded);
}

DS_TEST_FUNCTION(forest_algorithms) {
    ChildSiblingNode root = {1, NULL, NULL};
    ChildSiblingNode child = {2, NULL, NULL};
    ChildSiblingNode child_sibling = {3, NULL, NULL};
    ChildSiblingNode grandchild = {4, NULL, NULL};
    ChildSiblingNode forest_sibling = {5, NULL, NULL};
    root.firstChild = &child;
    child.nextSibling = &child_sibling;
    child.firstChild = &grandchild;
    root.nextSibling = &forest_sibling;
    DS_CHECK(CountLeaves(&root) == 3);
    DS_CHECK(ChildSiblingHeight(&root) == 3);
    DS_CHECK(CountLeaves(NULL) == 0);
    DS_CHECK(ChildSiblingHeight(NULL) == 0);
}

DS_TEST_FUNCTION(disjoint_set_operations) {
    DisjointSet sets = {0, NULL};
    int root;
    int root4;
    DS_CHECK(DisjointSetInit(&sets, 6));
    DS_CHECK(DisjointSetSize(&sets) == 6);
    DS_CHECK(FindWithoutCompression(&sets, 0, &root) && root == 0);
    DS_CHECK(FindWithoutCompression(&sets, 1, &root) && root == 1);
    DS_CHECK(FindWithoutCompression(&sets, 2, &root) && root == 2);
    DS_CHECK(FindWithoutCompression(&sets, 3, &root) && root == 3);
    DS_CHECK(FindWithoutCompression(&sets, 4, &root) && root == 4);
    DS_CHECK(FindWithoutCompression(&sets, 5, &root) && root == 5);
    DS_CHECK(UnionRoots(&sets, 0, 1));
    DS_CHECK(!UnionRoots(&sets, 0, 1));
    DS_CHECK(FindWithoutCompression(&sets, 1, &root) && root == 0);
    DS_CHECK(UnionBySize(&sets, 2, 3));
    DS_CHECK(Union(&sets, 1, 2));
    DS_CHECK(Find(&sets, 3, &root) && root == 0);
    DS_CHECK(FindWithoutCompression(&sets, 3, &root) && root == 0);
    DS_CHECK(Union(&sets, 4, 5));
    DS_CHECK(Find(&sets, 5, &root) && Find(&sets, 4, &root4) && root == root4);
    Initialize(&sets);
    DS_CHECK(Find(&sets, 1, &root) && root == 1);
    DS_CHECK(Find(&sets, 3, &root) && root == 3);
    DisjointSetDestroy(&sets);
}

DS_TEST_FUNCTION(disjoint_set_boundaries) {
    DisjointSet empty = {0, NULL};
    DisjointSet sets = {0, NULL};
    int root;
    DS_CHECK(DisjointSetInit(&empty, 0));
    DS_CHECK(DisjointSetSize(&empty) == 0);
    DS_CHECK(!Find(&empty, 0, &root));
    DS_CHECK(!Find(NULL, 0, &root));
    DisjointSetDestroy(&empty);
    DS_CHECK(DisjointSetInit(&sets, 2));
    DS_CHECK(!UnionRoots(&sets, 0, 0));
    DS_CHECK(UnionRoots(&sets, 0, 1));
    DS_CHECK(!UnionBySize(&sets, 1, 0));
    DS_CHECK(!Union(&sets, 0, 2));
    DS_CHECK(!DisjointSetInit(&sets, (size_t)INT_MAX + 1));
    DS_CHECK(DisjointSetSize(&sets) == 2);
    DS_CHECK(FindWithoutCompression(&sets, 1, &root) && root == 0);
    DS_CHECK(DisjointSetInit(&sets, 0));
    DS_CHECK(DisjointSetSize(&sets) == 0 && sets.parent_or_size == NULL);
    DisjointSetDestroy(&sets);
}

typedef struct VisitBuffer {
    int values[8];
    size_t length;
} VisitBuffer;

static void SaveVisit(int value, void *context) {
    VisitBuffer *buffer = (VisitBuffer *)context;
    if (buffer->length < sizeof(buffer->values) / sizeof(buffer->values[0])) {
        buffer->values[buffer->length++] = value;
    }
}

DS_TEST_FUNCTION(generic_traversal) {
    BinaryNode nodes[6] = {{0}};
    VisitBuffer visited = {{0}, 0};
    const int preorder[] = {1, 2, 4, 5, 3, 6};
    const int inorder[] = {4, 2, 5, 1, 6, 3};
    const int postorder[] = {4, 5, 2, 6, 3, 1};
    SampleTree(nodes);
    Track(&nodes[0], Preorder, SaveVisit, &visited);
    DS_CHECK(visited.length == 6 && memcmp(visited.values, preorder, sizeof(preorder)) == 0);
    visited.length = 0;
    Track(&nodes[0], Inorder, SaveVisit, &visited);
    DS_CHECK(visited.length == 6 && memcmp(visited.values, inorder, sizeof(inorder)) == 0);
    visited.length = 0;
    Track(&nodes[0], Postorder, SaveVisit, &visited);
    DS_CHECK(visited.length == 6 && memcmp(visited.values, postorder, sizeof(postorder)) == 0);
    visited.length = 0;
    Track(NULL, Inorder, SaveVisit, &visited);
    DS_CHECK(visited.length == 0);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(question_types),
        DS_TEST_CASE(traversals),
        DS_TEST_CASE(traversal_boundaries),
        DS_TEST_CASE(threaded_tree),
        DS_TEST_CASE(binary_tree_answers),
        DS_TEST_CASE(binary_tree_edges),
        DS_TEST_CASE(deletion),
        DS_TEST_CASE(ancestor_lca),
        DS_TEST_CASE(sequential_lca),
        DS_TEST_CASE(width),
        DS_TEST_CASE(full_tree_conversion),
        DS_TEST_CASE(leaf_list),
        DS_TEST_CASE(similarity),
        DS_TEST_CASE(weighted_path),
        DS_TEST_CASE(expression_tree),
        DS_TEST_CASE(sequential_bst),
        DS_TEST_CASE(tree_forest_roundtrip),
        DS_TEST_CASE(forest_algorithms),
        DS_TEST_CASE(disjoint_set_operations),
        DS_TEST_CASE(disjoint_set_boundaries),
        DS_TEST_CASE(generic_traversal),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
