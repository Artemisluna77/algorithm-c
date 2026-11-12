#include "string_matching.h"
#include "test_harness.h"

#include <string.h>

static size_t StringLength(const char *value) {
    return strlen(value);
}

static int NextEquals(const NextTable *table, const size_t *expected,
                      size_t expected_length) {
    size_t i;
    if (table == NULL || table->length != expected_length ||
        (expected_length != 0 && table->data == NULL)) {
        return 0;
    }
    for (i = 0; i < expected_length; ++i) {
        if (table->data[i] != expected[i]) {
            return 0;
        }
    }
    return 1;
}

DS_TEST_FUNCTION(storage_types) {
    StaticString fixed = {{0}, 0};
    HeapString heap = {NULL, 0};
    char maximum[STATIC_STRING_MAX_LEN];
    DS_CHECK(STATIC_STRING_MAX_LEN == 255);
    DS_CHECK(StaticStringAssign(&fixed, "a", 1));
    DS_CHECK(fixed.ch[0] == 'a');
    DS_CHECK(fixed.length == 1);
    DS_CHECK(!StaticStringAssign(&fixed, "too long", 256));
    DS_CHECK(fixed.length == 1);
    DS_CHECK(StaticStringAssign(&fixed, "abcdef", 6));
    DS_CHECK(StaticStringAssign(&fixed, fixed.ch + 1, 4));
    DS_CHECK(fixed.length == 4 && memcmp(fixed.ch, "bcde", 4) == 0);
    DS_CHECK(StaticStringAssign(&fixed, fixed.ch, fixed.length));
    DS_CHECK(fixed.length == 4 && memcmp(fixed.ch, "bcde", 4) == 0);
    memset(maximum, 'm', sizeof(maximum));
    DS_CHECK(StaticStringAssign(&fixed, maximum, sizeof(maximum)));
    DS_CHECK(fixed.length == STATIC_STRING_MAX_LEN);
    DS_CHECK(fixed.ch[STATIC_STRING_MAX_LEN - 1] == 'm');

    DS_CHECK(HeapStringAssign(&heap, "b", 1));
    DS_CHECK(heap.ch != NULL);
    DS_CHECK(heap.ch[0] == 'b');
    DS_CHECK(heap.ch[1] == '\0');
    DS_CHECK(heap.length == 1);
    DS_CHECK(HeapStringAssign(&heap, "", 0));
    DS_CHECK(heap.ch != NULL);
    DS_CHECK(heap.length == 0);
    HeapStringDestroy(&heap);
    DS_CHECK(heap.ch == NULL);
    DS_CHECK(heap.length == 0);
    HeapStringDestroy(&heap);
}

DS_TEST_FUNCTION(brute_force_match) {
    const char *text = "ababcabcacbab";
    DS_CHECK(BruteForceIndex(text, StringLength(text), "abcac", 5) == 6);
    DS_CHECK(BruteForceIndex("xxneedle", 8, "needle", 6) == 3);
    DS_CHECK(BruteForceIndex("haystack", 8, "xyz", 3) == 0);
    DS_CHECK(BruteForceIndex("", 0, "x", 1) == 0);
    DS_CHECK(BruteForceIndex("abc", 3, "", 0) == 1);
    DS_CHECK(BruteForceIndex("", 0, "", 0) == 1);
    DS_CHECK(BruteForceIndex("x", 1, "longer", 6) == 0);
    DS_CHECK(BruteForceIndex(NULL, 1, "x", 1) == 0);
}

DS_TEST_FUNCTION(kmp_next_table) {
    static const size_t abcac[] = {0, 0, 1, 1, 1, 2};
    static const size_t aaaa[] = {0, 0, 1, 2, 3};
    static const size_t empty[] = {0};
    NextTable table = BuildNext("abcac", 5);
    DS_CHECK(NextEquals(&table, abcac, sizeof(abcac) / sizeof(abcac[0])));
    NextTableDestroy(&table);
    table = BuildNext("aaaa", 4);
    DS_CHECK(NextEquals(&table, aaaa, sizeof(aaaa) / sizeof(aaaa[0])));
    NextTableDestroy(&table);
    table = BuildNext("", 0);
    DS_CHECK(NextEquals(&table, empty, sizeof(empty) / sizeof(empty[0])));
    NextTableDestroy(&table);
}

