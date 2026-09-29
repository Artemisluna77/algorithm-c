#ifndef DATA_STRUCTURES_2027_TEST_HARNESS_H
#define DATA_STRUCTURES_2027_TEST_HARNESS_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*DsTestFunction)(void);

typedef struct DsTestCase {
    const char *name;
    DsTestFunction run;
} DsTestCase;

static int ds_test_failure_count = 0;

static void ds_test_check(int condition, const char *expression,
                          const char *file, int line) {
    if (!condition) {
        fprintf(stderr, "%s:%d: 检查失败：%s\n", file, line, expression);
        ++ds_test_failure_count;
    }
}

static int ds_test_run(int argc, char **argv,
                       const DsTestCase *cases, size_t case_count) {
    const char *selected_name = argc > 1 ? argv[1] : NULL;
    size_t executed_count = 0;
    int total_failure_count = 0;

    for (size_t i = 0; i < case_count; ++i) {
        if (selected_name != NULL && strcmp(selected_name, cases[i].name) != 0) {
            continue;
        }
        ds_test_failure_count = 0;
        cases[i].run();
        ++executed_count;
        if (ds_test_failure_count == 0) {
            printf("[通过] %s\n", cases[i].name);
        } else {
            fprintf(stderr, "[失败] %s：%d 项检查未通过\n",
                    cases[i].name, ds_test_failure_count);
            total_failure_count += ds_test_failure_count;
        }
    }

    if (executed_count == 0) {
        fprintf(stderr, "未找到测试用例：%s\n",
                selected_name == NULL ? "<none>" : selected_name);
        return EXIT_FAILURE;
    }
    return total_failure_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

#define DS_CHECK(expression) \
    ds_test_check((expression) != 0, #expression, __FILE__, __LINE__)

#define DS_TEST_FUNCTION(name) static void test_##name(void)
#define DS_TEST_CASE(name) {#name, test_##name}

#endif
