# 第 7 章 查找：代码索引

覆盖本章扫描页 PDF 第 277–342 页（印刷页第 265–330 页）。用户任务所给 PDF 第 343 页起已进入第 8 章“排序”；第 345 页的直接插入排序程序不属于本章。

正文、题目和答案分别存放在 `body/`、`questions/` 和 `answers/`。每行对应一个完整印刷代码块；同一灰底块中的类型/函数合并在一行。只提出编程要求而没有印出代码的练习没有补写答案。

源码统一转换为 C17；顺序表通过指针和显式长度/容量描述，树节点通过结构体指针连接并提供初始化/销毁接口。函数以状态码和输出参数表达未命中、非法输入及缓冲区不足。

## 代码块

| # | 类别 | 章节/小节 | PDF 页 / 书页 | 印刷代码块及功能 | 源文件 | 测试用例 |
|---:|---|---|---|---|---|---|
| 1 | 正文 | 7.2.1 顺序查找 | 277 / 265 | `Ch07SearchTable` 和 `ch07_search_seq`：以哨兵实现顺序查找 | `body/search_algorithms.h`、`body/search_algorithms.c` | `sequential_search`、`sequential_boundaries`、`source_types` |
| 2 | 正文 | 7.2.2 折半查找 | 279 / 267 | `Binary_Search`：迭代折半查找 | `body/search_algorithms.c`：`ch07_binary_search` | `binary_search` |
| 3 | 题目 | 7.2.2 试题 22 | 283 / 271 | 固定步长跳跃后回看区间的查找片段 | `questions/search_question_snippets.h`、`questions/search_question_snippets.c`：`ch07_stride_search` | `stride_search` |
| 4 | 答案 | 7.2.2 试题 04 | 289 / 277 | 递归 `BinSearchRec` 及其一基下标查找表：命中返回位置，未命中返回 0 | `answers/search_answers.h`、`answers/search_answers.c`：`ch07_bin_search_rec` | `recursive_binary_search` |
| 5 | 答案 | 7.2.2 试题 05 | 289 / 277 | `SeqSrch`：查找命中后与前一项交换的自组织查找 | `answers/search_answers.h`、`answers/search_answers.c`：`ch07_seq_srch` | `self_organizing_search` |
| 6 | 答案 | 7.2.2 试题 06 | 290 / 278 | `findkey`：在行列递增的方阵中查找关键字 | `answers/search_answers.c`：`ch07_find_key` | `sorted_matrix_search` |
| 7 | 正文 | 7.3.1 二叉排序树 | 291 / 279 | `BST_Search`：沿左右子树查找关键字 | `body/search_algorithms.c`：`ch07_bst_search` | `bst_search` |
| 8 | 正文 | 7.3.1 二叉排序树 | 292 / 280 | `BST_Insert`：递归插入关键字 | `body/search_algorithms.c`：`ch07_bst_insert` | `bst_insert_build` |
| 9 | 正文 | 7.3.1 二叉排序树 | 292 / 280 | `Create_BST`：按输入顺序批量构造二叉排序树 | `body/search_algorithms.c`：`ch07_create_bst` | `bst_insert_build` |
| 10 | 答案 | 7.3.1 试题 05 | 314 / 302 | `JudgeBST`：用中序次序判断二叉排序树 | `answers/search_answers.c`：`ch07_judge_bst` | `judge_bst` |
| 11 | 答案 | 7.3.1 试题 06 | 314–315 / 302–303 | `level`：计算二叉排序树中查找关键字的层数 | `answers/search_answers.c`：`ch07_level` | `search_level` |
| 12 | 答案 | 7.3.1 试题 07 | 315 / 303 | `Judge_AVL`：递归计算高度并判断平衡性 | `answers/search_answers.c`：`ch07_judge_avl` | `judge_avl` |
| 13 | 答案 | 7.3.1 试题 08 | 315 / 303 | `MinKey`、`MaxKey`：查找二叉排序树中的最小/最大关键字 | `answers/search_answers.c`：`ch07_min_key`、`ch07_max_key` | `minmax` |
| 14 | 答案 | 7.3.1 试题 09 | 316 / 304 | `OutPut`：逆中序输出所有不小于阈值的关键字 | `answers/search_answers.c`：`ch07_output_threshold` | `output_threshold` |
| 15 | 答案 | 7.3.1 试题 10 | 316 / 304 | `Search_Small`：查找二叉排序树中第 k 小关键字 | `answers/search_answers.c`：`ch07_search_small` | `kth_smallest` |

## 算法与测试

- 共整理 **15 个印刷代码块**：正文 5 个、题目 1 个、答案 9 个。
- 共实现 **16 个可调用算法操作**；`MinKey` 与 `MaxKey`、`BST_Insert` 与 `Create_BST` 分别计为独立操作。
- `tests/search_tests.c` 注册 **16 个 CTest 用例**，覆盖常规输入、命中/未命中、空表/空树、无效秩、重复关键字和边界子区间；`source_types` 用于编译及查找表/树类型的基本构造检查。
- 7.4 B 树、7.5 散列表范围经 OCR 全页筛查和逐页视觉核对，PDF 第 317–342 页未发现完整印刷程序代码块；相关习题只有题目或文字解析，未补写解答。题目段落未印出算法代码的条目也未生成算法实现。

## 来源核对

扫描版 PDF 经全页 OCR 定位候选页后渲染视觉确认。第 7 章最后内容在 PDF 第 342 页结束；第 343 页为第 8 章分隔页，PDF 第 345 页直接插入排序代码属于第 8 章，因此不纳入本索引。每个印刷代码块对应源文件中的中文功能、章节/小节、PDF 页和印刷页注释。`BSTNode`、查找表等类型适配仅用于让印刷算法可通过公开接口测试，不作为新增印刷代码块统计。
