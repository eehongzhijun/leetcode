#include "stdio.h"
#include "string.h"
#include "stdbool.h"

/* https://leetcode.cn/problems/valid-parentheses/ */
/* 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。


示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "()[]{}"
输出：true
示例 3：

输入：s = "(]"
输出：false


提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成 */
char pairs(char a) {
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}

bool isValid(char *s)
{
    size_t len = strlen(s);

    if (len % 2 == 1) {
        return false;
    }

    int stk[len + 1], top = 0;
    for (int i = 0; i < len; i++) {
        char ch = pairs(s[i]);
        if (ch) {
            if (top == 0 || stk[top - 1] != ch) {
                return false;
            }
            top--;
        } else {
            stk[top++] = s[i];
        }
    }
    return top == 0;
}

void isValidTest(void)
{
    /*  true: ((())) ()()() ()((())) ((()))() (())))()
        false: ([)]  */
    char s[] = "((()))()";

    printf("input:%s\n", s);

    bool ret = isValid(s);
    if (ret) {
        printf("output:true\n");
    } else {
        printf("output:false\n");
    }
}

/* https://leetcode.cn/problems/roman-to-integer/ */
/* 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，
所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。



示例 1:

输入: s = "III"
输出: 3
示例 2:

输入: s = "IV"
输出: 4
示例 3:

输入: s = "IX"
输出: 9
示例 4:

输入: s = "LVIII"
输出: 58
解释: L = 50, V= 5, III = 3.
示例 5:

输入: s = "MCMXCIV"
输出: 1994
解释: M = 1000, CM = 900, XC = 90, IV = 4.


提示：

1 <= s.length <= 15
s 仅含字符 ('I', 'V', 'X', 'L', 'C', 'D', 'M')
题目数据保证 s 是一个有效的罗马数字，且表示整数在范围 [1, 3999] 内
题目所给测试用例皆符合罗马数字书写规则，不会出现跨位等情况。
IL 和 IM 这样的例子并不符合题目要求，49 应该写作 XLIX，999 应该写作 CMXCIX 。
关于罗马数字的详尽书写规则，可以参考 罗马数字 - Mathematics 。*/
int romanToInt(char *s)
{
    int n = 0;
    for (int i = 0; s[i] != 0; i++) {
        switch (s[i]) {
        case 'I':
            if (s[i + 1] == 'V') {
                n += 4;
                i++;
            } else if (s[i + 1] == 'X') {
                n += 9;
                i++;
            } else {
                n += 1;
            }
            break;
        case 'V':
            n += 5;
            break;
        case 'X':
            if (s[i + 1] == 'L') {
                n += 40;
                i++;
            } else if (s[i + 1] == 'C') {
                n += 90;
                i++;
            } else {
                n += 10;
            }
            break;
        case 'L':
            n += 50;
            break;
        case 'C':
            if (s[i + 1] == 'M') {
                n += 900;
                i++;
            } else if (s[i + 1] == 'D') {
                n += 400;
                i++;
            } else {
                n += 100;
            }
            break;
        case 'D':
            n += 500;
            break;
        case 'M':
            n += 1000;
            break;
        default:
            break;
        }
    }

    return n;
}

void romanToIntTest(void)
{
    char s[] = "CMLII";

    printf("input=%s\n", s);
    int ret = romanToInt(s);
    printf("output=%d\n", ret);
}
