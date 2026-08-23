#include "test.h"

#include "solution.c"

int main(void)
{
    /* 题目示例 */
    char *case1[] = {"5", "2", "C", "D", "+"};
    char *case2[] = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    char *case3[] = {"1"};

    EXPECT_INT_EQ(30, calPoints(case1, 5));
    EXPECT_INT_EQ(27, calPoints(case2, 8));
    EXPECT_INT_EQ(1, calPoints(case3, 1));

    /* 移除后应恢复到更早的有效得分 */
    char *cancelAndReuse[] = {"10", "20", "C", "D", "+"};
    EXPECT_INT_EQ(60, calPoints(cancelAndReuse, 5));

    /* 负数也可以参与翻倍和相加 */
    char *negativeScores[] = {"-5", "-3", "+", "D"};
    EXPECT_INT_EQ(-32, calPoints(negativeScores, 4));

    /* 得分可以被连续撤销，最终记录也可能为空 */
    char *allCancelled[] = {"7", "C", "-2", "C"};
    EXPECT_INT_EQ(0, calPoints(allCancelled, 4));

    return finishTests();
}
