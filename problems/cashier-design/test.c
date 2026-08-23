#include "test.h"

#include "solution.c"

static bool expectCashes(const int initCashes[4], const Payment payments[],
                         int paymentsSize, const int expected[5])
{
    int returnSize = 0;
    int *actual = cashierCheckout(initCashes, payments, paymentsSize, &returnSize);
    bool equal = actual != NULL && returnSize == 5;

    if (equal) {
        for (int i = 0; i < returnSize; ++i) {
            if (actual[i] != expected[i]) {
                equal = false;
                break;
            }
        }
    }

    free(actual);
    return equal;
}

int main(void)
{
    /* 题目样例：同一笔收到的钞票可以参与本次找零。 */
    const int exampleInit[] = {5, 2, 5, 1};
    const Payment examplePayments[] = {
        {47, {0, 0, 0, 0, 1}},
        {2, {0, 1, 0, 0, 0}},
        {1, {1, 0, 0, 1, 0}},
    };
    const int exampleExpected[] = {3, 2, 5, 0, 1};
    EXPECT_TRUE(expectCashes(exampleInit, examplePayments, 3, exampleExpected));

    /* 付款金额恰好等于价格，所有收到的钞票均进入收银台。 */
    const int exactInit[] = {0, 0, 0, 0};
    const Payment exactPayments[] = {
        {6, {1, 1, 0, 0, 0}},
    };
    const int exactExpected[] = {1, 1, 0, 0, 0};
    EXPECT_TRUE(expectCashes(exactInit, exactPayments, 1, exactExpected));

    /* 付款不足时整笔失败，收银台状态不变。 */
    const int underpaidInit[] = {1, 2, 3, 4};
    const Payment underpaidPayments[] = {
        {10, {0, 1, 0, 0, 0}},
    };
    const int underpaidExpected[] = {1, 2, 3, 4, 0};
    EXPECT_TRUE(expectCashes(underpaidInit, underpaidPayments, 1,
                             underpaidExpected));

    /* 总付款足够但无法组合出找零金额时，收到的钞票全部退回。 */
    const int noChangeInit[] = {0, 0, 0, 0};
    const Payment noChangePayments[] = {
        {1, {0, 1, 0, 0, 0}},
    };
    const int noChangeExpected[] = {0, 0, 0, 0, 0};
    EXPECT_TRUE(expectCashes(noChangeInit, noChangePayments, 1,
                             noChangeExpected));

    /* 找零 10 元时应使用一张 10 元，而不是两张 5 元。 */
    const int minimumNotesInit[] = {0, 2, 1, 0};
    const Payment minimumNotesPayments[] = {
        {40, {0, 0, 0, 1, 0}},
    };
    const int minimumNotesExpected[] = {0, 2, 0, 1, 0};
    EXPECT_TRUE(expectCashes(minimumNotesInit, minimumNotesPayments, 1,
                             minimumNotesExpected));

    /* 没有 10 元钞票时，应改用两张 5 元完成 10 元找零。 */
    const int smallerNotesInit[] = {0, 2, 0, 0};
    const Payment smallerNotesPayments[] = {
        {40, {0, 0, 0, 1, 0}},
    };
    const int smallerNotesExpected[] = {0, 0, 0, 1, 0};
    EXPECT_TRUE(expectCashes(smallerNotesInit, smallerNotesPayments, 1,
                             smallerNotesExpected));

    return finishTests();
}
