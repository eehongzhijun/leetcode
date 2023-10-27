/**
 * @file lc_dp_medium.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stdio.h"
#include "stdbool.h"

/* https://leetcode.cn/problems/maximum-subarray/ */
int maxSubArray(int *nums, int numsSize)
{
    int dp[numsSize];
    int i;
    int ans;

    dp[0] = nums[0];
    ans = dp[0];
    for (i = 1; i < numsSize; i++) {
        if (dp[i - 1] > 0) {
            dp[i] = dp[i - 1] + nums[i];
        } else {
            dp[i] = nums[i];
        }
        ans = dp[i] > ans ? dp[i] : ans;
    }
    return ans;
}

/* https://leetcode.cn/problems/unique-paths-ii/ */
int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize,
                             int *obstacleGridColSize)
{
    if (obstacleGridSize <= 0 || *obstacleGridColSize <= 0) {
        return 0;
    }
    int dp[obstacleGridSize][*obstacleGridColSize];
    int i, j;
    bool flag = false;

    for (i = 0; i < obstacleGridSize; i++) {
        if (obstacleGrid[i][0] || flag) {
            dp[i][0] = 0;
            flag = true;
        } else {
            dp[i][0] = 1;
        }
    }
    flag = false;
    for (i = 0; i < *obstacleGridColSize; i++) {
        if (obstacleGrid[0][i] || flag) {
            dp[0][i] = 0;
            flag = true;
        } else {
            dp[0][i] = 1;
        }
    }

    for (i = 1; i < obstacleGridSize; i++) {
        for (j = 1; j < *obstacleGridColSize; j++) {
            if (obstacleGrid[i][j]) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    return dp[obstacleGridSize - 1][*obstacleGridColSize - 1];
}

/* https://leetcode.cn/problems/jump-game/ */
bool canJump(int *nums, int numsSize)
{
    int i;
    int k = 0;

    for (i = 0; i < numsSize; i++) {
        if (i > k) {
            return false;
        }
        k = (nums[i] + i) > k ? (nums[i] + i) : k;
    }
    return true;
}

/* https://leetcode.cn/problems/unique-paths/ */
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

示例 1：
——————————————————————————————
|oo |   |   |   |   |   |   |
——————————————————————————————
|   |   |   |   |   |   |x1 |
——————————————————————————————
|   |   |   |   |   |x2 | * |
——————————————————————————————

输入：m = 3, n = 7
输出：28
示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
示例 3：

输入：m = 7, n = 3
输出：28
示例 4：

输入：m = 3, n = 3
输出：6


提示：

1 <= m, n <= 100
题目数据保证答案小于等于 2 * 109 */
int uniquePaths(int m, int n)
{
    if (m <= 0 && n <= 0) {
        return 0;
    }
    int dp[m][n];
    int i, j;

    for (i = 0; i < m; i++) {
        dp[i][0] = 1;
    }

    for (i = 0; i < n; i++) {
        dp[0][i] = 1;
    }

    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
        }
    }
    return dp[m - 1][n - 1];
}

int uniquePathsTest(void)
{
    int m, n;
    printf("please input m and n:\n");
    scanf("%d%d", &m, &n);
    int ret = uniquePaths(m, n);
    printf("output:%d\n", ret);
    return 0;
}

int lc_dp_medium_test(void)
{
    int ret = -1;
    // ret = uniquePathsTest();
    return ret;
}
