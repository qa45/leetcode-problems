#include "test.h"

#include "solution.c"

int main(void)
{
    /* 题目示例 */
    int example1[] = {5, 5, 5, 10, 20};
    int example2[] = {5, 5, 10, 10, 20};

    EXPECT_TRUE(lemonadeChange(example1, 5));
    EXPECT_TRUE(!lemonadeChange(example2, 5));

    /* 最小规模：第一位顾客是否需要找零 */
    int singleFive[] = {5};
    int singleTen[] = {10};
    int singleTwenty[] = {20};

    EXPECT_TRUE(lemonadeChange(singleFive, 1));
    EXPECT_TRUE(!lemonadeChange(singleTen, 1));
    EXPECT_TRUE(!lemonadeChange(singleTwenty, 1));

    /* 一张 20 美元可用 10 美元和 5 美元组合找零 */
    int mixedChange[] = {5, 5, 10, 20};
    EXPECT_TRUE(lemonadeChange(mixedChange, 4));

    /* 总金额充足不代表持有的钞票组合能够正确找零 */
    int unusableTens[] = {5, 5, 10, 10, 20};
    EXPECT_TRUE(!lemonadeChange(unusableTens, 5));

    /* 较长队列中连续使用两种找零组合 */
    int longQueue[] = {5, 5, 10, 20, 5, 5, 5, 5, 5, 5,
                       5, 5, 5, 10, 5, 5, 20, 5, 20, 5};
    EXPECT_TRUE(lemonadeChange(longQueue, 20));

    return finishTests();
}
