# 第 1 章代码索引：绪论与算法评价

本章范围为 PDF 第 13–24 页（书页第 1–12 页）。`正文`、`试题`、`答案解析`按代码在原书中的位置标记。题目选项中的孤立表达式、单条操作语句和复杂度公式不作为完整程序代码块；PDF 第22页的 `if` 语句表用于推导递归次数，也不是完整程序。第 1.2.4 节答案与解析未发现需单独归档的完整代码块。书中 C 代码按 C17 转换；本章无 C++ 特有实现。

| 编号 | 类别 | 功能/代码块 | PDF 页码 | 书页 | 源文件 | 测试用例 |
| --- | --- | --- | ---: | ---: | --- | --- |
| C01-B-001 | 正文 | 数组逆序查找 | 17 | 5 | `body/reverse_search.c` | `reverse_search` |
| C01-B-002 | 正文 | 顺序执行常数、线性、平方级语句块 | 18 | 6 | `body/additive_block_example.c` | `additive_blocks` |
| C01-B-003 | 正文 | 嵌套常数、线性、平方级语句块 | 18 | 6 | `body/multiplicative_block_example.c` | `multiplicative_blocks` |
| C01-B-004 | 正文 | 二倍递增循环 | 23 | 11 | `body/summary_doubling_loop.c` | `summary_doubling` |
| C01-B-005 | 正文 | 平方条件递增循环 | 23 | 11 | `body/summary_square_root_loop.c` | `summary_square_root` |
| C01-Q-006 | 试题 | 循环倍增至超过 n | 18–19 | 6–7 | `questions/q06_double_loop.c` | `q06` |
| C01-Q-007 | 试题 | 递增至立方超过 n | 19 | 7 | `questions/q07_cube_loop.c` | `q07` |
| C01-Q-008 | 试题 | 冒泡排序最坏情况下的交换频度 | 19 | 7 | `questions/q08_bubble_frequency.c` | `q08` |
| C01-Q-009 | 试题 | 分支与嵌套循环输出次数 | 19 | 7 | `questions/q09_branch_loops.c` | `q09` |
| C01-Q-010 | 试题 | 三角形嵌套循环计数 | 19 | 7 | `questions/q10_triangular_loop.c` | `q10` |
| C01-Q-011 | 试题 | 递归时间复杂度函数 | 19 | 7 | `questions/q11_recurrence.c` | `q11` |
| C01-Q-012 | 试题 | 二倍递增循环 | 19 | 7 | `questions/q12_doubling.c` | `q12` |
| C01-Q-013 | 试题 | 递归阶乘 | 19 | 7 | `questions/q13_factorial.c` | `q13` |
| C01-Q-014 | 试题 | 二倍外循环与线性内循环 | 20 | 8 | `questions/q14_geometric_outer.c` | `q14` |
| C01-Q-015 | 试题 | 累加至阈值 | 20 | 8 | `questions/q15_triangular_sum.c` | `q15` |
| C01-Q-016 | 试题 | 逐次试算整数平方根 | 20 | 8 | `questions/q16_integer_sqrt.c` | `q16` |
| C01-Q-017 | 试题 | 倍增外循环与递增内循环 | 20 | 8 | `questions/q17_geometric_nested.c` | `q17` |
| C01-Q-018 | 试题 | 平方根范围内的三角循环 | 20 | 8 | `questions/q18_sqrt_triangular.c` | `q18` |
| C01-Q-APP01-1 | 试题 | 线性累加程序段 | 20 | 8 | `questions/application_01_linear.c` | `application_01` |
| C01-Q-APP01-2 | 试题 | 平方条件递增循环 | 20 | 8 | `questions/application_02_integer_sqrt.c` | `application_02` |
| C01-Q-APP01-3 | 试题 | 二维数组逐项置零 | 20 | 8 | `questions/application_03_zero_matrix.c` | `application_03` |

测试通过 `add_ds_test_executable` 与 `add_ds_test_case` 接入 CMake/CTest；每个表列用例均覆盖典型输入及边界输入。
