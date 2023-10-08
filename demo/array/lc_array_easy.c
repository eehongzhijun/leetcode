/**
 * @file lc_array_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#include "utils.h"

/* https://leetcode.cn/problems/two-out-of-three/ */
/* 给你三个整数数组 nums1、nums2 和 nums3 ，请你构造并返回一个 元素各不相同的 数组，且由 至少 在 两个 数组中出现的所有值组成。数组中的元素可以按 任意 顺序排列。


示例 1：

输入：nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
输出：[3,2]
解释：至少在两个数组中出现的所有值为：
- 3 ，在全部三个数组中都出现过。
- 2 ，在数组 nums1 和 nums2 中出现过。
示例 2：

输入：nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
输出：[2,3,1]
解释：至少在两个数组中出现的所有值为：
- 2 ，在数组 nums2 和 nums3 中出现过。
- 3 ，在数组 nums1 和 nums2 中出现过。
- 1 ，在数组 nums1 和 nums3 中出现过。
示例 3：

输入：nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
输出：[]
解释：不存在至少在两个数组中出现的值。


提示：

1 <= nums1.length, nums2.length, nums3.length <= 100
1 <= nums1[i], nums2[j], nums3[k] <= 100 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_LEN 100

int *twoOutOfThree(int *nums1, int nums1Size, int *nums2, int nums2Size,
                   int *nums3, int nums3Size, int *returnSize)
{
    int mp[MAX_LEN + 1];
    memset(mp, 0, sizeof(int) * (MAX_LEN + 1));
    int i;
    for (i = 0; i < nums1Size; i++) {
        mp[nums1[i]] = 1;
    }
    for (i = 0; i < nums2Size; i++) {
        mp[nums2[i]] |= 2;
    }
    for (i = 0; i < nums3Size; i++) {
        mp[nums3[i]] |= 4;
    }
    int pos = 0;
    int *res = (int *)malloc(sizeof(int) * MAX_LEN);
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, sizeof(int) * MAX_LEN);
    for (i = 0; i <= MAX_LEN; i++) {
        if (mp[i] & (mp[i] - 1)) {
            res[pos] = i;
            pos++;
        }
    }
    *returnSize = pos;
    return res;
}

void twoOutOfThreeTest(void)
{

}

/* https://leetcode.cn/problems/find-pivot-index/ */
/* 给你一个整数数组 nums ，请计算数组的 中心下标 。

数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

如果中心下标位于数组最左端，那么左侧数之和视为 0 ，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。

如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1 。



示例 1：

输入：nums = [1, 7, 3, 6, 5, 6]
输出：3
解释：
中心下标是 3 。
左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11 ，
右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。
示例 2：

输入：nums = [1, 2, 3]
输出：-1
解释：
数组中不存在满足此条件的中心下标。
示例 3：

输入：nums = [2, 1, -1]
输出：0
解释：
中心下标是 0 。
左侧数之和 sum = 0 ，（下标 0 左侧不存在元素），
右侧数之和 sum = nums[1] + nums[2] = 1 + -1 = 0 。


提示：

1 <= nums.length <= 104
-1000 <= nums[i] <= 1000


注意：本题与主站 1991 题相同：https://leetcode-cn.com/problems/find-the-middle-index-in-array/ */
int pivotIndex(int *nums, int numsSize)
{
    int i;
    int sum = 0;
    int left = 0;

    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    for (i = 0; i < numsSize; i++) {
        if (left * 2 + nums[i] == sum) {
            return i;
        }
        left += nums[i];
    }
    return -1;
}

void pivotIndexTest(void)
{

}

/* https://leetcode.cn/problems/intersection-of-two-arrays-ii/ */
/* 给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。



示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
示例 2:

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]


提示：

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000


进阶：

如果给定的数组已经排好序呢？你将如何优化你的算法？
如果 nums1 的大小比 nums2 小，哪种方法更优？
如果 nums2 的元素存储在磁盘上，内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办？*/
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size,
               int *returnSize)
{
    bubble_sort(nums1, nums1Size);
    bubble_sort(nums2, nums2Size);

    int minLen = nums1Size > nums2Size ? nums2Size : nums1Size;
    int *ans = (int *)malloc(sizeof(int) * minLen);
    if (ans == NULL) {
        *returnSize = 0;
        return ans;
    }
    int i = 0, j = 0, cnt = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] == nums2[j]) {
            ans[cnt] = nums1[i];
            i++;
            j++;
            cnt++;
        } else if (nums1[i] > nums2[j]) {
            j++;
        } else {
            i++;
        }
    }
    *returnSize = cnt;
    return ans;
}

