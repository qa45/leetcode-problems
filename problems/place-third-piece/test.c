#include "test.h"

#include "solution.c"

static bool checkCase(int point1[2], int point2[2],
                      int expectedX, int expectedY)
{
    int returnSize = 0;
    int *result = placeThirdPiece(point1, 2, point2, 2, &returnSize);
    bool passed = result != NULL && returnSize == 2 &&
                  result[0] == expectedX && result[1] == expectedY;

    free(result);
    return passed;
}

int main(void)
{
    /* 官方示例 */
    int example1Point1[] = {1, 1};
    int example1Point2[] = {2, 1};
    int example2Point1[] = {1, 1};
    int example2Point2[] = {3, 1};
    int example3Point1[] = {0, 0};
    int example3Point2[] = {1, 1};
    int example4Point1[] = {1, 1};
    int example4Point2[] = {4, 1};

    EXPECT_TRUE(checkCase(example1Point1, example1Point2, 0, 1));
    EXPECT_TRUE(checkCase(example2Point1, example2Point2, 2, 1));
    EXPECT_TRUE(checkCase(example3Point1, example3Point2, 2, 2));
    EXPECT_TRUE(checkCase(example4Point1, example4Point2, -1, -1));

    /* 垂直方向：x 相同时选择 y 较小的位置 */
    int verticalPoint1[] = {5, 7};
    int verticalPoint2[] = {5, 8};
    EXPECT_TRUE(checkCase(verticalPoint1, verticalPoint2, 5, 6));

    /* 135° 斜线与棋盘边界 */
    int diagonalPoint1[] = {0, 18};
    int diagonalPoint2[] = {1, 17};
    EXPECT_TRUE(checkCase(diagonalPoint1, diagonalPoint2, 2, 16));

    /* 两点相距两格时填补中间位置 */
    int gapPoint1[] = {16, 16};
    int gapPoint2[] = {18, 18};
    EXPECT_TRUE(checkCase(gapPoint1, gapPoint2, 17, 17));

    /* 输入顺序不影响候选位置的字典序选择 */
    int reversedPoint1[] = {2, 2};
    int reversedPoint2[] = {1, 1};
    EXPECT_TRUE(checkCase(reversedPoint1, reversedPoint2, 0, 0));

    /* 两点不在允许的四种方向上 */
    int invalidDirectionPoint1[] = {1, 1};
    int invalidDirectionPoint2[] = {2, 3};
    EXPECT_TRUE(checkCase(invalidDirectionPoint1, invalidDirectionPoint2,
                          -1, -1));

    return finishTests();
}
