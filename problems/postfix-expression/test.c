#include "test.h"

/*
 * 直接包含答案文件后，static 函数也处于同一个编译单元中，
 * 因而可以从这个本地测试入口调用。
 */
#include "solution.c"

int main(void)
{
    /* 题目示例 */
    EXPECT_INT_EQ(5, Calc("9,3,5,-,2,*,+"));
    EXPECT_INT_EQ(-7, Calc("3,-3,-,2,/,10,-"));

    /* 单个操作数和负数 */
    EXPECT_INT_EQ(42, Calc("42"));
    EXPECT_INT_EQ(-42, Calc("-42"));

    /* 检查左右操作数顺序 */
    EXPECT_INT_EQ(7, Calc("10,3,-"));
    EXPECT_INT_EQ(4, Calc("20,5,/"));

    /* C99/C17 的整数除法会向 0 截断 */
    EXPECT_INT_EQ(-1, Calc("-5,3,/"));
    EXPECT_INT_EQ(-1, Calc("5,-3,/"));
    EXPECT_INT_EQ(1, Calc("-5,-3,/"));

    return finishTests();
}
