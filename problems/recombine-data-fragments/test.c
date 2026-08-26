#include "test.h"

#include "solution.c"

static void expectRecombine(
    const char *expected,
    const DataFragment *dataFragments,
    size_t dataFragmentsSize,
    int dstType)
{
    char *actual = Recombine(dataFragments, dataFragmentsSize, dstType);
    EXPECT_STRING_EQ(expected, actual);
    free(actual);
}

int main(void)
{
    /* 样例 1：乱序且混有其他数据类型。 */
    DataFragment example1[] = {
        {0, 1, 0, 5, "hello"},
        {1, 2, 1, 2, "CC"},
        {0, 3, 1, 5, "world"},
        {0, 0, 0, 3, "Say"},
        {1, 0, 0, 2, "AA"},
        {0, 2, 0, 2, "to"},
        {1, 1, 0, 2, "BB"},
    };
    expectRecombine("Sayhellotoworld", example1,
                    sizeof(example1) / sizeof(example1[0]), 0);

    /* 样例 2：缺少 index 0。 */
    DataFragment example2[] = {
        {9, 2, 1, 5, "world"},
        {9, 1, 0, 5, "hello"},
    };
    expectRecombine("NA", example2,
                    sizeof(example2) / sizeof(example2[0]), 9);

    /* 单个分段也可以组成完整数据包。 */
    DataFragment single[] = {
        {3, 0, 1, 2, "OK"},
    };
    expectRecombine("OK", single, sizeof(single) / sizeof(single[0]), 3);

    /* 重复分段只拼接一次。 */
    DataFragment duplicates[] = {
        {4, 1, 1, 2, "BB"},
        {4, 0, 0, 2, "AA"},
        {4, 0, 0, 2, "AA"},
        {4, 1, 1, 2, "BB"},
    };
    expectRecombine("AABB", duplicates,
                    sizeof(duplicates) / sizeof(duplicates[0]), 4);

    /* 每个分段都达到最大净荷长度，检查结果空间是否包含 '\0'。 */
    DataFragment maxPayloadLength[] = {
        {2, 2, 1, 5, "KLMNO"},
        {2, 0, 0, 5, "ABCDE"},
        {2, 1, 0, 5, "FGHIJ"},
    };
    expectRecombine("ABCDEFGHIJKLMNO", maxPayloadLength,
                    sizeof(maxPayloadLength) / sizeof(maxPayloadLength[0]), 2);

    /* 中间序号缺失。 */
    DataFragment missingMiddle[] = {
        {5, 0, 0, 2, "AA"},
        {5, 2, 1, 2, "CC"},
    };
    expectRecombine("NA", missingMiddle,
                    sizeof(missingMiddle) / sizeof(missingMiddle[0]), 5);

    /* 最大序号没有结束标志。 */
    DataFragment noEndFlag[] = {
        {6, 0, 0, 2, "AA"},
        {6, 1, 0, 2, "BB"},
    };
    expectRecombine("NA", noEndFlag,
                    sizeof(noEndFlag) / sizeof(noEndFlag[0]), 6);

    /* 没有目标类型的分段。 */
    DataFragment otherType[] = {
        {7, 0, 1, 2, "AA"},
    };
    expectRecombine("NA", otherType,
                    sizeof(otherType) / sizeof(otherType[0]), 8);

    /* 非目标类型的最大合法 index 不应影响目标数据包。 */
    DataFragment unrelatedMaxIndex[] = {
        {1, 0, 1, 2, "OK"},
        {9, 100000, 1, 5, "other"},
    };
    expectRecombine("OK", unrelatedMaxIndex,
                    sizeof(unrelatedMaxIndex) / sizeof(unrelatedMaxIndex[0]), 1);

    /* 目标类型使用最大合法 index，但中间分段缺失。 */
    DataFragment targetMaxIndexWithGap[] = {
        {2, 0, 0, 2, "AA"},
        {2, 100000, 1, 2, "ZZ"},
    };
    expectRecombine("NA", targetMaxIndexWithGap,
                    sizeof(targetMaxIndexWithGap) /
                        sizeof(targetMaxIndexWithGap[0]),
                    2);

    return finishTests();
}
