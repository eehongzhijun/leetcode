/**
 * @file lc_hash_table_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#include "utils.h"
#include "uthash.h"

/* 查找元素 元素去重 存储元素 */

/* https://leetcode.cn/problems/x-of-a-kind-in-a-deck-of-cards/ */
/* 给定一副牌，每张牌上都写着一个整数。

此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

每组都有 X 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 X >= 2 时返回 true。

示例 1：

输入：deck = [1,2,3,4,4,3,2,1]
输出：true
解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
示例 2：

输入：deck = [1,1,1,2,2,2,3,3]
输出：false
解释：没有满足要求的分组。

提示：

1 <= deck.length <= 104
0 <= deck[i] < 104 */
/*
    [0,0,0,1,1,1,2,2,2] 0<3> 1<3> 2<3> -- 3 3 3
    [1,1,2,2,2,2] 2 4 -- 3 3
    [1,1,1,1,2,2,2,2,2,2] 4 6 -- 5 5
    [0,0,0,0,0,0,0,1,2,3,3,3,4,5,6] 7 1 1 3 1 1 1
    [1,2,2,3,3,3] 1 2 3
*/
#undef HASH_TABLE_hasGroupsSizeX
#if defined(HASH_TABLE_hasGroupsSizeX)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool hasGroupsSizeX(int *deck, int deckSize)
{
    ht_t *ht = NULL;
    ht_t *it, *tmp;
    int i;

    if (deckSize < 2) {
        return 0;
    }
    for (i = 0; i < deckSize; i++) {
        HASH_FIND_INT(ht, &deck[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = deck[i];
            tmp->val = 1;
            HASH_ADD_INT(ht, key, tmp);
        } else {
            tmp->val++;
        }
    }

    int max, flag;
    for (i = deckSize; i > 0; i--) {
        flag = 1;
        for (tmp = ht; tmp != NULL; tmp = tmp->hh.next) {
            if ((tmp->val) % i != 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            max = i;
            break;
        }
    }

    if (max >= 2)
        return true;
    else
        return false;
}

int hasGroupsSizeXTest(void)
{
    int deck[] = {1, 1, 2, 2, 2, 2};
    int deckSize = ARRAY_SIZE(deck);

    printf("intput:\n");
    PRINT_ARRAY(deck, deckSize, "%d ");
    printf("output:%s\n",
           (hasGroupsSizeX(deck, deckSize) == 1) ? "true" : "false");
    return 0;
}
#endif

/* https://leetcode.cn/problems/set-mismatch/ */
/* 集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，
导致集合 丢失了一个数字 并且 有一个数字重复 。

给定一个数组 nums 代表了集合 S 发生错误后的结果。

请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。

示例 1：

输入：nums = [1,2,2,4]
输出：[2,3]
示例 2：

输入：nums = [1,1]
输出：[1,2]


提示：

2 <= nums.length <= 104
1 <= nums[i] <= 104 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#undef HASH_TABLE_findErrorNums
#if defined(HASH_TABLE_findErrorNums)

typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

int *findErrorNums(int *nums, int numsSize, int *returnSize)
{
    int i;
    int *ans = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;
    ht_t *ht = NULL;
    ht_t *tmp;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            HASH_ADD_INT(ht, key, tmp);
        } else {
            ans[0] = nums[i];
        }
    }

    ht_t *tmp1;
    for (i = 1; i <= numsSize; i++) {
        HASH_FIND_INT(ht, &i, tmp1);
        if (tmp1 == NULL) {
            ans[1] = i;
            break;
        }
    }

    HASH_ITER(hh, ht, tmp, tmp1)
    {
        // printf("del tmp->key=%d\n", tmp->key);
        HASH_DEL(ht, tmp);
        free(tmp);
    }
    return ans;
}

int findErrorNumsTest(void)
{
    int nums[] = {1, 2, 2, 4};
    int numsSize = ARRAY_SIZE(nums);
    int returnSize;

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int *ret = findErrorNums(nums, numsSize, &returnSize);
    if (ret == NULL) {
        return -1;
    }
    printf("output:\n");
    PRINT_ARRAY(ret, returnSize, "%d ");
    return 0;
}
#endif

/* https://leetcode.cn/problems/longest-harmonious-subsequence/ */
/* 和谐数组是指一个数组里元素的最大值和最小值之间的差别 正好是 1 。

现在，给你一个整数数组 nums ，请你在所有可能的子序列中找到最长的和谐子序列的长度。

数组的子序列是一个由数组派生出来的序列，它可以通过删除一些元素或不删除元素、且不改变其余元素的顺序而得到。

示例 1：

输入：nums = [1,3,2,2,5,2,3,7]
输出：5
解释：最长的和谐子序列是 [3,2,2,2,3]
示例 2：

输入：nums = [1,2,3,4]
输出：2
示例 3：

输入：nums = [1,1,1,1]
输出：0


提示：

1 <= nums.length <= 2 * 104
-109 <= nums[i] <= 109 */
#undef HASH_TABLE_findLHS
#if defined(HASH_TABLE_findLHS)

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

int findLHS(int *nums, int numsSize)
{
    ht_t *ht = NULL;
    ht_t *tmp;
    int ans = 0;
    int i;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            tmp->val = 1;
            HASH_ADD_INT(ht, key, tmp);
        } else {
            tmp->val++;
        }
    }

    ht_t *it, *tmp1;
    HASH_ITER(hh, ht, it, tmp)
    {
        if (it) {
            int next_key = it->key + 1;
            HASH_FIND_INT(ht, &next_key, tmp1);
            if (tmp1) {
                ans = (it->val + tmp1->val > ans) ? (it->val + tmp1->val) : ans;
            }
        }
    }

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }

    return ans;
}

