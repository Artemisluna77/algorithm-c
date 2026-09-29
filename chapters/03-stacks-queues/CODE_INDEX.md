# 第 3 章代码索引：栈、队列和数组应用

本章源码与测试使用纯 C17，整理覆盖 PDF 第 75–120 页（书页第 63–108 页），分别按 `body/` 正文、`questions/` 试题和 `answers/` 答案解析归档。每个列出的代码块均在对应源码或头文件上方标注功能、章节/小节及 PDF 页码和书页；测试通过公开函数和结构体操作验证。

## 正文

| 编号 | 功能/代码块 | PDF 页码 | 书页 | 源文件 | 测试用例 |
| --- | --- | ---: | ---: | --- | --- |
| C03-B-001 | 顺序栈数组与栈顶指针定义 | 76 | 64 | `body/sequential_stack.h` | `seq_stack_init` |
| C03-B-002 | 初始化顺序栈 | 77 | 65 | `body/init_stack.c` | `seq_stack_init` |
| C03-B-003 | 判断顺序栈是否为空 | 77 | 65 | `body/stack_empty.c` | `seq_stack_empty` |
| C03-B-004 | 顺序栈入栈 | 77 | 65 | `body/push.c` | `seq_stack_push` |
| C03-B-005 | 顺序栈出栈 | 77 | 65 | `body/pop.c` | `seq_stack_pop` |
| C03-B-006 | 读取顺序栈栈顶 | 78 | 66 | `body/get_top.c` | `seq_stack_get_top` |
| C03-B-007 | 链栈结点定义 | 78 | 66 | `body/linked_stack_node.h` | `link_stack_node` |
| C03-B-008 | 顺序循环队列定义 | 89 | 77 | `body/circular_queue.h` | `circular_queue_init` |
| C03-B-009 | 初始化循环队列 | 90 | 78 | `body/init_circular_queue.c` | `circular_queue_init` |
| C03-B-010 | 判断循环队列是否为空 | 90 | 78 | `body/circular_queue_empty.c` | `circular_queue_init` |
| C03-B-011 | 循环队列入队及队满判断 | 90 | 78 | `body/circular_enqueue.c` | `circular_queue_enqueue` |
| C03-B-012 | 循环队列出队及队空判断 | 90–91 | 78–79 | `body/circular_dequeue.c` | `circular_queue_dequeue` |
| C03-B-013 | 链式队列结点与队列定义 | 91 | 79 | `body/linked_queue.h` | `linked_queue_init` |
| C03-B-014 | 初始化带头结点的链式队列 | 91 | 79 | `body/linked_queue_init.c` | `linked_queue_init` |
| C03-B-015 | 判断链式队列是否为空 | 91–92 | 79–80 | `body/linked_queue_empty.c` | `linked_queue_init` |
| C03-B-016 | 链式队列入队 | 92 | 80 | `body/linked_enqueue.c` | `linked_queue_enqueue` |
| C03-B-017 | 链式队列出队 | 92 | 80 | `body/linked_dequeue.c` | `linked_queue_dequeue` |
| C03-B-018 | 递归计算 Fibonacci 数列 | 104 | 92 | `body/fibonacci.c` | `fibonacci` |
| C03-B-019 | 声明并初始化总结示例中的顺序栈 | 120 | 108 | `body/summary_stack.h`, `body/summary_stack_init.c` | `summary_stack_init` |
| C03-B-020 | 总结示例的顺序栈入栈语句 | 120 | 108 | `body/summary_stack_push.c` | `summary_stack_push` |
| C03-B-021 | 总结示例的顺序栈出栈语句 | 120 | 108 | `body/summary_stack_pop.c` | `summary_stack_pop` |

## 试题

