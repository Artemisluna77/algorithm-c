#include "string_matching.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// 功能：设置定长顺序存储串并记录串长。
// 来源：《2027数据结构》第4章 4.1.3；PDF第122页；书页第110页。
int StaticStringAssign(StaticString *string, const char *data, size_t length) {
    if (string == NULL || (data == NULL && length != 0) ||
        length > STATIC_STRING_MAX_LEN) {
        return 0;
    }
    if (length != 0) {
        memmove(string->ch, data, length);
    }
    string->length = length;
    return 1;
}

// 功能：复制字节序列到堆分配串，保留旧值直到新缓冲区分配成功。
// 来源：《2027数据结构》第4章 4.1.3；PDF第123页；书页第111页。
int HeapStringAssign(HeapString *string, const char *data, size_t length) {
    char *copy;
    if (string == NULL || (data == NULL && length != 0) || length == SIZE_MAX) {
        return 0;
    }
    copy = (char *)malloc(length + 1);
    if (copy == NULL) {
        return 0;
    }
    if (length != 0) {
        memcpy(copy, data, length);
    }
    copy[length] = '\0';
    free(string->ch);
    string->ch = copy;
    string->length = length;
    return 1;
}

// 功能：释放堆分配串并清空其字段。
void HeapStringDestroy(HeapString *string) {
    if (string != NULL) {
        free(string->ch);
        string->ch = NULL;
        string->length = 0;
    }
}

// 功能：逐字符比较主串和模式串；失配后主串回退并从模式首字符重试。
// 来源：《2027数据结构》第4章 4.2.1；PDF第123页；书页第111页。
size_t BruteForceIndex(const char *text, size_t text_length,
                       const char *pattern, size_t pattern_length) {
    size_t start;
    if ((text == NULL && text_length != 0) ||
        (pattern == NULL && pattern_length != 0)) {
        return 0;
    }
    if (pattern_length == 0) {
        return 1;
    }
    if (pattern_length > text_length) {
        return 0;
    }
    for (start = 0; start <= text_length - pattern_length; ++start) {
        if (memcmp(text + start, pattern, pattern_length) == 0) {
            return start + 1;
        }
    }
    return 0;
}

static NextTable EmptyTable(void) {
    NextTable table;
    table.data = NULL;
    table.length = 0;
    return table;
}

static NextTable AllocateTable(size_t pattern_length) {
    NextTable table = EmptyTable();
    if (pattern_length == SIZE_MAX || pattern_length + 1 > SIZE_MAX / sizeof(size_t)) {
        return table;
    }
    table.length = pattern_length + 1;
    table.data = (size_t *)calloc(table.length, sizeof(size_t));
    if (table.data == NULL) {
        table.length = 0;
    }
    return table;
}

// 功能：依据最长相等前后缀递推求出一基下标的 KMP next 数组。
// 来源：《2027数据结构》第4章 4.2.2；PDF第128页；书页第116页。
NextTable BuildNext(const char *pattern, size_t pattern_length) {
    NextTable next;
    size_t i;
    size_t j;
    if (pattern == NULL && pattern_length != 0) {
        return EmptyTable();
    }
    next = AllocateTable(pattern_length);
    if (next.data == NULL || pattern_length == 0) {
        return next;
    }

    i = 1;
    j = 0;
    while (i < pattern_length) {
        if (j == 0 || pattern[i - 1] == pattern[j - 1]) {
            ++i;
            ++j;
            next.data[i] = j;
        } else {
            j = next.data[j];
        }
    }
    return next;
}

// 功能：销毁动态 next 表并清空其字段。
void NextTableDestroy(NextTable *table) {
    if (table != NULL) {
        free(table->data);
        table->data = NULL;
        table->length = 0;
    }
}

static int IsValidTable(const NextTable *table, size_t pattern_length) {
    size_t i;
    if (table == NULL || table->data == NULL ||
        pattern_length == SIZE_MAX || table->length < pattern_length + 1) {
        return 0;
    }
    for (i = 1; i <= pattern_length; ++i) {
        if (table->data[i] >= i) {
            return 0;
        }
    }
    return 1;
}

// 功能：按 next 表回退模式串指针，主串指针仅向前移，返回首次匹配的一基位置。
// 来源：《2027数据结构》第4章 4.2.2；PDF第129页；书页第117页。
size_t KmpIndex(const char *text, size_t text_length,
                const char *pattern, size_t pattern_length,
                const NextTable *next) {
    size_t i = 0;
    size_t j = 1;
    if ((text == NULL && text_length != 0) ||
        (pattern == NULL && pattern_length != 0) ||
        !IsValidTable(next, pattern_length)) {
        return 0;
    }
    while (i < text_length && j <= pattern_length) {
        if (j == 0 || text[i] == pattern[j - 1]) {
            ++i;
            ++j;
        } else {
            j = next->data[j];
        }
    }
    return j > pattern_length ? i - pattern_length + 1 : 0;
}

// 功能：在 next 回退表基础上跳过与当前失配字符必然相同的模式串位置。
// 来源：《2027数据结构》第4章 4.2.3；PDF第129页；书页第117页。
NextTable BuildNextVal(const char *pattern, size_t pattern_length) {
    NextTable nextval;
    size_t i;
    size_t j;
    if (pattern == NULL && pattern_length != 0) {
        return EmptyTable();
    }
    nextval = AllocateTable(pattern_length);
    if (nextval.data == NULL || pattern_length == 0) {
        return nextval;
    }

    i = 1;
    j = 0;
    while (i < pattern_length) {
        if (j == 0 || pattern[i - 1] == pattern[j - 1]) {
            ++i;
            ++j;
            nextval.data[i] = pattern[i - 1] != pattern[j - 1]
                                  ? j
                                  : nextval.data[j];
        } else {
            j = nextval.data[j];
        }
    }
    return nextval;
}

// 功能：复用 KMP 匹配过程，以 nextval 表避免重复比较同一失配字符。
// 来源：依据《2027数据结构》第4章 4.2.3“匹配算法不变”说明派生；PDF第129页；书页第117页。不是独立印刷代码块。
size_t KmpIndexNextVal(const char *text, size_t text_length,
                       const char *pattern, size_t pattern_length,
                       const NextTable *nextval) {
    size_t i = 0;
    size_t j = 1;
    if ((text == NULL && text_length != 0) ||
        (pattern == NULL && pattern_length != 0) ||
        !IsValidTable(nextval, pattern_length)) {
        return 0;
    }
    while (i < text_length && j <= pattern_length) {
        if (j == 0 || text[i] == pattern[j - 1]) {
            ++i;
            ++j;
        } else {
            j = nextval->data[j];
        }
    }
    return j > pattern_length ? i - pattern_length + 1 : 0;
}
