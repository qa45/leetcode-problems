#include "test.h"

#include "solution.c"

static bool checkCase(int *nums, int numsSize, int target)
{
    int returnSize = 0;
    int *result = twoSum(nums, numsSize, target, &returnSize);

    bool passed = result != NULL && returnSize == 2 &&
                  result[0] >= 0 && result[0] < numsSize &&
                  result[1] >= 0 && result[1] < numsSize &&
                  result[0] != result[1] &&
                  nums[result[0]] + nums[result[1]] == target;

    free(result);
    return passed;
}

int main(void)
{
    int case1[] = {2, 7, 11, 15};
    int case2[] = {3, 2, 4};
    int case3[] = {3, 3};

    EXPECT_TRUE(checkCase(case1, 4, 9));
    EXPECT_TRUE(checkCase(case2, 3, 6));
    EXPECT_TRUE(checkCase(case3, 2, 6));

    return finishTests();
}
