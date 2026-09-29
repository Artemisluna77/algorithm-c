# 第8章 排序代码索引

PDF 页序第345–403页（书页约第333–391页）。书页号按本 PDF 的页码差值换算；每项均已对照页面图像核对。

## 正文代码

| # | 代码块／功能 | PDF页／书页 | 源文件与公开 API | 测试 |
|---:|---|---|---|---|
| 1 | 直接插入排序 `InsertSort` | 345／约333¹ | `body/sorting_algorithms.c`：`ch08_insertion_sort` | `insertion_sort` |
| 2 | 折半插入排序 `BInsertSort` | 346／334 | 同上：`ch08_binary_insertion_sort` | `binary_insertion_sort` |
| 3 | 希尔排序 `ShellSort`（跨页续） | 347–348／335–336 | 同上：`ch08_shell_sort` | `shell_sort` |
| 4 | 冒泡排序 `BubbleSort` | 352／340 | 同上：`ch08_bubble_sort` | `bubble_sort` |
| 5 | 交换辅助代码 `swap`（冒泡排序脚注） | 352／340 | 同上：`ch08_swap_values` | `swap_values` |
| 6 | 快速排序递归函数 `QuickSort` | 355／343 | 同上：`ch08_quick_sort` | `quick_sort` |
| 7 | 首元素枢轴划分 `Partition` | 355／343 | 同上：`ch08_partition_first_pivot`；答案快速选择与平衡分组另有同算法辅助实现，见答案 #2、#4 | `first_pivot_partition` |
| 8 | 简单选择排序 `SelectSort` | 363／351 | 同上：`ch08_selection_sort` | `selection_sort` |
| 9 | 最大堆建堆与向下调整 `BuildMaxHeap`、`HeapAdjust` | 365／353 | 同上：`ch08_build_max_heap`、`ch08_heap_adjust` | `build_max_heap`、`heap_adjust` |
| 10 | 堆排序 `HeapSort` | 365／353 | 同上：`ch08_heap_sort` | `heap_sort` |
| 11 | 归并操作 `Merge`（辅助数组声明与函数） | 376／364 | 同上：`ch08_merge_sorted_ranges` | `merge_ranges` |
| 12 | 递归二路归并排序 `MergeSort` | 376／364 | 同上：`ch08_merge_sort` | `merge_sort` |
| 13 | 稳定计数排序 `CountSort`（跨页续） | 378–379／366–367 | 同上：`ch08_counting_sort` | `counting_sort` |

## 题目代码

| # | 代码块／功能 | PDF页／书页 | 源文件与公开 API | 测试 |
|---:|---|---|---|---|
| 1 | 荷兰国旗题给定枚举与未完成函数声明 | 358／346 | `questions/sorting_question_types.h`：`Color`、`Flag_Arrange` 声明 | 完整算法见答案项 #3 |
| 2 | 优先队列元素结构 `PriorityQueueElement` | 368／356 | `questions/sorting_question_types.h`：`PriorityQueueElement` | `priority_queue_operations` |
| 3 | 两两比较计数排序 `cmpcountsort` | 381／369 | `questions/comparison_count_sort.c`：`ch08_comparison_count_sort` | `comparison_count_sort` |

## 答案与解析代码

