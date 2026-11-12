#ifndef CHAPTER04_STRING_MATCHING_H
#define CHAPTER04_STRING_MATCHING_H

#include <stddef.h>

#define STATIC_STRING_MAX_LEN 255

// 功能：定义定长顺序存储串，最多保存 MAXLEN=255 个字符。
// 来源：《2027数据结构》第4章 4.1.3；PDF第122页；书页第110页。
typedef struct StaticString {
    char ch[STATIC_STRING_MAX_LEN];
    size_t length;
} StaticString;

// 功能：定义堆分配串，以动态字符数组保存串值并记录串长；调用者负责释放。
// 来源：《2027数据结构》第4章 4.1.3；PDF第123页；书页第111页。
typedef struct HeapString {
    char *ch;
    size_t length;
} HeapString;

#define HEAP_STRING_INIT {NULL, 0}

// 功能：保存按书中一基下标定义构造的 KMP next 表；调用者负责销毁。
typedef struct NextTable {
    size_t *data;
    size_t length;
} NextTable;

// 功能：设置定长顺序存储串；支持输入与目标存储区重叠，容量不足或参数无效时返回 0。
// 来源：《2027数据结构》第4章 4.1.3；PDF第122页；书页第110页。
int StaticStringAssign(StaticString *string, const char *data, size_t length);

// 功能：复制字节序列到堆分配串；对象首次使用前须设为 HEAP_STRING_INIT，成功返回 1。
// 来源：《2027数据结构》第4章 4.1.3；PDF第123页；书页第111页。
int HeapStringAssign(HeapString *string, const char *data, size_t length);

// 功能：释放堆分配串并清空其字段。
void HeapStringDestroy(HeapString *string);

// 功能：按暴力法查找模式串首次出现的一基位置；未匹配返回 0，空模式串返回 1。
// 来源：《2027数据结构》第4章 4.2.1；PDF第123页；书页第111页。
size_t BruteForceIndex(const char *text, size_t text_length,
                       const char *pattern, size_t pattern_length);

// 功能：按书中一基定义计算 KMP next 表；表的下标 0 保留为占位项。
// 来源：《2027数据结构》第4章 4.2.2；PDF第128页；书页第116页。
NextTable BuildNext(const char *pattern, size_t pattern_length);

// 功能：销毁动态 next 表并清空其字段。
void NextTableDestroy(NextTable *table);

// 功能：使用 next 表执行 KMP 模式匹配，返回一基起始位置或 0。
// 来源：《2027数据结构》第4章 4.2.2；PDF第129页；书页第117页。
size_t KmpIndex(const char *text, size_t text_length,
                const char *pattern, size_t pattern_length,
                const NextTable *next);

// 功能：按书中改进规则计算 KMP nextval 表。
// 来源：《2027数据结构》第4章 4.2.3；PDF第129页；书页第117页。
NextTable BuildNextVal(const char *pattern, size_t pattern_length);

// 功能：复用 KMP 匹配过程，以 nextval 表跳过重复失配比较并返回一基起始位置或 0。
// 来源：依据《2027数据结构》第4章 4.2.3“匹配算法不变”说明派生；PDF第129页；书页第117页。不是独立印刷代码块。
size_t KmpIndexNextVal(const char *text, size_t text_length,
                       const char *pattern, size_t pattern_length,
                       const NextTable *nextval);

#endif
