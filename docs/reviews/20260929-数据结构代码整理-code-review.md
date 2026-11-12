# 代码审查报告:数据结构代码整理

- **审查日期**:2026-09-29
- **审查分支**:`feat/20260929-数据结构代码整理`
- **审查基准**:`main`(f634aa4)
- **变更集**:分支相对 `main` 尚无新提交(`git diff main...HEAD` 为空),全部交付物为未跟踪的工作区文件——`chapters/` 八章、`tests/`、`CMakeLists.txt`、`README.md`,约 1.2 万行 C 代码。
- **构建验收证据**:cmake 配置与编译全部成功;CTest 193 项测试 100% 通过,0 失败。
- **审查方式**:Standards(编码标准)与 Spec(规格符合度)两轴独立审查后聚合。

规格来源:`.scratch/2027-data-structures-c/spec.md` 及工单 `.scratch/2027-data-structures-c/issues/`(01–19)。

## Standards(编码标准)

总体:已抽样全部 8 章的 body/questions/answers/tests 及 8 份 CODE_INDEX.md。页码注释、可追溯索引、CTest 独立用例、C17+仅标准库、README 目录约定均落实良好。

### (a) 成文标准违规(硬性)

1. spec.md「每段代码前写中文功能注释」——`chapters/05-trees/answers/tree_solutions.c:41`(`PushConstNode`)、`:66`(`PushMutableNode`)、`:91`(`PushPath`)三个辅助函数完全没有中文功能注释;第 7/8 章同类辅助函数(如 `ch07_insert_node`、`ch08_validate_array`)均有注释,属标准执行不一致。

### (b) Smell(均为判断题,非硬性违规)

1. **Duplicated Code**(最重):动态数组"倍增扩容+溢出检查"逻辑至少 6 份拷贝——`chapters/05-trees/answers/tree_solutions.c:41/66/91/304`、`chapters/06-graphs/body/graph_algorithms.c:128`、`chapters/06-graphs/answers/graph_answers.c:19`、`chapters/05-trees/body/threaded_tree.c:79`。建议各章提取一个共享增长辅助函数。
2. **Duplicated Code**:`chapters/03-stacks-queues/body/circular_enqueue.c` 与 `circular_dequeue.c` 重复同一组 `front/rear` 越界守卫(各 6 行),可提取有效性检查。
3. **Duplicated Code**:首枢轴划分有两份实现——`ch08_partition_first_pivot`(`chapters/08-sorting/body/sorting_algorithms.c:172`)与 `ch08_partition_first`(`chapters/08-sorting/answers/sorting_answers.c:9`)。因各自对应书中不同片段、可追溯性优先,可保留,但建议在索引中互相标注。
4. **Data Clumps**:`chapters/06-graphs/questions/graph_question_types.h` 中三个字段完全相同的邻接矩阵结构体,系逐题保真所致,可接受;可加注释说明为何不合并。
5. **Shotgun Surgery**:第 3 章一行一文件(`init_circular_queue.c`、`push.c`、`pop.c` 等)使接口调整需多点散改,系溯源约定驱动,可接受但值得知悉。
6. `chapters/06-graphs/answers/graph_answers.c:392-397` 的三行手写交换可提取小 helper,属轻微。

## Spec(规格符合度)

### (a) 缺失/不完整

1. 工单 02–19 首条验收项(收录完整、不遗漏、不补写)全部未勾选;工单 19"逐页对照 404 页核验"未勾选,Comments 自认"未逐页人工目检"——覆盖完整性遗留人工验收(spec《全局验收》:"逐页视觉核对为代码完整性的依据")。
2. 已跟踪文件 `AGENTS.md` 被修改(分支命名规范英文化、删除过时的"尚无首个提交"说明),与整理代码的工单无关,属未声明改动;且新规则要求英文分支名,与当前分支名 `feat/20260929-数据结构代码整理` 自相矛盾。
3. 第 4 章 questions/answers 仅 README、第 5 章 questions 仅 2 个类型定义——与索引"书未印代码"声明一致,符合 spec 不补写原则,但结论依赖上述未完成的人工核验。

### (b) 超范围行为

无实质 scope creep。第 8 章 PDF403 伪代码转写、第 4/5 章派生实现均属 spec"伪代码转 C17/补足最小编译上下文"授权内且单列;B 树/散列、基数与外部排序、数组矩阵均按"未印代码不补写"处理。

### (c) 可疑实现(经核实为忠实转写,非问题)

- 第 2 章第 9 题书印函数名 `Union` 实为交集逻辑,索引如实记录未擅改。
- 第 8 章 `setPartition` 保留原书行为并自注非全局最优。
- 两处"约 333/约 391"页码系二维码遮挡推算,有脚注,非占位符。

### 章节覆盖结论

| 章节 | 结论 | 说明 |
| --- | --- | --- |
| 第 1 章 绪论 | 符合 | 21 条全有页码与测试 |
| 第 2 章 链表 | 符合 | 38 条,`Union` 命名冲突已记录 |
| 第 3 章 栈与队列 | 符合 | 40 块,接口题只留声明 |
| 第 4 章 串 | 符合 | 正文 6 块,题/答声明无印刷代码 |
| 第 5 章 树 | 符合 | 46 块+派生单列 |
| 第 6 章 图 | 符合 | 28 块,题型只留类型 |
| 第 7 章 查找 | 符合 | 15 块,B 树/散列明示无码 |
| 第 8 章 排序 | 符合 | 28 块+1 段伪代码转写,页码推算有脚注 |

## 汇总

- **Standards 轴**:7 条(1 硬违规 + 6 判断题)。最重:`tree_solutions.c` 三个辅助函数缺中文功能注释(spec 硬性要求,需修复)。
- **Spec 轴**:5 条发现(3 条待办/提示、2 条核实为非问题)。最重:全书 404 页逐页人工核对尚未执行——代码完整性的最终验收闸门还开着。

## 修复与用户决策

- `tree_solutions.c` 三个辅助函数已补中文功能注释；循环队列下标校验已提取为共享辅助函数，并加入无效下标测试。
- 图题型保留同构结构体的原因已写入注释；第 8 章首元素枢轴划分已在代码索引中互相引用。
- 用户确认采用英文分支命名，保留 `AGENTS.md` 中的英文命名约定。
- 用户确认全书覆盖采用“404 页全页 OCR 定位 + 所有代码候选页视觉核对和索引交叉检查”，无需再对非候选页逐页人工目检；规格和工单已据此更新。
- 动态数组扩容与局部交换 helper 属于非阻断的结构异味，本次保留现状以维持各容器约定和代码溯源性。