| 编号 | 功能/代码块 | PDF 页码 | 书页 | 源文件 | 测试用例 |
| --- | --- | ---: | ---: | --- | --- |
| C03-Q-003A | 综合应用题03给出的栈操作接口 `Push`、`Pop`、`StackEmpty`、`StackOverflow` | 96 | 84 | `questions/q03_stack_queue_api.h` | `provided_stack_queue_interfaces` |
| C03-Q-003B | 综合应用题03待实现队列的 `Enqueue`、`Dequeue`、`QueueEmpty` 接口 | 96 | 84 | `questions/q03_stack_queue_api.h` | `provided_stack_queue_interfaces` |
| C03-Q-005 | 计算递归表达式 `f(f(1))` | 106 | 94 | `questions/q05_recursive_expression.c` | `q05_recursive_expression` |
| C03-Q-006 | 按递归定义计算调用次数函数 | 107 | 95 | `questions/q06_recursive_calls.c` | `q06_recursive_calls` |
| C03-Q-007 | 跟踪 `func(func(5))` 的递归调用次序 | 107 | 95 | `questions/q07_recursive_order.c` | `q07_recursive_order` |
| C03-Q-015 | 递归计算 `S(n)` | 107 | 95 | `questions/q15_recursive_sum.c` | `q15_recursive_sum` |

## 答案与解析

| 编号 | 功能/代码块 | PDF 页码 | 书页 | 源文件 | 测试用例 |
| --- | --- | ---: | ---: | --- | --- |
| C03-A-001 | 判断入栈/出栈操作序列是否合法 | 86 | 74 | `answers/judge_stack_sequence.c` | `judge_stack_sequence` |
| C03-A-002 | 用栈判断链表字符序列是否回文 | 86 | 74 | `answers/list_palindrome.c` | `list_palindrome` |
| C03-A-003 | 共享栈数组及两个栈顶定义 | 87 | 75 | `answers/shared_stack.h` | `shared_stack_init` |
| C03-A-004 | 初始化共享栈 | 87 | 75 | `answers/shared_stack_init.c` | `shared_stack_init` |
| C03-A-005 | 共享栈入栈 | 87 | 75 | `answers/shared_stack_push.c` | `shared_stack_push` |
| C03-A-006 | 共享栈出栈 | 87–88 | 75–76 | `answers/shared_stack_pop.c` | `shared_stack_pop` |
| C03-A-007 | 带 tag 标记的循环队列入队 | 99 | 87 | `answers/tagged_queue_enqueue.c` | `tagged_queue_enqueue` |
| C03-A-008 | 带 tag 标记的循环队列出队 | 99–100 | 87–88 | `answers/tagged_queue_dequeue.c` | `tagged_queue_dequeue` |
| C03-A-009 | 借助栈反转队列 | 100 | 88 | `answers/inverse_queue.c` | `inverse_queue` |
| C03-A-010 | 双栈队列入队及输入栈满时的倒栈处理 | 100 | 88 | `answers/two_stack_queue_enqueue.c` | `two_stack_enqueue` |
| C03-A-011 | 双栈队列出队 | 100–101 | 88–89 | `answers/two_stack_queue_dequeue.c` | `two_stack_dequeue` |
| C03-A-012 | 判断双栈队列是否为空 | 101 | 89 | `answers/two_stack_queue_empty.c` | `two_stack_empty` |
| C03-A-013 | 用栈检查圆括号、方括号和花括号匹配 | 112 | 100 | `answers/brackets_check.c` | `brackets_check` |

## 范围核对

- PDF 第 75–120 页均以 OCR 文本定位候选，再逐页渲染并视觉核对代码区；OCR 仅用于辅助定位。
- 试题选项中的单条入栈/出栈表达式、指针更新式和公式不是完整程序代码块，未扩写为答案。PDF 第 96 页综合应用题03的两个灰底块是操作接口而非算法；已转换为 `questions/q03_stack_queue_api.h` 中的 C17 函数声明，未补写函数体。PDF 第 113–119 页的数组与特殊矩阵内容为表示式、公式和图示，没有完整程序代码块。
- PDF 第 120 页的最小值栈是设计题，正文只给出文字提示和一条 `stack_min` 更新语句，没有印出完整算法；因此未补写实现。
- 本章整理 40 个代码块：正文 21 个、试题 6 个、答案与解析 13 个；CTest 注册 33 个用例：正文 16 个、试题 5 个、答案与解析 12 个。题目接口块使用编译期签名检查，不虚构运行时算法。