void findLHSTest(void)
{
    int nums[] = {1, 3, 2, 2, 5, 2, 3, 7};
    int numsSize = ARRAY_SIZE(nums);

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int ret = findLHS(nums, numsSize);
    printf("output:%d\n", ret);
}
#endif

/* Alice 有 n 枚糖，其中第 i 枚糖的类型为 candyType[i] 。Alice 注意到她的体重正在增长，所以前去拜访了一位医生。

医生建议 Alice 要少摄入糖分，只吃掉她所有糖的 n / 2 即可（n 是一个偶数）。Alice 非常喜欢这些糖，她想要在遵循医生建议的情况下，
尽可能吃到最多不同种类的糖。

给你一个长度为 n 的整数数组 candyType ，返回： Alice 在仅吃掉 n / 2 枚糖的情况下，可以吃到糖的 最多 种类数。

示例 1：

输入：candyType = [1,1,2,2,3,3]
输出：3
解释：Alice 只能吃 6 / 2 = 3 枚糖，由于只有 3 种糖，她可以每种吃一枚。
示例 2：

输入：candyType = [1,1,2,3]
输出：2
解释：Alice 只能吃 4 / 2 = 2 枚糖，不管她选择吃的种类是 [1,2]、[1,3] 还是 [2,3]，她只能吃到两种不同类的糖。
示例 3：

输入：candyType = [6,6,6,6]
输出：1
解释：Alice 只能吃 4 / 2 = 2 枚糖，尽管她能吃 2 枚，但只能吃到 1 种糖。


提示：

n == candyType.length
2 <= n <= 104
n 是一个偶数
-105 <= candyType[i] <= 105 */

/* https://leetcode.cn/problems/distribute-candies/ */
#undef HASH_TABLE_distributeCandies
#if defined(HASH_TABLE_distributeCandies)
typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

ht_t *ht = NULL;

void insert(int key)
{
    ht_t *it;
    HASH_FIND_INT(ht, &key, it);
    if (it == NULL) {
        it = (ht_t *)malloc(sizeof *it);
        it->key = key;
        HASH_ADD_INT(ht, key, it);
    }
}

void deelte_all(void)
{
    ht_t *it;
    ht_t *tmp;

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }
}

int distributeCandies(int *candyType, int candyTypeSize)
{
    ht = NULL;
    int ans;
    for (int i = 0; i < candyTypeSize; i++) {
        insert(candyType[i]);
    }
    if (candyTypeSize / 2 >= HASH_COUNT(ht)) {
        ans = HASH_COUNT(ht);
    } else {
        ans = candyTypeSize / 2;
    }
    return ans;
}

void distributeCandiesTest(void)
{
    int candyType[] = {6, 6, 6, 6};
    int candyTypeSize = ARRAY_SIZE(candyType);

    printf("input:\n");
    PRINT_ARRAY(candyType, candyTypeSize, "%d ");
    int ret = distributeCandies(candyType, candyTypeSize);
    printf("output:%d\n", ret);
    deelte_all();
}
#endif

/* https://leetcode.cn/problems/longest-palindrome/ */
/* 给定一个包含大写字母和小写字母的字符串 s ，返回 通过这些字母构造成的 最长的回文串 。

在构造过程中，请注意 区分大小写 。比如 "Aa" 不能当做一个回文字符串。

示例 1:

输入:s = "abccccdd"
输出:7
解释:
我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
示例 2:

输入:s = "a"
输出:1
示例 3：

输入:s = "aaaaaccc"
输出:7


提示:

1 <= s.length <= 2000
s 只由小写 和/或 大写英文字母组成 */
#if defined(HASH_TABLE_xlongestPalindrome)
int xlongestPalindrome(char *s)
{
    int t1[26] = {0}; // lower
    int t2[26] = {0}; // upper
    int ans = 0;
    int i;

    for (i = 0; s[i] != 0; i++) {
        if (islower(s[i])) {
            t1[s[i] - 'a']++;
        } else {
            t2[s[i] - 'A']++;
        }
    }

    int flag = 0;
    for (i = 0; i < 26; i++) {
        if (t1[i] % 2 == 0) {
            ans += t1[i];
        } else {
            flag = 1;
            ans += (t1[i] - 1);
        }

        if (t2[i] % 2 == 0) {
            ans += t2[i];
        } else {
            flag = 1;
            ans += (t2[i] - 1);
        }
    }
    return ans + flag;
}

