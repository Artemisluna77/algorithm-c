# 《2027数据结构》算法代码（C17）

本项目按章节整理 PDF 正文、试题和答案解析中的代码块，并将代码统一实现为 C17。C17 原生支持取地址运算符 `&` 与指针；书中依赖 C++ 的引用、类、模板和标准容器则改写为 C 结构体、指针、数组及显式长度/状态参数。伪代码也转换为可编译、可测试的 C，不另存伪代码版本。

## 构建与测试

在 CLion 中打开本目录，等待 CMake 配置完成后，可运行各章节的测试目标。命令行构建方式：

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 目录约定

- `chapters/NN-*/body/`：正文代码
- `chapters/NN-*/questions/`：题干和选项中的代码
- `chapters/NN-*/answers/`：答案与解析中的代码
- `chapters/NN-*/tests/`：通过公开 C 函数或结构体操作调用算法的测试
- 每章 `CODE_INDEX.md`：代码块、PDF 页码、书页、源文件及测试用例索引
- `tests/test_harness.h`：轻量 C 测试工具；每个用例可作为独立 CTest 项运行

源码注释和索引保留原 PDF 页码、书内页码及代码块类别，便于回查来源。
