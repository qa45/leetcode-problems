# 太空项目时长单位转换

某创新公司正在进行一项星球太空项目，其中涉及不同时长单位之间的转换和表示。

给你一个表示时长的字符串 `inputStr`，请将该时长尽可能转换成更大的单位，并返回转换后的字符串。

转换结果需要满足以下规则：

- 每个单位对应的数值必须是整数；
- 优先使用尽可能大的单位；
- 数值为 `0` 的单位不输出；
- 无法继续向上转换的剩余部分，使用较小单位继续表示；
- 各单位按照从大到小的顺序输出，数值、单位及不同单位之间均使用一个空格分隔。

该星球的时长单位换算关系如下：

```text
1 year   = 22 month
1 month  = 31 day
1 day    = 24 hour
1 hour   = 60 minute
1 minute = 60 second
```

## 示例 1

```text
输入：inputStr = "489607 minute"
输出："10 month 30 day 7 minute"
```

**解释：**

```text
489607 minute = 10 month 30 day 0 hour 7 minute
```

由于 `hour` 对应的数值为 `0`，因此结果中不输出该单位。

## 示例 2

```text
输入：inputStr = "530323200 second"
输出："9 year"
```

## 示例 3

```text
输入：inputStr = "21 month"
输出："21 month"
```

**解释：** `1 year = 22 month`，而 `21 month` 不足 `1 year`，因此无法继续转换。

## 提示

- `inputStr` 的格式为 `"数值 单位"`；
- 数值是大于 `0` 的十进制整数；
- 单位是 `year`、`month`、`day`、`hour`、`minute` 或 `second` 之一；
- 转换前后的总时长均小于 `10 year`；
- 返回的字符串必须在函数内通过 `malloc` 分配，由调用者负责调用 `free` 释放。

## C 语言函数签名

```c
static char *UnitTransform(const char *inputStr)
{
    return NULL;
}
```

