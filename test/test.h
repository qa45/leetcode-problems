#ifndef LEETCODE_TEST_H
#define LEETCODE_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int passed;
    int failed;
} LeetCodeTestStats;

static LeetCodeTestStats leetcodeTestStats = {0, 0};

#define NEXT_TEST_CASE()                                                        \
    (leetcodeTestStats.passed + leetcodeTestStats.failed + 1)

#define EXPECT_TRUE(condition)                                                  \
    do {                                                                        \
        bool testActual = (condition);                                          \
        int testCaseNumber = NEXT_TEST_CASE();                                  \
        if (testActual) {                                                       \
            ++leetcodeTestStats.passed;                                         \
            printf("[PASS] case %d\n", testCaseNumber);                       \
        } else {                                                                \
            ++leetcodeTestStats.failed;                                         \
            printf("[FAIL] case %d\n  expect: true\n  actual: false\n",    \
                   testCaseNumber);                                             \
        }                                                                       \
    } while (0)

#define EXPECT_INT_EQ(expectedExpression, actualExpression)                     \
    do {                                                                        \
        int testExpected = (expectedExpression);                                \
        int testActual = (actualExpression);                                    \
        int testCaseNumber = NEXT_TEST_CASE();                                  \
        if (testExpected == testActual) {                                       \
            ++leetcodeTestStats.passed;                                         \
            printf("[PASS] case %d\n", testCaseNumber);                       \
        } else {                                                                \
            ++leetcodeTestStats.failed;                                         \
            printf("[FAIL] case %d\n  expect: %d\n  actual: %d\n",         \
                   testCaseNumber, testExpected, testActual);                   \
        }                                                                       \
    } while (0)

#define EXPECT_STRING_EQ(expectedExpression, actualExpression)                  \
    do {                                                                        \
        const char *testExpected = (expectedExpression);                        \
        const char *testActual = (actualExpression);                            \
        bool testEqual = testExpected == NULL                                   \
                             ? testActual == NULL                               \
                             : testActual != NULL &&                            \
                                   strcmp(testExpected, testActual) == 0;        \
        int testCaseNumber = NEXT_TEST_CASE();                                  \
        if (testEqual) {                                                        \
            ++leetcodeTestStats.passed;                                         \
            printf("[PASS] case %d\n", testCaseNumber);                       \
        } else {                                                                \
            ++leetcodeTestStats.failed;                                         \
            printf("[FAIL] case %d\n  expect: \"%s\"\n  actual: \"%s\"\n", \
                   testCaseNumber,                                              \
                   testExpected == NULL ? "(null)" : testExpected,            \
                   testActual == NULL ? "(null)" : testActual);                \
        }                                                                       \
    } while (0)

static int finishTests(void)
{
    int total = leetcodeTestStats.passed + leetcodeTestStats.failed;
    printf("\nTests: %d/%d passed\n", leetcodeTestStats.passed, total);
    return leetcodeTestStats.failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif
