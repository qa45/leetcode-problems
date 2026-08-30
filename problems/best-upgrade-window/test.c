#include "test.h"

#include <limits.h>

#include "solution.c"

#define HOURS_PER_WEEK 168

static void expectWindow(int expectedStart, int expectedEnd, int cap,
                         const int *visitCnt, size_t visitCntSize)
{
    Window actual = GetBestWindow(cap, visitCnt, visitCntSize);
    EXPECT_INT_EQ(expectedStart, actual.start);
    EXPECT_INT_EQ(expectedEnd, actual.end);
}

static void testExampleOne(void)
{
    const int daily[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1,
    };
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = daily[i % 24U];
    }

    expectWindow(22, 25, 6, visitCnt, HOURS_PER_WEEK);
}

static void testExampleTwo(void)
{
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = 1;
    }
    visitCnt[166] = 167;

    expectWindow(167, 165, 167, visitCnt, HOURS_PER_WEEK);
}

static void testExampleThree(void)
{
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = 1;
    }

    expectWindow(0, 167, 200, visitCnt, HOURS_PER_WEEK);
}

static void testNoWindow(void)
{
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = 1;
    }

    expectWindow(-1, -1, 0, visitCnt, HOURS_PER_WEEK);
}

static void testZeroCapAndFullCycle(void)
{
    int visitCnt[HOURS_PER_WEEK] = {0};
    expectWindow(0, 167, 0, visitCnt, HOURS_PER_WEEK);
}

static void testSmallestStartWins(void)
{
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = 1;
    }

    expectWindow(0, 1, 2, visitCnt, HOURS_PER_WEEK);
}

static void testSumDoesNotOverflowInt(void)
{
    int visitCnt[HOURS_PER_WEEK];

    for (size_t i = 0; i < HOURS_PER_WEEK; ++i) {
        visitCnt[i] = INT_MAX;
    }

    expectWindow(0, 0, INT_MAX, visitCnt, HOURS_PER_WEEK);
}

int main(void)
{
    testExampleOne();
    testExampleTwo();
    testExampleThree();
    testNoWindow();
    testZeroCapAndFullCycle();
    testSmallestStartWins();
    testSumDoesNotOverflowInt();
    return finishTests();
}
