# 第 6 章 图：代码索引

覆盖 PDF 第 207–276 页，印刷页第 195–264 页。所有整理代码均迁移为纯 C17；每个条目对应一个印刷代码块，同一块中的数据类型或辅助函数合并在同一行。算法实现沿用代码旁中文注释中的出处。

正文、题目和答案分别存放在 `body/`、`questions/` 和 `answers/`。题目中只印出数据类型的代码块保留原类型，不补写题目未给出的算法答案。

## 代码块

| # | 类别 | 章节/小节 | PDF 页 / 书页 | 印刷代码块及功能 | 源文件 | 测试用例 |
|---:|---|---|---|---|---|---|
| 1 | 正文 | 6.2.2 图的存储 | 214 / 202 | 邻接矩阵图 `MGraph` 类型 | `body/graph_source_types.h` | `source_types` |
| 2 | 正文 | 6.2.2 图的存储 | 216 / 204 | 邻接表图 `ArcNode`、`VNode`、`ALGraph` 类型 | `body/graph_source_types.h` | `source_types` |
| 3 | 题目 | 6.2.4 试题 07 | 221 / 209 | 欧拉路径题给定的邻接矩阵 `MGraph` 类型 | `questions/graph_question_types.h` | `source_types` |
| 4 | 题目 | 6.2.4 试题 08 | 221 / 209 | 出度大于入度题给定的邻接矩阵 `MGraph` 类型 | `questions/graph_question_types.h` | `source_types` |
| 5 | 答案 | 6.2.2 试题 05 | 225 / 213 | `Convert`：邻接表转邻接矩阵 | `answers/graph_answers.c` | `graph_conversion`、`graph_conversion_boundaries` |
| 6 | 答案 | 6.2.4 试题 07 | 225 / 213 | `IsExistEL`：按顶点度数奇偶性判断欧拉回路/通路 | `answers/graph_answers.c` | `euler_trail_degree` |
| 7 | 答案 | 6.2.4 试题 08 | 226 / 214 | `printK`：找出出度大于入度的顶点 | `answers/graph_answers.c` | `vertices_by_degree` |
| 8 | 正文 | 6.3.1 图的广度优先遍历 | 227 / 215 | `BFSTraverse`：遍历所有连通分量的外层控制 | `body/graph_algorithms.c` | `bfs_traversal`、`bfs_boundaries` |
| 9 | 正文 | 6.3.1 图的广度优先遍历 | 227 / 215 | 邻接表 `BFS`：从指定顶点进行广度优先搜索 | `body/graph_algorithms.c` | `bfs_traversal`、`bfs_boundaries` |
| 10 | 正文 | 6.3.1 图的广度优先遍历 | 227 / 215 | 邻接矩阵 `BFS`：从指定顶点进行广度优先搜索 | `body/graph_algorithms.c` | `bfs_traversal`、`bfs_boundaries` |
| 11 | 正文 | 6.3.1 图的广度优先遍历 | 228 / 216 | `BFS_MIN_Distance`：求无权图单源最短路径边数 | `body/graph_algorithms.c` | `bfs_shortest_distances` |
| 12 | 正文 | 6.3.2 图的深度优先遍历 | 229 / 217 | `DFSTraverse`：遍历所有连通分量的外层控制 | `body/graph_algorithms.c` | `dfs_traversal` |
| 13 | 正文 | 6.3.2 图的深度优先遍历 | 229 / 217 | 邻接表 `DFS`：递归深度优先遍历 | `body/graph_algorithms.c` | `dfs_traversal` |
| 14 | 正文 | 6.3.2 图的深度优先遍历 | 229 / 217 | 邻接矩阵 `DFS`：递归深度优先遍历 | `body/graph_algorithms.c` | `dfs_traversal` |
| 15 | 答案 | 6.3.4 综合应用题 03 | 236 / 224 | `isTree` 及递归访问辅助过程：判断无向图是否为树 | `answers/graph_answers.c` | `tree_detection` |
| 16 | 答案 | 6.3.4 综合应用题 04 | 236 / 224 | DFS 判断两顶点之间是否存在路径 | `answers/graph_answers.c` | `reachability` |
| 17 | 答案 | 6.3.4 综合应用题 04 | 237 / 225 | BFS 判断两顶点之间是否存在路径 | `answers/graph_answers.c` | `reachability` |
| 18 | 答案 | 6.3.4 综合应用题 05 | 237 / 225 | `FindPath`：回溯输出两顶点间所有简单路径 | `answers/graph_answers.c` | `paths` |
| 19 | 正文 | 6.4.1 最小生成树 | 238 / 226 | 最小生成树通用选边框架 | `body/graph_algorithms.c` | `mst_framework` |
| 20 | 正文 | 6.4.1 最小生成树 | 239 / 227 | `Prim`：从指定顶点逐步扩展最小生成树 | `body/graph_algorithms.c` | `prim_mst` |
| 21 | 正文 | 6.4.1 最小生成树 | 240 / 228 | `Kruskal`：按权值递增选边并避免成环 | `body/graph_algorithms.c` | `kruskal_mst` |
| 22 | 正文 | 6.4.4 有向无环图 | 245–246 / 233–234 | `TopologicalSort`：用栈进行拓扑排序 | `body/graph_algorithms.c` | `topological_sort` |
| 23 | 题目 | 6.4.4 试题 13 | 257 / 245 | 拓扑序唯一性题给定的邻接矩阵 `MGraph` 类型 | `questions/graph_question_types.h` | `source_types` |
| 24 | 答案 | 6.4.4 试题 07 | 269 / 257 | DFS 完成时间逆序生成拓扑序 | `answers/graph_answers.c` | `dfs_topological_sort` |
| 25 | 答案 | 6.3.4 综合应用题 10 | 270–271 / 258–259 | 路由应用中的链路、网络、路由弧和路由器类型 | `answers/routing_types.h` | `source_types` |
| 26 | 答案 | 6.4.4 试题 13 | 272–273 / 260–261 | 判断有向图是否只有唯一拓扑序 | `answers/graph_answers.c` | `unique_topological_order` |
| 27 | 正文 | 归纳总结 | 274 / 262 | 邻接矩阵 `NextNeighbor`：查找顶点的下一个邻接点 | `body/graph_algorithms.c` | `next_neighbors` |
| 28 | 正文 | 归纳总结 | 274 / 262 | 邻接表 `NextNeighbor`：查找邻接链中的下一个邻接点 | `body/graph_algorithms.c` | `next_neighbors` |

## 算法与测试

- 共整理 **28 个印刷代码块**：正文 15 个、题目 3 个、答案 10 个。
- 其中包含 **17 种算法操作**；邻接矩阵/邻接表版本分别保留为独立代码块，但按同一操作统计。
- `tests/graph_tests.c` 注册 **19 个 CTest 用例**，通过 `DS_TEST_FUNCTION`、`DS_TEST_CASE`、`DS_CHECK` 和 `ds_test_run`，覆盖常规输入、空图、孤立点、不可达点、环、非连通图、非法顶点及源类型编译。
- 动态图与结果对象的生命周期接口位于 `body/graph_algorithms.h`；`answers/routing_types.c` 和邻接表类型的销毁函数提供所有权清理支持，不计作新增印刷代码块。
- 题目第 6.2.4 试题 07、08 和第 6.4.4 试题 13 只有图类型定义，没有印出算法实现；本目录只保留题中类型，不补写答案。

## 来源核对

扫描版 PDF 经全页 OCR 定位候选页，并逐页渲染、视觉核对含代码的页面。PDF 第 270–271 页的路由类型块跨页。所有源实现前均有中文功能、章节/小节和 PDF/印刷页码注释；可调用的图包装类型是测试上下文，不计作书中印刷代码块。
