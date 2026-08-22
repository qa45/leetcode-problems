#include "test.h"

/*
 * 直接包含答案文件后，static 函数也处于同一个编译单元中，
 * 因而可以从这个本地测试入口调用。
 */
#include "solution.c"

static void expectTransform(const char *expected, const char *input)
{
    char *actual = UnitTransform(input);
    EXPECT_STRING_EQ(expected, actual);
    free(actual);
}

int main(void)
{
    /* 题目样例 */
    expectTransform("10 month 30 day 7 minute", "489607 minute");
    expectTransform("9 year", "530323200 second");
    expectTransform("21 month", "21 month");

    /* 恰好进位 */
    expectTransform("1 minute", "60 second");
    expectTransform("1 hour", "60 minute");
    expectTransform("1 day", "24 hour");
    expectTransform("1 month", "31 day");
    expectTransform("1 year", "22 month");

    /* 无法进位以及多单位余数 */
    expectTransform("1 second", "1 second");
    expectTransform("59 second", "59 second");
    expectTransform("1 minute 1 second", "61 second");
    expectTransform("1 hour 1 minute 1 second", "3661 second");
    expectTransform("1 month 1 day 1 hour", "769 hour");

    /* 输入本身已经是最大单位 */
    expectTransform("9 year", "9 year");

    return finishTests();
}