DS_TEST_FUNCTION(kmp_match) {
    NextTable next = BuildNext("abcac", 5);
    DS_CHECK(KmpIndex("ababcabcacbab", 13, "abcac", 5, &next) == 6);
    NextTableDestroy(&next);
    next = BuildNext("needle", 6);
    DS_CHECK(KmpIndex("needle", 6, "needle", 6, &next) == 1);
    DS_CHECK(KmpIndex("xxneedle", 8, "needle", 6, &next) == 3);
    NextTableDestroy(&next);
    next = BuildNext("xyz", 3);
    DS_CHECK(KmpIndex("haystack", 8, "xyz", 3, &next) == 0);
    DS_CHECK(KmpIndex("", 0, "x", 1, &next) == 0);
    NextTableDestroy(&next);
    next = BuildNext("", 0);
    DS_CHECK(KmpIndex("abc", 3, "", 0, &next) == 1);
    DS_CHECK(KmpIndex("", 0, "", 0, &next) == 1);
    DS_CHECK(KmpIndex("abc", 3, "", 0, NULL) == 0);
    NextTableDestroy(&next);
    {
        NextTable short_table = {NULL, 0};
        DS_CHECK(KmpIndex("x", 1, "x", 1, &short_table) == 0);
        DS_CHECK(KmpIndexNextVal("x", 1, "x", 1, &short_table) == 0);
    }
}

DS_TEST_FUNCTION(kmp_overlap) {
    NextTable next = BuildNext("aaa", 3);
    DS_CHECK(KmpIndex("aaaaa", 5, "aaa", 3, &next) == 1);
    NextTableDestroy(&next);
    next = BuildNext("aba", 3);
    DS_CHECK(KmpIndex("ababa", 5, "aba", 3, &next) == 1);
    NextTableDestroy(&next);
}

DS_TEST_FUNCTION(nextval_table) {
    static const size_t aaaab[] = {0, 0, 0, 0, 0, 4};
    static const size_t abcac[] = {0, 0, 1, 1, 0, 2};
    static const size_t empty[] = {0};
    NextTable table = BuildNextVal("aaaab", 5);
    DS_CHECK(NextEquals(&table, aaaab, sizeof(aaaab) / sizeof(aaaab[0])));
    NextTableDestroy(&table);
    table = BuildNextVal("abcac", 5);
    DS_CHECK(NextEquals(&table, abcac, sizeof(abcac) / sizeof(abcac[0])));
    NextTableDestroy(&table);
    table = BuildNextVal("", 0);
    DS_CHECK(NextEquals(&table, empty, sizeof(empty) / sizeof(empty[0])));
    NextTableDestroy(&table);
}

DS_TEST_FUNCTION(optimized_kmp_match) {
    NextTable nextval = BuildNextVal("abcac", 5);
    DS_CHECK(KmpIndexNextVal("ababcabcacbab", 13, "abcac", 5, &nextval) == 6);
    NextTableDestroy(&nextval);
    nextval = BuildNextVal("needle", 6);
    DS_CHECK(KmpIndexNextVal("needle", 6, "needle", 6, &nextval) == 1);
    DS_CHECK(KmpIndexNextVal("xxneedle", 8, "needle", 6, &nextval) == 3);
    NextTableDestroy(&nextval);
    nextval = BuildNextVal("xyz", 3);
    DS_CHECK(KmpIndexNextVal("haystack", 8, "xyz", 3, &nextval) == 0);
    DS_CHECK(KmpIndexNextVal("", 0, "x", 1, &nextval) == 0);
    NextTableDestroy(&nextval);
    nextval = BuildNextVal("", 0);
    DS_CHECK(KmpIndexNextVal("abc", 3, "", 0, &nextval) == 1);
    DS_CHECK(KmpIndexNextVal("", 0, "", 0, &nextval) == 1);
    NextTableDestroy(&nextval);
}

int main(int argc, char **argv) {
    const DsTestCase cases[] = {
        DS_TEST_CASE(storage_types),
        DS_TEST_CASE(brute_force_match),
        DS_TEST_CASE(kmp_next_table),
        DS_TEST_CASE(kmp_match),
        DS_TEST_CASE(kmp_overlap),
        DS_TEST_CASE(nextval_table),
        DS_TEST_CASE(optimized_kmp_match),
    };
    return ds_test_run(argc, argv, cases, sizeof(cases) / sizeof(cases[0]));
}
