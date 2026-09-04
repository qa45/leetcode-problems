#include "test.h"

#include "solution.c"

static void freeRows(int **rows, size_t rowCount, size_t *colSizes)
{
    if (rows != NULL) {
        for (size_t row = 0; row < rowCount; ++row) {
            free(rows[row]);
        }
    }
    free(rows);
    free(colSizes);
}

static bool expectRows(MiniDb *db, int tableId, char **conditions,
                       size_t conditionsSize, const int *expected,
                       size_t expectedRows, size_t expectedCols)
{
    size_t actualRows = 0;
    size_t *actualColSizes = NULL;
    int **actual = MiniDbSelect(db, tableId, conditions, conditionsSize,
                                &actualRows, &actualColSizes);
    bool equal = actualRows == expectedRows;

    if (equal && expectedRows > 0U) {
        equal = actual != NULL && actualColSizes != NULL;
    }
    for (size_t row = 0; equal && row < actualRows; ++row) {
        if (actual[row] == NULL || actualColSizes[row] != expectedCols) {
            equal = false;
            break;
        }
        for (size_t col = 0; col < expectedCols; ++col) {
            if (actual[row][col] != expected[row * expectedCols + col]) {
                equal = false;
                break;
            }
        }
    }

    freeRows(actual, actualRows, actualColSizes);
    return equal;
}

static void testExampleOne(void)
{
    MiniDb *db = MiniDbInit();
    MiniDbCreate(db, 1, 3, "a");
    const int row1[] = {2, 3, 7};
    const int row2[] = {4, 5, 6};
    const int row3[] = {3, 4, 6};
    MiniDbInsert(db, 1, row1, 3);
    MiniDbInsert(db, 1, row2, 3);
    MiniDbInsert(db, 1, row3, 3);

    char condition1[] = "b=5";
    char condition2[] = "c=6";
    char *conditions[] = {condition1, condition2};
    const int expected[] = {4, 5, 6};
    EXPECT_TRUE(expectRows(db, 1, conditions, 2, expected, 1, 3));
    MiniDbFree(db);
}

static void testExampleTwo(void)
{
    MiniDb *db = MiniDbInit();
    MiniDbCreate(db, 2, 4, "ba");
    const int table2Row1[] = {9, 23, 47, 41};
    MiniDbInsert(db, 2, table2Row1, 4);
    MiniDbCreate(db, 3, 3, "ca");
    const int table2Row2[] = {10, 20, 47, 99};
    const int table2Row3[] = {10, 23, 47, 58};
    const int table3Row1[] = {9, 555, 47};
    const int table3Row2[] = {9, 23, 47};
    MiniDbInsert(db, 2, table2Row2, 4);
    MiniDbInsert(db, 2, table2Row3, 4);
    MiniDbInsert(db, 3, table3Row1, 3);
    MiniDbInsert(db, 3, table3Row2, 3);

    char conditionC[] = "c=47";
    char *conditionsC[] = {conditionC};
    const int expectedTable2[] = {
        10, 20, 47, 99,
        9,  23, 47, 41,
        10, 23, 47, 58,
    };
    EXPECT_TRUE(expectRows(db, 2, conditionsC, 1, expectedTable2, 3, 4));

    char conditionA[] = "a=9";
    char conditionB[] = "b=555";
    char *missingConditions[] = {conditionA, conditionB};
    EXPECT_TRUE(expectRows(db, 2, missingConditions, 2, NULL, 0, 4));

    char *table3Conditions[] = {conditionA};
    const int expectedTable3[] = {9, 555, 47};
    EXPECT_TRUE(expectRows(db, 3, table3Conditions, 1, expectedTable3, 1, 3));
    MiniDbFree(db);
}

static void testDuplicateCreateAndPrimaryKey(void)
{
    MiniDb *db = MiniDbInit();
    MiniDbCreate(db, 10000, 2, "ba");
    MiniDbCreate(db, 10000, 1, "a");

    const int original[] = {0, 10000};
    const int conflicting[] = {0, 10000};
    const int distinct[] = {10000, 10000};
    MiniDbInsert(db, 10000, original, 2);
    MiniDbInsert(db, 10000, conflicting, 2);
    MiniDbInsert(db, 10000, distinct, 2);

    char condition[] = "b=10000";
    char *conditions[] = {condition};
    const int expected[] = {0, 10000, 10000, 10000};
    EXPECT_TRUE(expectRows(db, 10000, conditions, 1, expected, 2, 2));
    MiniDbFree(db);
}

int main(void)
{
    testExampleOne();
    testExampleTwo();
    testDuplicateCreateAndPrimaryKey();
    return finishTests();
}
