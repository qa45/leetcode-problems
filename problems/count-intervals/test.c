#include "test.h"

/*
 * 直接包含答案文件后，static 函数也处于同一个编译单元中，
 * 因而可以从这个本地测试入口调用。
 */
#include "solution.c"

int main(void)
{
    /* 题目示例 */
    const int example[] = {2, 0, 2, 0, 2};
    EXPECT_INT_EQ(8,
                  CountIntervals(example,
                                 sizeof(example) / sizeof(example[0]),
                                 (LengthRange){2, 4},
                                 1));

    /* 最小规模及 threshold 为 0 */
    const int singleZero[] = {0};
    EXPECT_INT_EQ(1,
                  CountIntervals(singleZero,
                                 sizeof(singleZero) / sizeof(singleZero[0]),
                                 (LengthRange){1, 1},
                                 0));

    /* 所有合法长度的区间都满足条件 */
    const int allEqual[] = {5, 5, 5};
    EXPECT_INT_EQ(6,
                  CountIntervals(allEqual,
                                 sizeof(allEqual) / sizeof(allEqual[0]),
                                 (LengthRange){1, 3},
                                 5));

    /* 只检查固定长度，覆盖长度范围的闭区间边界 */
    const int fixedLength[] = {1, 2, 3, 4};
    EXPECT_INT_EQ(2,
                  CountIntervals(fixedLength,
                                 sizeof(fixedLength) / sizeof(fixedLength[0]),
                                 (LengthRange){2, 2},
                                 2));

    /* 平均值不能整除时仍需按真实大小判断 */
    const int fractionalAverage[] = {1, 2, 4};
    EXPECT_INT_EQ(1,
                  CountIntervals(fractionalAverage,
                                 sizeof(fractionalAverage) /
                                     sizeof(fractionalAverage[0]),
                                 (LengthRange){2, 2},
                                 2));

    /* 没有任何区间达到阈值 */
    const int belowThreshold[] = {1, 1, 1, 1};
    EXPECT_INT_EQ(0,
                  CountIntervals(belowThreshold,
                                 sizeof(belowThreshold) /
                                     sizeof(belowThreshold[0]),
                                 (LengthRange){1, 4},
                                 2));

    /* threshold 为 0 时，长度 2 和 3 共有 3 + 2 个区间 */
    const int zeroThreshold[] = {3, 0, 4, 0};
    EXPECT_INT_EQ(5,
                  CountIntervals(zeroThreshold,
                                 sizeof(zeroThreshold) /
                                     sizeof(zeroThreshold[0]),
                                 (LengthRange){2, 3},
                                 0));

    /* 最大 recordsSize 和 maxLen，兼顾计数上界与运行效率 */
    int maximumCase[10000];
    for (size_t i = 0; i < sizeof(maximumCase) / sizeof(maximumCase[0]); ++i) {
        maximumCase[i] = 10000;
    }
    EXPECT_INT_EQ(9500500,
                  CountIntervals(maximumCase,
                                 sizeof(maximumCase) / sizeof(maximumCase[0]),
                                 (LengthRange){1, 1000},
                                 10000));

    return finishTests();
}
