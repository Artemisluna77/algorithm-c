# 第5章「树与二叉树」代码索引

范围：PDF 第 136–206 页（书页第 124–194 页）。OCR 只用于定位候选页；每个代码块均对照 PDF 渲染页图核对。PDF 第 159–162 页等题目中的零散选项表达式不是完整代码块，因此不转录成算法。

本章源码与测试已迁移为纯 C17；动态结果和堆分配树结构提供显式释放接口。

共整理 **46 个书中代码块**：正文 22 个、题目数据结构定义 2 个、答案解析 22 个。另有孩子兄弟转换的正文规则派生实现与清理支持代码，单独列为派生实现，不计入书中代码块数。

## 正文

| 功能 / 代码块 | 来源 | C17 文件 | 测试 |
|---|---|---|---|
| 二叉链表结点 `BinaryNode` | PDF 144，书页 132 | [`body/binary_tree.h`](body/binary_tree.h) | `ch05_tree_tests.traversals` |
| 先序遍历 `PreOrder` | PDF 153，书页 141 | [`body/binary_tree.c`](body/binary_tree.c) | `ch05_tree_tests.traversals`、`ch05_tree_tests.traversal_boundaries` |
| 中序遍历 `InOrder` | PDF 153，书页 141 | [`body/binary_tree.c`](body/binary_tree.c) | 同上 |
| 后序遍历 `PostOrder` | PDF 153，书页 141 | [`body/binary_tree.c`](body/binary_tree.c) | 同上 |
| 层次遍历 `LevelOrder` | PDF 154，书页 142 | [`body/binary_tree.c`](body/binary_tree.c) | 同上 |
| 中序线索结点 `ThreadNode` | PDF 156，书页 144 | [`body/threaded_tree.h`](body/threaded_tree.h) | `ch05_tree_tests.threaded_tree` |
| 建立中序前驱、后继线索 `InThread` | PDF 156–157，书页 144–145 | [`body/threaded_tree.c`](body/threaded_tree.c) | `ch05_tree_tests.threaded_tree` |
| 建立整棵线索树 `CreateInThread` | PDF 157，书页 145 | 同上 | 同上 |
| 查找中序首结点 `Firstnode` | PDF 157，书页 145 | 同上 | 同上 |
| 查找中序后继 `Nextnode` | PDF 157，书页 145 | 同上 | 同上 |
| 线索树非递归中序遍历 `Inorder` | PDF 158，书页 146 | 同上 | 同上 |
| 树的双亲表示结点与数组 `PTree` | PDF 180–181，书页 168–169 | [`body/tree_forest.h`](body/tree_forest.h) | `ch05_tree_tests.question_types` |
| 孩子兄弟结点 `CSNode` | PDF 182，书页 170 | 同上 | `ch05_tree_tests.tree_forest_roundtrip`、`ch05_tree_tests.forest_algorithms` |
| 孩子兄弟表示与递归叶结点计数 `Leaves` | PDF 192，书页 180 | 同上 / [`body/tree_forest.c`](body/tree_forest.c) | `ch05_tree_tests.forest_algorithms` |
| 孩子兄弟表示的树高 `Height` | PDF 192，书页 180 | [`body/tree_forest.c`](body/tree_forest.c) | `ch05_tree_tests.forest_algorithms` |
| 并查集双亲数组 `UFSets` | PDF 195，书页 183 | [`body/disjoint_set.h`](body/disjoint_set.h) | `ch05_tree_tests.disjoint_set_operations`、`ch05_tree_tests.disjoint_set_boundaries` |
| 并查集初始化 `Initial` | PDF 196，书页 184 | [`body/disjoint_set.c`](body/disjoint_set.c) | `ch05_tree_tests.disjoint_set_operations` |
| 并查集基本查找 `Find` | PDF 196，书页 184 | 同上 | 同上 |
| 并查集基本合并 `Union` | PDF 196，书页 184 | 同上 | 同上 |
| 按集合大小合并 `Union` | PDF 196，书页 184 | 同上 | 同上 |
| 路径压缩查找 `Find` | PDF 196–197，书页 184–185 | 同上 | 同上 |
| 回调形式的通用递归遍历 `Track` | PDF 204–205，书页 192–193 | [`body/binary_tree.c`](body/binary_tree.c) | `ch05_tree_tests.generic_traversal` |

## 题目

| 功能 / 代码块 | 来源 | C17 文件 | 测试 |
|---|---|---|---|
| 表达式树结点 `ExpressionNode`（固定 10 字节数据域） | PDF 163，书页 151 | [`questions/problem_types.h`](questions/problem_types.h) | `ch05_tree_tests.question_types`、`ch05_tree_tests.expression_tree` |
| 顺序存储二叉树 `SequentialTree` | PDF 164，书页 152 | 同上 | `ch05_tree_tests.question_types`、`ch05_tree_tests.sequential_bst` |

PDF 第 159–162 页及题目其余部分没有完整印出的算法代码。选项中出现的单行条件和问题描述不作为代码块；未补写没有书中答案代码的题目。

## 答案解析