| # | 代码块／功能 | PDF页／书页 | 源文件与公开 API | 测试 |
|---:|---|---|---|---|
| 1 | 奇偶元素双指针划分 `move` | 360–361／348–349 | `answers/sorting_answers.c`：`ch08_move_even_before_odd` | `move_even_before_odd` |
| 2 | 快速选择第 k 小元素 `kth_elem` | 361／349 | 同上：`ch08_kth_element`（k 从 1 开始），内部使用 `ch08_partition_first`；该首元素划分与正文 #7 的实现分别保留 | `kth_element` |
| 3 | 荷兰国旗排序 `Flag_Arrange`（承接题目枚举） | 361–362／349–350 | 同上：`ch08_arrange_flag` | `arrange_flag` |
| 4 | 按中位枢轴平衡分组 `setPartition`（跨页续） | 362–363／350–351 | 同上：`ch08_partition_for_balance` | `balanced_partition` |
| 5 | 单链表简单选择排序 `selectSort` | 374／362 | 同上：`ch08_linked_list_selection_sort` | `linked_list_selection_sort` |
| 6 | 小根堆判断 `IsMinHeap` | 374／362 | 同上：`ch08_is_min_heap` | `is_min_heap` |
| 7 | 优先队列堆结构定义 | 374／362 | 同上：`DsPriorityQueue` | `priority_queue_operations` |
| 8 | 优先队列入队 `enqueue` | 374／362 | 同上：`ch08_priority_queue_enqueue` | `priority_queue_operations` |
| 9 | 优先队列出队 `dequeue`（跨页续） | 374–375／362–363 | 同上：`ch08_priority_queue_dequeue` | `priority_queue_operations` |
| 10 | 对已排序前缀继续插入排序 `Insert_Sort`（跨页续） | 391–392／379–380 | 同上：`ch08_insertion_sort_suffix` | `insertion_sort_suffix` |
| 11 | 末元素枢轴划分 `Partition` | 392／380 | 同上：`ch08_partition_last_pivot` | `last_pivot_partition` |
| 12 | 比较计数排序的稳定性修正分支 | 385／373 | 同上：`ch08_count_stable_pair` | `stable_pair_count_fragment` |

## 思维拓展伪代码转 C

| # | 来源 | 算法与转写 | C 源文件／测试 |
|---:|---|---|---|
| 1 | 第8章“思维拓展”提示，PDF 第403页／书页约第391页¹ | 将 0–65535 固定值域频数排序及“减去最小值处理负数”的伪代码说明实现为可调用 C17 函数 `ch08_frequency_sort_signed`；最小值与最大值跨度超过 65536 时返回范围错误 | `answers/sorting_exploration.c`；`range_frequency_sort` |

## 核对范围与转写约定

共整理 **28 个印刷代码块**：正文 13 个、题目 3 个、答案与解析 12 个；另把第403页提示中的 1 段说明性伪代码转写为 C17。CTest 注册 26 个单独用例。

¹ PDF 第345页的印刷页码末位受二维码遮挡；“333”由相邻页推算。第403页页码同样被遮挡，“391”由相邻页页码顺推。

- 已按 PDF 页序第345–403页逐页查看低分辨率联系页，并放大核对代码候选页：345–348、352、355、358、360–363、365、368、374–376、378–379、381、385、391–392。跨页代码按一个代码块登记。
- 第8章 8.5.2 基数排序和 8.7 外部排序的本段页面包含原理、图示、表格与题目答案，未发现完整程序代码块；不据此补写未印出的基数排序或外部排序实现。
- 题干第358页只给出 `Flag_Arrange(...){...}` 占位函数；可编译的枚举与函数声明登记在 `questions/sorting_question_types.h`，省略号占位没有作为伪代码副本保存。答案里的完整实现单独归入 `answers/`。
- 伪代码不另存原文副本；第403页提示中的频数排序已纳入 `answers/sorting_exploration.c`。频数数组最多有 65536 个槽，负数通过减去输入最小值映射到非负下标；跨度超限时明确返回 `DS_STATUS_INVALID_VALUE`，空间上界相对输入长度为 O(1)。
- 所有实现均为 C17，可通过头文件中的公开函数和结构体调用；错误输入通过 `DsStatus` 返回。C17 原生支持取地址符 `&` 和指针。计数排序要求键值在 `[0, key_range)`；奇偶划分按 `% 2 != 0` 判定奇数，因此可处理负奇数。
- 第362–363页 `setPartition` 按印刷代码选取前 `floor(n/2)` 个较小元素并返回右区和减左区和（有符号值）；源文未证明该划分可使次级目标 `|S1-S2|` 达到全局最优，转写保留其实际算法行为。

## 构建与测试

章节目标：`ch08_sort_tests`。CTest 为每项测试分别注册用例，合计26项。可在 CLion 选择该目标，或在仓库根目录运行：

```sh
cmake -S . -B build
cmake --build build --target ch08_sort_tests
ctest --test-dir build -R '^ch08_sort_tests\.' --output-on-failure
```
