# LeetCode C 本地刷题环境

本目录使用 Windows + VS Code + MSYS2 UCRT64 GCC/GDB。代码按 LeetCode 的函数接口组织，不需要在答案文件中处理标准输入输出。

项目的构建、运行、调试任务会自动把 `C:\msys64\ucrt64\bin` 加到进程的 `PATH`，确保 GCC 的子进程可以加载 MSYS2 提供的 DLL；不要求修改 Windows 的全局环境变量。

## 目录约定

每道题单独放在一个目录中：

```text
problems/
└── 0001-two-sum/
    ├── solution.c   # 提交到 LeetCode 的函数实现
    └── test.c       # 仅用于本地测试，包含 main
```

`test.c` 通过 `#include "solution.c"` 引入答案，因此构建时只编译 `test.c`。提交时只复制 `solution.c` 中的内容，不要提交 `test.c`。

公共测试工具位于 `test/test.h`，目前提供：

- `EXPECT_TRUE(condition)`：检查任意条件；
- `EXPECT_INT_EQ(expected, actual)`：检查整数返回值；
- `EXPECT_STRING_EQ(expected, actual)`：检查字符串返回值；
- `finishTests()`：打印汇总并返回适合程序退出的状态码。

## 在 VS Code 中使用

1. 打开某道题目录下的 `solution.c` 或 `test.c`，确保它是当前活动文件。
2. 按 `Ctrl+Shift+B` 构建当前题目。
3. 运行任务 `C: run current problem` 可构建并运行测试。
4. 在 `solution.c` 中设置断点，按 `F5` 选择 `C: debug current problem` 进行调试。

编译参数包含 C17、常用警告、调试符号和关闭优化：

```text
-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g3 -O0
```

## 新建一道题

可以参考 `problems/postfix-expression/test.c`。每道题的通用骨架是：

```c
#include "test.h"
#include "solution.c"

int main(void)
{
    EXPECT_INT_EQ(期望值, 待测试函数(参数));
    return finishTests();
}
```

新建题目目录后：

1. 把 `solution.c` 改成题目给定的函数接口和你的实现。
2. 在 `test.c` 中为该函数准备测试用例。
3. 保留 `#include "solution.c"`。

若 LeetCode 题目定义了 `struct ListNode`、`struct TreeNode` 等类型，本地测试时需要在 `test.c` 的 `#include "solution.c"` 之前补上相同的结构体定义；提交时不要重复平台已经提供的定义。
