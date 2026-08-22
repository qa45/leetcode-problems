# 磁盘空间占用区间统计

某台现网设备每天都会产生大量日志，这些日志会占用磁盘空间，并按照一定规则自动清除。因此，设备每天的磁盘空间占用量都会发生变化。

运维系统从设备上电开始，每天采集一次磁盘空间占用情况，并将结果记录在整数数组 `records` 中，单位为 MB。

给你一个整数数组 `records`、一个区间长度范围 `lengthRange` 和一个整数 `threshold`，请统计同时满足以下条件的连续非空区间数量：

- 区间长度在 `[lengthRange.minLen, lengthRange.maxLen]` 范围内，包括两个边界；
- 区间内所有元素的平均值大于等于 `threshold`。

返回满足条件的连续区间数量。

## 示例 1

```text
输入：records = [2, 0, 2, 0, 2], lengthRange = [2, 4], threshold = 1
输出：8
```

**解释：**

需要检查长度为 `2`、`3` 和 `4` 的所有连续区间。

满足条件的区间如下：

```text
长度 2：[2, 0]、[0, 2]、[2, 0]、[0, 2]
长度 3：[2, 0, 2]、[2, 0, 2]
长度 4：[2, 0, 2, 0]、[0, 2, 0, 2]
```

例如，区间 `[2, 0, 2]` 的平均值为 `4 / 3`，大于等于 `1`，因此满足条件；区间 `[0, 2, 0]` 的平均值为 `2 / 3`，小于 `1`，因此不满足条件。

满足条件的连续区间共有 `8` 个。

## 提示

- `1 <= recordsSize <= 10000`
- `0 <= records[i] <= 10000`
- `1 <= lengthRange.minLen <= lengthRange.maxLen <= 1000`
- `lengthRange.maxLen <= recordsSize`
- `0 <= threshold <= 10000`

## C 语言函数签名

```c
typedef struct {
    int minLen;
    int maxLen;
} LengthRange;

static int CountIntervals(const int *records,
                          size_t recordsSize,
                          LengthRange lengthRange,
                          int threshold)
{
    return 0;
}
```

