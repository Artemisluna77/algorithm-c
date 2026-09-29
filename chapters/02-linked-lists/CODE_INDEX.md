# 第 2 章代码索引

本索引按代码在书中的类别分开记录：正文示例放在 `body/`，题目中直接给出的代码定义放在 `questions/`，答案与解析中的实现放在 `answers/`。PDF 页码是本地 PDF 阅读器的页序，书页为页面印刷页码（本章相差 12 页）。源代码保留中文功能与来源注释；为便于 CLion/CMake 使用，书中代码块按 C17 语义转换并由测试验证；原 C++ `new[]` 示例改用 C17 `malloc/free`。

答案解析中第 9 题的题意及算法说明写的是“求交集”，但印刷代码函数名为 `Union`，实现也执行交集并把结果保留在 A 表。索引按题意和代码行为记录该命名冲突，没有把它改造成并集算法。

| 编号 | 类别 | 功能/代码块 | PDF 页码 | 书页 | 源文件 | 测试用例 |
| --- | --- | --- | ---: | ---: | --- | --- |
| C02-B-001 | 正文 | 静态顺序表结构（MaxSize=50） | 27–28 | 15–16 | `body/sequential_list.h` | `init_static` |
| C02-B-002 | 正文 | 动态顺序表结构 | 28 | 16 | `body/sequential_list.h` | `init_dynamic` |
| C02-B-003 | 正文 | C `malloc` 动态初始化示例的 C17 内存管理转换 | 28 | 16 | `body/sequential_list.c` | `allocation_examples` |
| C02-B-004 | 正文 | 书中 `new[]` 动态初始化示例的 C17 内存管理转换 | 28 | 16 | `body/sequential_list.c` | `allocation_examples` |
| C02-B-005 | 正文 | 静态顺序表初始化 | 28 | 16 | `body/sequential_list.c` | `init_static` |
| C02-B-006 | 正文 | 动态顺序表初始化 | 28–29 | 16–17 | `body/sequential_list.c` | `init_dynamic` |
| C02-B-007 | 正文 | 顺序表插入 | 29 | 17 | `body/sequential_list.c` | `insert_positions`, `insert_boundaries` |
| C02-B-008 | 正文 | 顺序表删除 | 29 | 17 | `body/sequential_list.c` | `delete_positions`, `delete_boundaries` |
| C02-B-009 | 正文 | 顺序查找 | 30 | 18 | `body/sequential_list.c` | `locate` |
| C02-B-010 | 正文 | 单链表结点定义 | 43 | 31 | `body/linked_lists.h` | `init_list_forms` |
| C02-B-011 | 正文 | 带头结点单链表初始化 | 43–44 | 31–32 | `body/linked_lists.c` | `init_list_forms` |
| C02-B-012 | 正文 | 不带头结点单链表初始化 | 44 | 32 | `body/linked_lists.c` | `init_list_forms` |
| C02-B-013 | 正文 | 单链表长度、按序号取结点、按值查找 | 44–45 | 32–33 | `body/linked_lists.c` | `length`, `get_by_index`, `locate_value` |
| C02-B-014 | 正文 | 单链表插入 | 45 | 33 | `body/linked_lists.c` | `insert_delete`, `operation_boundaries` |
| C02-B-015 | 正文 | 单链表删除 | 46 | 34 | `body/linked_lists.c` | `insert_delete`, `operation_boundaries` |
| C02-B-016 | 正文 | 单链表头插法建表 | 47 | 35 | `body/linked_lists.c` | `build_head_tail` |
| C02-B-017 | 正文 | 单链表尾插法建表 | 47 | 35 | `body/linked_lists.c` | `build_head_tail` |
| C02-B-018 | 正文 | 双链表结点定义 | 48 | 36 | `body/linked_lists.h` | `doubly_link_operations` |
| C02-B-019 | 正文 | 双链表结点插入指针操作 | 48 | 36 | `body/linked_lists.c` | `doubly_link_operations` |
| C02-B-020 | 正文 | 双链表结点删除指针操作 | 49 | 37 | `body/linked_lists.c` | `doubly_link_operations` |
| C02-B-021 | 正文 | 静态链表结点及数组类型 | 50 | 38 | `body/linked_lists.h` | `static_and_question_types` |
| C02-Q-001 | 试题 | 第 20 题单链表结点定义 | 57 | 45 | `questions/q20_node.h` | `static_and_question_types` |
| C02-A-001 | 答案解析 | 顺序表删除最小值并以表尾元素填补空位 | 34–35 | 22–23 | `answers/sequential_algorithms.c` | `delete_minimum` |
| C02-A-002 | 答案解析 | 顺序表逆置 `Reverse` | 35 | 23 | `answers/sequential_algorithms.c` | `reverse_sequence` |
| C02-A-003 | 答案解析 | 顺序表删除值为 x 的元素（压缩法）`del_x_1` | 35 | 23 | `answers/sequential_algorithms.c` | `erase_value` |
| C02-A-004 | 答案解析 | 顺序表删除值为 x 的元素（计数法）`del_x_2` | 35 | 23 | `answers/sequential_algorithms.c` | `erase_value` |
| C02-A-005 | 答案解析 | 删除顺序表中闭区间 [s,t] 的元素 `Del_s_t` | 36 | 24 | `answers/sequential_algorithms.c` | `erase_range` |
| C02-A-006 | 答案解析 | 有序顺序表去除重复元素 `Delete_Same` | 36 | 24 | `answers/sequential_algorithms.c` | `delete_same_sequence` |
| C02-A-007 | 答案解析 | 合并两个有序顺序表 `Merge` | 36–37 | 24–25 | `answers/sequential_algorithms.c` | `merge_sequence` |
| C02-A-008 | 答案解析 | 数组区间逆置 `Reverse` | 37 | 25 | `answers/sequential_algorithms.c` | `reverse_blocks` |
| C02-A-009 | 答案解析 | 逆置法交换两个相邻数组块 `Exchange` | 37 | 25 | `answers/sequential_algorithms.c` | `reverse_blocks` |
| C02-A-010 | 答案解析 | 有序数组查找、交换后继或插入 `SearchExchangeInsert` | 37–38 | 25–26 | `answers/sequential_algorithms.c` | `search_exchange_insert` |
| C02-A-011 | 答案解析 | 三个递增数组的公共元素 `samekey` | 38 | 26 | `answers/sequential_algorithms.c` | `common_three` |
| C02-A-012 | 答案解析 | 数组循环左移 `Reverse` 与 `Converse` | 39 | 27 | `answers/sequential_algorithms.c` | `rotate_left` |
| C02-A-013 | 答案解析 | 两个等长有序数组的中位数 `M_Search` | 39–40 | 27–28 | `answers/sequential_algorithms.c` | `median_two_sorted` |
| C02-A-014 | 答案解析 | 主元素候选与计数确认 `Majority` | 40 | 28 | `answers/sequential_algorithms.c` | `majority` |
| C02-A-015 | 答案解析 | 最小未出现正整数 `findMissMin` | 41 | 29 | `answers/sequential_algorithms.c` | `missing_positive` |
| C02-A-016 | 答案解析 | 三个有序数组的最小距离 `findMinofTrip` | 42 | 30 | `answers/sequential_algorithms.c` | `minimum_three_distance` |
| C02-A-017 | 答案解析 | 后缀极值乘积 `calMulMax` | 42 | 30 | `answers/sequential_algorithms.c` | `suffix_extreme_product` |
| C02-A-018 | 答案解析 | 删除单链表中所有值为 x 的结点（前驱法）`Del_X_1` | 62 | 50 | `answers/linked_list_algorithms.c` | `delete_value_methods` |
| C02-A-019 | 答案解析 | 删除单链表中所有值为 x 的结点（尾插重建法）`Del_X_2` | 62 | 50 | `answers/linked_list_algorithms.c` | `delete_value_methods` |
| C02-A-020 | 答案解析 | 删除单链表最小值结点 `Delete_Min` | 63 | 51 | `answers/linked_list_algorithms.c` | `delete_minimum` |
| C02-A-021 | 答案解析 | 头插法逆置单链表 `Reverse_1` | 63 | 51 | `answers/linked_list_algorithms.c` | `reverse_methods` |
| C02-A-022 | 答案解析 | 指针反转逆置单链表 `Reverse_2` | 64 | 52 | `answers/linked_list_algorithms.c` | `reverse_methods` |
| C02-A-023 | 答案解析 | 删除值位于开区间 (s,t) 的结点 `RangeDelete` | 64 | 52 | `answers/linked_list_algorithms.c` | `delete_open_range` |
| C02-A-024 | 答案解析 | 按奇数位和偶数位拆分单链表 `DisCreat_2` | 65 | 53 | `answers/linked_list_algorithms.c` | `split_alternating_positions` |
| C02-A-025 | 答案解析 | 递增单链表去除重复结点 `Del_Same` | 65 | 53 | `answers/linked_list_algorithms.c` | `erase_adjacent_duplicates` |
| C02-A-026 | 答案解析 | 两个有序单链表逐对求公共元素 `Get_Common` | 66 | 54 | `answers/linked_list_algorithms.c` | `sorted_intersections` |
| C02-A-027 | 答案解析 | 题意为交集、印刷函数名为 `Union` 的原链表归并算法 | 66–67 | 54–55 | `answers/linked_list_algorithms.c` | `sorted_intersections` |
| C02-A-028 | 答案解析 | 判断一个链表是否为另一个链表的连续子序列 `Pattern` | 67 | 55 | `answers/linked_list_algorithms.c` | `contiguous_pattern` |
| C02-A-029 | 答案解析 | 判断循环双链表是否对称 `Symmetry` | 68 | 56 | `answers/linked_list_algorithms.c` | `circular_doubly_symmetry` |
| C02-A-030 | 答案解析 | 拼接两个循环单链表 `Link` | 68 | 56 | `answers/linked_list_algorithms.c` | `circular_singly_link` |
| C02-A-031 | 答案解析 | 双链表按访问频次递减重排 `Locate` | 68–69 | 56–57 | `answers/linked_list_algorithms.c` | `frequency_locate` |
| C02-A-032 | 答案解析 | 单链表循环右移 `Converse` | 69 | 57 | `answers/linked_list_algorithms.c` | `rotate_right` |
| C02-A-033 | 答案解析 | Floyd 快慢指针查找环入口 `FindLoopStart` | 70 | 58 | `answers/linked_list_algorithms.c` | `find_loop_start` |
| C02-A-034 | 答案解析 | 偶数长度单链表的最大孪生和 `PairSum` | 70–71 | 58–59 | `answers/linked_list_algorithms.c` | `symmetric_pair_sum` |
| C02-A-035 | 答案解析 | `link` 结点定义及单链表倒数第 k 个结点 `Search_k` | 71 | 59 | `answers/q17_node.h`, `answers/linked_list_algorithms.c` | `kth_from_end` |
| C02-A-036 | 答案解析 | 字符结点定义、公共后缀长度 `listlen` 与起点查找 | 72 | 60 | `answers/q18_node.h`, `answers/linked_list_algorithms.c` | `common_suffix` |
| C02-A-037 | 答案解析 | 绝对值去重结点定义与算法 | 73 | 61 | `answers/q19_node.h`, `answers/linked_list_algorithms.c` | `absolute_value_deduplication` |
| C02-A-038 | 答案解析 | 单链表首尾交替重排 `change_list` | 73–74 | 61–62 | `answers/linked_list_algorithms.c` | `reorder_first_last` |

PDF 第26页的 ADT 操作清单以及第52–61页的选择题指针更新式、简短操作片段和答案解析中的说明性代码，不构成完整程序代码块，未将其扩写成算法答案。本章不含实现代码的设计题保持为索引以外的文字题目，没有代替书中补写答案。为完成 C17 转换而增加的动态内存释放函数、指针输出接口与测试辅助代码，不单独计入书中代码块索引。