void xlongestPalindromeTest(void)
{
    char s[] = "abccccdd";

    printf("input:%s\n", s);
    int ret = xlongestPalindrome(s);
    printf("output:%d\n", ret);
}
#endif
/* https://leetcode.cn/problems/happy-number/ */
/* 编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」 定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

示例 1：

输入：n = 19
输出：true
解释：
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
示例 2：

输入：n = 2
输出：false
提示：

1 <= n <= 231 - 1 */
#if defined HASH_TABLE_isHappy
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

ht_t *ht = NULL;

ht_t *find(int key)
{
    ht_t *tmp;
    HASH_FIND_INT(ht, &key, tmp);
    return tmp;
}

ht_t *insert(int key)
{
    ht_t *it;
    HASH_FIND_INT(ht, &key, it);
    if (it == NULL) {
        it = (ht_t *)malloc(sizeof *it);
        it->key = key;
        it->val = 0;
        HASH_ADD_INT(ht, key, it);
    } else {
        it->val = 1;
    }
    return it;
}

void deelte_all(void)
{
    ht_t *it;
    ht_t *tmp;

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }
}

void print_users(void)
{
    ht_t *it;

    for (it = ht; it != NULL; it = (ht_t *)(it->hh.next)) {
        printf("key:%d\n", it->key);
    }
}

bool isHappy(int n)
{
    int sum = 0;
    int m = 0;
    ht = NULL;
    insert(n);
    while (1) {
        while (n != 0) {
            m = n % 10;
            n /= 10;
            sum += pow(m, 2);
        }
        printf("sum=%d\n", sum);
        if (sum == 1) {
            return true;
        }
        n = sum;
        sum = 0;
        ht_t *it = insert(n);
        printf("it->val=%d\n", it->val);
        if (it->val) {
            return false;
        }
    }
    return 0;
}

void isHappyTest(void)
{
    int n = 13;
    printf("input:%d\n", n);
    printf("output:%s\n", (isHappy(n) == 1) ? "true" : "false");
    deelte_all();
}
#endif

/* https://leetcode.cn/problems/design-hashset/solutions/652778/she-ji-ha-xi-ji-he-by-leetcode-solution-xp4t/ */
struct List {
    int val;
    struct List *next;
};

void listPush(struct List *head, int x)
{
    struct List *tmp = malloc(sizeof(struct List));
    tmp->val = x;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List *head, int x)
{
    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            struct List *tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

bool listContains(struct List *head, int x)
{
    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            return true;
        }
    }
    return false;
}

void listFree(struct List *head)
{
    while (head->next) {
        struct List *tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;

int hash(int key)
{
    return key % base;
}

typedef struct {
    struct List *data;
} MyHashSet;

MyHashSet *myHashSetCreate()
{
    MyHashSet *ret = malloc(sizeof(MyHashSet));
    ret->data = malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        ret->data[i].val = 0;
        ret->data[i].next = NULL;
    }
    return ret;
}

void myHashSetAdd(MyHashSet *obj, int key)
{
    int h = hash(key);
    if (!listContains(&(obj->data[h]), key)) {
        listPush(&(obj->data[h]), key);
    }
}

void myHashSetRemove(MyHashSet *obj, int key)
{
    int h = hash(key);
    listDelete(&(obj->data[h]), key);
}

bool myHashSetContains(MyHashSet *obj, int key)
{
    int h = hash(key);
    return listContains(&(obj->data[h]), key);
}

void myHashSetFree(MyHashSet *obj)
{
    for (int i = 0; i < base; i++) {
        listFree(&(obj->data[i]));
    }
    free(obj->data);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);

 * myHashSetRemove(obj, key);

 * bool param_3 = myHashSetContains(obj, key);

 * myHashSetFree(obj);
*/
int myHashTest(void)
{
    return 0;
}

int lc_hash_table_easy_test(void)
{
    int ret = -1;
    // isHappyTest();
    // xlongestPalindromeTest();
    // distributeCandiesTest();
    // findLHSTest();
    // ret = findErrorNumsTest();
    // ret = myHashTest();
    // ret = hasGroupsSizeXTest();
    return ret;
}