void intersectTest(void)
{

}

/* https://leetcode.cn/problems/max-consecutive-ones/ */
/* 给定一个二进制数组 nums ， 计算其中最大连续 1 的个数。



示例 1：

输入：nums = [1,1,0,1,1,1]
输出：3
解释：开头的两位和最后的三位都是连续 1 ，所以最大连续 1 的个数是 3.
示例 2:

输入：nums = [1,0,1,1,0,1]
输出：2


提示：

1 <= nums.length <= 105
nums[i] 不是 0 就是 1. */
int findMaxConsecutiveOnes(int *nums, int numsSize)
{
    if (nums == NULL) {
        return 0;
    }
    int max = 0, cnt = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            cnt++;
        } else {
            cnt = 0;
        }
        max = MAX(max, cnt);
    }
    return max;
}

void findMaxConsecutiveOnesTest(void)
{

}

/* https://leetcode.cn/problems/array-partition/ */
/* 给定长度为 2n 的整数数组 nums ，你的任务是将这些数分成 n 对, 例如 (a1, b1), (a2, b2), ..., (an, bn) ，使得从 1 到 n 的 min(ai, bi) 总和最大。

返回该 最大总和 。



示例 1：

输入：nums = [1,4,3,2]
输出：4
解释：所有可能的分法（忽略元素顺序）为：
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
所以最大总和为 4
示例 2：

输入：nums = [6,2,6,5,1,2]
输出：9
解释：最优的分法为 (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6, 6) = 1 + 2 + 6 = 9


提示：

1 <= n <= 104
nums.length == 2 * n
-104 <= nums[i] <= 104 */
int arrayPairSum(int *nums, int numsSize)
{
    if (nums == NULL) {
        return 0;
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    int ans = 0;
    for (int i = 0; i < numsSize; i += 2) {
        ans += nums[i];
    }
    return ans;
}

void arrayPairSumTest(void)
{

}

/* https://leetcode.cn/problems/move-zeroes/ */
/* 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。



示例 1:

输入: nums = [0,1,0,3,12]
输出: [1,3,12,0,0]
示例 2:

输入: nums = [0]
输出: [0]


提示:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1


进阶：你能尽量减少完成的操作次数吗？*/
void moveZeroes(int *nums, int numsSize)
{
    if (nums == NULL) {
        return;
    }
    int i, j = 0;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            j++;
        } else if (j != 0) {
            nums[i - j] = nums[i];
            nums[i] = 0;
        }
    }
}

void moveZeroesTest(void)
{

}

/* https://leetcode.cn/problems/contains-duplicate/ */
/* 给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。


示例 1：

输入：nums = [1,2,3,1]
输出：true
示例 2：

输入：nums = [1,2,3,4]
输出：false
示例 3：

输入：nums = [1,1,1,3,3,4,3,2,4,2]
输出：true


提示：

1 <= nums.length <= 105
-109 <= nums[i] <= 109 */
bool containsDuplicate(int *nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i] == nums[i + 1]) {
            return true;
        }
    }
    return false;
}

void containsDuplicateTest(void)
{

}

/* https://leetcode.cn/problems/majority-element/ */
/* 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1：

输入：nums = [3,2,3]
输出：3
示例 2：

输入：nums = [2,2,1,1,1,2,2]
输出：2


提示：
n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109


进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。*/
int majorityElement(int *nums, int numsSize)
{
    if (numsSize <= 2) {
        return nums[0];
    }
    bubble_sort(nums, numsSize);

    int count = 1;
    int i;
    int cond = numsSize / 2;

    for (i = 0; i < numsSize - 1; i++) {
        if (nums[i] == nums[i + 1]) {
            count++;
            if (count > cond) {
                return nums[i];
            }
        }
    }
    return 0;
}

void majorityElementTest(void)
{
    int nums[] = { 3, 2, 3 };
    // int nums[] = {2,2,1,1,1,2,2};
    int numsSize = sizeof(nums) / sizeof(int);

    int ans = majorityElement(nums, numsSize);

    printf("output: ans=%d\n", ans);
}