| 功能 / 代码块 | 来源 | C17 文件 | 测试 |
|---|---|---|---|
| 顺序存储二叉树最近公共祖先 `Comm_Ancestor` | PDF 151–152，书页 139–140 | [`answers/tree_solutions.c`](answers/tree_solutions.c) | `ch05_tree_tests.sequential_lca` |
| 按层次遍历计算二叉树高度 `Btdepth` | PDF 170–171，书页 158–159 | 同上 | `ch05_tree_tests.binary_tree_answers` |
| 递归计算二叉树高度 `Btdepth2` | PDF 171，书页 159 | 同上 | 同上 |
| 判断完全二叉树 `IsComplete` | PDF 171，书页 159 | 同上 | 同上 |
| 统计双分支结点 `DsonNodes` | PDF 172，书页 160 | 同上 | 同上 |
| 交换左右子树 `swap` | PDF 172，书页 160 | 同上 | `ch05_tree_tests.binary_tree_edges` |
| 查找先序第 k 个结点 `PreNode` | PDF 172–173，书页 160–161 | 同上 | 同上 |
| 后序释放子树 `DeleteXTree` | PDF 173，书页 161 | 同上 | `ch05_tree_tests.deletion` |
| 删除所有目标值结点的子树 `Search` | PDF 173，书页 161 | 同上 | 同上 |
| 迭代输出目标结点祖先 `Search` | PDF 174，书页 162 | 同上 | `ch05_tree_tests.ancestor_lca` |
| 最近公共祖先 `Ancestor`（适配为结点指针接口） | PDF 174–175，书页 162–163 | 同上 | 同上 |
| 计算二叉树最大宽度 `BTWidth` | PDF 175–176，书页 163–164 | 同上 | `ch05_tree_tests.width` |
| 满二叉树先序转后序 `PreToPost` | PDF 176，书页 164 | 同上 | `ch05_tree_tests.full_tree_conversion` |
| ABCDEFG 先序转后序示例程序 | PDF 176，书页 164 | 同上 | 同上 |
| 中序遍历并链接叶结点 `Inorder` | PDF 176–177，书页 164–165 | 同上 | `ch05_tree_tests.leaf_list` |
| 判断两棵树结构相似 `similar` | PDF 177，书页 165 | 同上 | `ch05_tree_tests.similarity` |
| 带权二叉树结点 `node` | PDF 178，书页 166 | [`answers/tree_solutions.h`](answers/tree_solutions.h) | `ch05_tree_tests.weighted_path` |
| 按叶结点深度求 WPL（`WPL` / `WPL1`） | PDF 178，书页 166 | [`answers/tree_solutions.c`](answers/tree_solutions.c) | 同上 |
| 后序更新内部权值并求 WPL | PDF 178，书页 166 | 同上 | 同上 |
| 表达式树转中缀式 `BtreeToE` / `BtreeToExp` | PDF 179，书页 167 | 同上 | `ch05_tree_tests.expression_tree` |
| 中序递增检查顺序树是否为 BST `judgeInorderBST` | PDF 179，书页 167 | 同上 | `ch05_tree_tests.sequential_bst` |
| 自底向上子树界限检查 BST `judgeBST` | PDF 180，书页 168 | 同上 | 同上 |

题目 16、17 的数据结构定义与答案中的完整代码均已分别归入“题目”和“答案解析”。题目 15 的 WPL 结点是图示，不是代码块；含 `weight` 的结构代码位于 PDF 178 的答案解析。仅有文字或图示、没有印出算法代码的问题没有补答案。

## 派生与支撑实现

以下代码根据正文规则或为 C17 动态内存所有权 / 测试接口补充，不计入 46 个书中代码块。最近公共祖先行记录了已计数书中代码块的接口适配，不代表额外代码块。

| 实现 | 依据 / 用途 | 文件 | 测试 |
|---|---|---|---|
| 一般树转孩子兄弟表示 `TreeToChildSibling` | PDF 182–183，书页 170–171 的左孩子-右兄弟转换规则；用于往返测试 | [`body/tree_forest.c`](body/tree_forest.c) | `ch05_tree_tests.tree_forest_roundtrip` |
| 孩子兄弟表示还原一般树 `ChildSiblingToTree` | 同上 | 同上 | 同上 |
| 测试转换用的一般树结点 `GeneralTreeNode` | PDF 182–183 的转换规则派生 | [`body/tree_forest.h`](body/tree_forest.h) | `ch05_tree_tests.tree_forest_roundtrip` |
| 释放转换后孩子兄弟结点 `DestroyChildSibling` | C17 动态分配清理支持 | 同上 | 同上 |
| 二叉树最近公共祖先的动态路径实现 | 对照 PDF 174–175 的祖先路径规则，返回公开结点指针；实现改用动态路径数组 | [`answers/tree_solutions.c`](answers/tree_solutions.c) | `ch05_tree_tests.ancestor_lca` |
| 按元素查找并按大小合并的便捷接口 `Union` | 组合 PDF 196–197 的 `Find` 与按大小 `Union` | [`body/disjoint_set.c`](body/disjoint_set.c) | `ch05_tree_tests.disjoint_set_operations` |
| 先序 / 中序 / 后序遍历回调接口 | 将 PDF 204–205 的 `Track` 通用遍历占位点转为 C 回调与枚举 | [`body/binary_tree.h`](body/binary_tree.h)、[`body/binary_tree.c`](body/binary_tree.c) | `ch05_tree_tests.generic_traversal` |

## 测试入口

章节目标 `ch05_tree_tests` 已通过根 CMake 的 `add_ds_test_executable` 和 `add_ds_test_case` 注册 21 个可单独运行的用例；具体命令和 CLion 使用方法见仓库根目录 README。
