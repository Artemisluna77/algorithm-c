# 第4章「串」代码索引

范围：PDF 第 121–135 页（书页第 109–123 页）。OCR 仅用于定位候选页；下表代码已对照渲染页图核对。

已转录 **6 个书中代码块**，均属正文；题目和答案解析没有完整已印代码块。`KmpIndexNextVal` 是依据正文说明派生的匹配函数，不计入书中代码块数量。实现和测试接口已迁移为纯 C17。

| 类别 | 功能 / 代码块 | 来源 | C17 文件 | 测试 |
|---|---|---|---|---|
| 正文 | 定长顺序存储串 `StaticString` | PDF 122，书页 110 | [`body/string_matching.h`](body/string_matching.h) | `ch04_string_tests.storage_types` |
| 正文 | 堆分配存储串 `HeapString` | PDF 123，书页 111 | [`body/string_matching.h`](body/string_matching.h) | `ch04_string_tests.storage_types` |
| 正文 | 暴力模式匹配 `Index` | PDF 123，书页 111 | [`body/string_matching.c`](body/string_matching.c) | `ch04_string_tests.brute_force_match` |
| 正文 | KMP `next` 表构造 `get_next` | PDF 128，书页 116 | [`body/string_matching.c`](body/string_matching.c) | `ch04_string_tests.kmp_next_table` |
| 正文 | KMP 匹配 `Index_KMP` | PDF 129，书页 117 | [`body/string_matching.c`](body/string_matching.c) | `ch04_string_tests.kmp_match`、`ch04_string_tests.kmp_overlap` |
| 正文 | 改进 `nextval` 表构造 `get_nextval` | PDF 129，书页 117 | [`body/string_matching.c`](body/string_matching.c) | `ch04_string_tests.nextval_table` |
| 派生实现 | 使用 `nextval` 执行 KMP 匹配；沿用原匹配过程，替换回退表 | 依据 PDF 129，书页 117 的正文说明派生 | [`body/string_matching.c`](body/string_matching.c) | `ch04_string_tests.optimized_kmp_match` |

## 分类说明

- [正文实现](body/) 保留存储定义与已印算法，接口使用纯 C17 函数和结构体；堆字符串与 next 表由调用者显式销毁。
- [题目](questions/README.md) 未印出可独立整理的完整代码块；未为无代码题目补答。
- [答案](answers/README.md) 未发现完整已印代码块。
- 暴力匹配、KMP 与优化 KMP 均覆盖常规匹配、未匹配、空串、重叠匹配或表长度边界。