/* https://leetcode.cn/problems/single-number/ */
/* 给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。

示例 1 ：

输入：nums = [2,2,1]
输出：1
示例 2 ：

输入：nums = [4,1,2,1,2]
输出：4
示例 3 ：

输入：nums = [1]
输出：1


提示：

1 <= nums.length <= 3 * 104
-3 * 104 <= nums[i] <= 3 * 104
除了某个元素只出现一次以外，其余每个元素均出现两次 */
int singleNumber(int *nums, int numsSize)
{
    int i, result = 0;
    for (i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }
    return result;
}

void singleNumberTest(void)
{

}

/* https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/ */
/* 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。



示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。


提示：

1 <= prices.length <= 105
0 <= prices[i] <= 104 */
int maxProfit(int *prices, int pricesSize)
{
    int tmp = prices[0];
    int diff = 0;
    int i;

    for (i = 1; i < pricesSize; i++) {
        if (tmp >= prices[i]) {
            tmp = prices[i];
        } else if (diff < (prices[i] - tmp)) {
            diff = prices[i] - tmp;
        }
    }

    return diff;
}

void maxProfitTest(void)
{
    // int nums[] = {7,1,5,3,6,4};
    int nums[] = { 7, 6, 4, 3, 1 };
    int numsSize = sizeof(nums) / sizeof(int);

    int ans = maxProfit(nums, numsSize);

    printf("output: ans=%d\n", ans);
}

/* https://leetcode.cn/problems/pascals-triangle-ii/ */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getRow(int rowIndex, int *returnSize)
{
    if (returnSize == NULL) {
        return NULL;
    }
    *returnSize = rowIndex + 1;
    int *ret = (int *)malloc(sizeof(int) * (rowIndex + 1));
    int *pre_ret = (int *)malloc(sizeof(int) * (rowIndex + 1));
    if (ret == NULL || pre_ret == NULL) {
        return NULL;
    }
    memset(ret, 0, sizeof(int) * (rowIndex + 1));
    memset(pre_ret, 0, sizeof(int) * (rowIndex + 1));
    int i, j;
    for (i = 0; i < rowIndex + 1; i++) {
        ret[0] = ret[i] = 1;
        for (j = 1; j < i + 1; j++) {
            ret[j] = pre_ret[j - 1] + pre_ret[j];
        }
        int *tmp = pre_ret;
        pre_ret = ret;
        ret = tmp;
    }
    return pre_ret;
}

void getRowTest(void)
{

}

/* https://leetcode.cn/problems/pascals-triangle/ */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **generate(int numRows, int *returnSize, int **returnColumnSizes)
{
    if (returnSize == NULL || returnColumnSizes == NULL) {
        return NULL;
    }
    // printf("%s\n", __func__);
    *returnSize = 0;
    *returnColumnSizes = (int *)malloc(sizeof(int) * numRows);
    int **ret = (int **)malloc(sizeof(int *) * numRows);
    ret[*returnSize] = (int *)malloc(sizeof(int) * 1);
    ret[*returnSize][0] = 1;
    (*returnColumnSizes)[*returnSize] = 1;
    (*returnSize)++;
    int i, j;
    for (i = 1; i < numRows; i++) {
        ret[*returnSize] = (int *)malloc(sizeof(int) * (i + 1));
        (*returnColumnSizes)[*returnSize] = i + 1;
        for (j = 0; j < i + 1; j++) {
            if (j == 0 || j == i) {
                ret[*returnSize][j] = 1;
            } else {
                ret[*returnSize][j] =
                    ret[*returnSize - 1][j - 1] + ret[*returnSize - 1][j];
                //printf("*returnSize=%d, j=%d, retret[*returnSize][j]=%d\n", *returnSize, j, ret[*returnSize][j]);
            }
        }
        // if (i == 2) {
        //     printf("i=%d\n", i);
        //     return NULL;
        // }
        (*returnSize)++;
    }
    return ret;
}

void generateTest(void)
{

}

/* https://leetcode.cn/problems/merge-sorted-array/ */
/* 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。



示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
示例 2：

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
示例 3：

输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。


提示：

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 109


进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？ */
void arr_right_shift(int *nums, int len, int s, int e)
{
    for (int i = s; i > e; i--) {
        nums[i] = nums[i - 1];
    }
}

