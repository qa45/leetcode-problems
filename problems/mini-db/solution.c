#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MINI_DB_MAX_TABLE_ID 10000
#define MINI_DB_MAX_COLUMNS 26
#define MINI_DB_INITIAL_CAPACITY 8U

typedef struct {
    size_t colNum;
    size_t keyCount;
    unsigned char keyColumns[MINI_DB_MAX_COLUMNS];
    size_t rowCount;
    size_t rowCapacity;
    int **rows;
} MiniDbTable;

typedef struct {
    MiniDbTable *tables[MINI_DB_MAX_TABLE_ID + 1];
} MiniDb;

static int comparePrimaryKey(const MiniDbTable *table, const int *left,
                             const int *right)
{
    for (size_t i = 0; i < table->keyCount; ++i) {
        size_t column = table->keyColumns[i];
        if (left[column] < right[column]) {
            return -1;
        }
        if (left[column] > right[column]) {
            return 1;
        }
    }
    return 0;
}

static size_t findInsertPosition(const MiniDbTable *table, const int *values)
{
    size_t left = 0;
    size_t right = table->rowCount;

    while (left < right) {
        size_t middle = left + (right - left) / 2U;
        if (comparePrimaryKey(table, table->rows[middle], values) < 0) {
            left = middle + 1U;
        } else {
            right = middle;
        }
    }
    return left;
}

static bool rowMatches(const int *row, const unsigned char *conditionColumns,
                       const int *conditionValues, size_t conditionsSize)
{
    for (size_t i = 0; i < conditionsSize; ++i) {
        if (row[conditionColumns[i]] != conditionValues[i]) {
            return false;
        }
    }
    return true;
}

// 注意：该函数为类构造函数，返回的对象指针将作为其他待实现函数的入参；框架代码在调用该函数后，会输出 null（而非指针）
static MiniDb *MiniDbInit(void)
{
    return calloc(1, sizeof(MiniDb));
}

static void MiniDbCreate(MiniDb *sys, int tableId, int colNum, const char *keys)
{
    if (sys == NULL || tableId < 1 || tableId > MINI_DB_MAX_TABLE_ID ||
        sys->tables[tableId] != NULL) {
        return;
    }

    MiniDbTable *table = calloc(1, sizeof(MiniDbTable));
    if (table == NULL) {
        return;
    }

    table->colNum = (size_t)colNum;
    while (keys[table->keyCount] != '\0') {
        table->keyColumns[table->keyCount] =
            (unsigned char)(keys[table->keyCount] - 'a');
        ++table->keyCount;
    }
    sys->tables[tableId] = table;
}

static void MiniDbInsert(MiniDb *sys, int tableId, const int *values,
                         size_t valuesSize)
{
    if (sys == NULL || tableId < 1 || tableId > MINI_DB_MAX_TABLE_ID) {
        return;
    }

    MiniDbTable *table = sys->tables[tableId];
    if (table == NULL || values == NULL || valuesSize != table->colNum) {
        return;
    }

    size_t position = findInsertPosition(table, values);
    if (position < table->rowCount &&
        comparePrimaryKey(table, table->rows[position], values) == 0) {
        return;
    }

    if (table->rowCount == table->rowCapacity) {
        size_t newCapacity = table->rowCapacity == 0U
                                 ? MINI_DB_INITIAL_CAPACITY
                                 : table->rowCapacity * 2U;
        int **newRows = realloc(table->rows, newCapacity * sizeof(*newRows));
        if (newRows == NULL) {
            return;
        }
        table->rows = newRows;
        table->rowCapacity = newCapacity;
    }

    int *newRow = malloc(table->colNum * sizeof(*newRow));
    if (newRow == NULL) {
        return;
    }
    memcpy(newRow, values, table->colNum * sizeof(*newRow));

    memmove(&table->rows[position + 1U], &table->rows[position],
            (table->rowCount - position) * sizeof(*table->rows));
    table->rows[position] = newRow;
    ++table->rowCount;
}

// 注意：返回的数组必须在函数内调用malloc进行内存分配，由框架代码调用free进行内存释放。
// 同时，所返回的数组长度必须保存在 *returnSize 中。
static int **MiniDbSelect(MiniDb *sys, int tableId, char **conditions,
                          size_t conditionsSize, size_t *returnSize,
                          size_t **returnColSizes)
{
    *returnSize = 0;
    *returnColSizes = NULL;
    if (sys == NULL || tableId < 1 || tableId > MINI_DB_MAX_TABLE_ID ||
        conditionsSize > MINI_DB_MAX_COLUMNS) {
        return NULL;
    }

    MiniDbTable *table = sys->tables[tableId];
    if (table == NULL) {
        return NULL;
    }

    unsigned char conditionColumns[MINI_DB_MAX_COLUMNS];
    int conditionValues[MINI_DB_MAX_COLUMNS];
    for (size_t i = 0; i < conditionsSize; ++i) {
        conditionColumns[i] = (unsigned char)(conditions[i][0] - 'a');
        conditionValues[i] = (int)strtol(&conditions[i][2], NULL, 10);
    }

    size_t matchCount = 0;
    for (size_t i = 0; i < table->rowCount; ++i) {
        if (rowMatches(table->rows[i], conditionColumns, conditionValues,
                       conditionsSize)) {
            ++matchCount;
        }
    }
    if (matchCount == 0U) {
        return NULL;
    }

    int **result = malloc(matchCount * sizeof(*result));
    size_t *colSizes = malloc(matchCount * sizeof(*colSizes));
    if (result == NULL || colSizes == NULL) {
        free(result);
        free(colSizes);
        return NULL;
    }

    size_t resultIndex = 0;
    for (size_t i = 0; i < table->rowCount; ++i) {
        if (!rowMatches(table->rows[i], conditionColumns, conditionValues,
                        conditionsSize)) {
            continue;
        }

        result[resultIndex] = malloc(table->colNum * sizeof(*result[resultIndex]));
        if (result[resultIndex] == NULL) {
            for (size_t j = 0; j < resultIndex; ++j) {
                free(result[j]);
            }
            free(result);
            free(colSizes);
            return NULL;
        }
        memcpy(result[resultIndex], table->rows[i],
               table->colNum * sizeof(*result[resultIndex]));
        colSizes[resultIndex] = table->colNum;
        ++resultIndex;
    }

    *returnSize = matchCount;
    *returnColSizes = colSizes;
    return result;
}

static void MiniDbFree(MiniDb *sys)
{
    if (sys == NULL) {
        return;
    }

    for (size_t tableId = 1; tableId <= MINI_DB_MAX_TABLE_ID; ++tableId) {
        MiniDbTable *table = sys->tables[tableId];
        if (table == NULL) {
            continue;
        }
        for (size_t row = 0; row < table->rowCount; ++row) {
            free(table->rows[row]);
        }
        free(table->rows);
        free(table);
    }
    free(sys);
}