void merge_stored_array(int *nums1, int nums1Size, int m, int *nums2,
                        int nums2Size, int n)
{
    if (nums2 == NULL || n == 0) {
        return;
    }
    int i, j;
    int offset = m;
    for (i = 0, j = 0; i < nums1Size && j < nums2Size; i++) {
        if (i < offset && m != 0) {
            if (nums1[i] >= nums2[j]) {
                arr_right_shift(nums1, nums1Size, offset, i);
                offset++;
                nums1[i] = nums2[j];
                j++;
            }
        } else {
            nums1[i] = nums2[j];
            j++;
        }
    }
}

void mergeTest(void)
{

}

/* https://leetcode.cn/problems/plus-one/ */
/* 给定一个由 整数 组成的 非空 数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。



示例 1：

输入：digits = [1,2,3]
输出：[1,2,4]
解释：输入数组表示数字 123。
示例 2：

输入：digits = [4,3,2,1]
输出：[4,3,2,2]
解释：输入数组表示数字 4321。
示例 3：

输入：digits = [0]
输出：[1]


提示：

1 <= digits.length <= 100
0 <= digits[i] <= 9 */
int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    for (int i = digitsSize - 1; i >= 0; i--) {
        if (digits[i] != 9) {
            digits[i]++;
            *returnSize = digitsSize;
            return digits;
        } else {
            digits[i] = 0;
        }
    }
    *returnSize = digitsSize + 1;
    int *tmp = (int *)malloc(sizeof(int) * (digitsSize + 1));
    if (tmp == NULL) {
        *returnSize = 0;
        return tmp;
    }
    for (int i = 1; i < digitsSize + 1; i++) {
        tmp[i] = digits[i - 1];
    }
    tmp[0] = 1;
    return tmp;
}

void plusOneTest(void)
{

}

/* https://leetcode.cn/problems/search-insert-position/ */
/* 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。



示例 1:

输入: nums = [1,3,5,6], target = 5
输出: 2
示例 2:

输入: nums = [1,3,5,6], target = 2
输出: 1
示例 3:

输入: nums = [1,3,5,6], target = 7
输出: 4


提示:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 为 无重复元素 的 升序 排列数组
-104 <= target <= 104 */
int searchInsert(int *nums, int numsSize, int target)
{
    int i;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] >= target) {
            return i;
        }
    }
    return i;
}

void searchInsertTest(void)
{

}

/* https://leetcode.cn/problems/remove-element/ */
/* 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。



说明:

为什么返回数值是整数，但输出的答案是数组呢?

请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下:

// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);

// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}


示例 1：

输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2]
解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。
示例 2：

输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3]
解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。


提示：

0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100 */
int removeElement(int *nums, int numsSize, int val)
{
    if (nums == NULL) {
        return 0;
    }
    int fast, slow;
    for (slow = 0, fast = 0; fast < numsSize; fast++) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}

void removeElementTest(void)
{

}

/* https://leetcode.cn/problems/remove-duplicates-from-sorted-array/ */
/* 给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。

考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：

更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
返回 k 。
判题标准:

系统会用下面的代码来测试你的题解:

int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案

int k = removeDuplicates(nums); // 调用

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么您的题解将被 通过。

示例 1：

输入：nums = [1,1,2]
输出：2, nums = [1,2,_]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。
示例 2：

输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。


提示：

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
nums 已按 非严格递增 排列 */
int removeDuplicates(int *nums, int numsSize)
{
    int s = 0, f = 1;
    while (s < f && f < numsSize) {
        if (nums[s] != nums[f]) {
            s++;
        }
        f++;
        if (f - s > 1) {
            nums[s] = nums[f - 1];
        }
    }
    return s + 1;
}

void removeDuplicatesTest(void)
{

}

/* https://leetcode.cn/problems/two-sum/ */
/* 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]


提示：

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案


进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = 0; j < numsSize - i - 1; ++j) {
            if (nums[i] + nums[j + i + 1] == target) {
                int *ret = (int *)malloc(sizeof(int) * 2);
                ret[0] = i;
                ret[1] = j + i + 1;
                *returnSize = 2;
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

void twoSumTest(void)
{
    int nums[4] = { 2, 7, 11, 15 };
    int target = 9;
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize;

    int *ans = twoSum(nums, numsSize, target, &returnSize);

    printf("output: [%d,%d]\n", ans[0], ans[1]);
}