/**
 * @file main_test.c
 * @author eehongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "math.h"

#include "gnu/libc-version.h"

#include "utils.h"

extern void stack_test(void);
extern void queue_test(void);

int g_m, g_n; // 表示定义该文件全局变量
extern int g_a, g_b; // 表示外部已经定义好的全局变量，这里是该文件对其声明，不是定义。

void extern_test(void)
{

    printf("EXTERN TEST\n");
    /* int g_x, g_y; 定义局部变量*/
    extern int g_x, g_y; // 声明外部全局变量，下面才可以使用
    printf("g_x=%d, g_y=%d\n", g_x, g_y);
}

// 定义全局变量g_x, g_y，但是上面main_test函数想使用全局变量必须使用extern进行声明才能引用
int g_x = 0;
int g_y = 1;
void test(void)
{
    printf("test, g_x=%d, g_y=%d\n", g_x, g_y);
}


/* memory layout test */
static int u_s_g_var_a; /* 未初始化静态全局变量a 存放在bss段 */
static int i_s_g_var_b = 10; /* 已初始化静态全局变量b 存在在data段 */

int u_g_var_c; /* 未初始化全局变量c */
int i_g_var_d = 10; /* 已初始化全局变量d */

const int u_g_c_var_e; /* const 修饰未初始化全局常量 */
const int i_g_c_var_f = 10; /* const 修饰初始化全局常量 */

void func_test(void)
{
    printf("func\n");
}

int memory_layout_test(void)
{
    int l_var_a;
    int l_var_b = 10;
    int *l_var_c = NULL;
    int *l_var_d = NULL;
    static int u_s_l_var_e;
    static int i_s_l_var_f = 10;
    const int u_l_c_var_g;
    const int i_l_c_var_h = 10;
    char *l_var_s = "Hello World";
    char l_var_arr[] = "Hello World";
    const int *l_p_a =  &l_var_a;   /* 常量指针 */
    int * const l_p_b = &l_var_b;       /* 指针常量 */
    const int * const l_p_c =  &i_l_c_var_h;    /* 指向常量的常指针 */
    int *l_var_aa = (int *)alloca(sizeof(int) * 4); /* 从栈分配内存 */

    printf("-----------------------------------------------------\n");
    printf("栈区\n");
    printf("%s\t\t%p\n", STR(l_var_aa), l_var_aa);
    printf("%s\t\t\t%p\n", STR(l_var_a), &l_var_a);
    printf("%s\t\t\t%p\n", STR(l_var_b), &l_var_b);
    printf("%s\t\t%p\n", STR(&l_var_c), &l_var_c);
    printf("%s\t\t%p\n", STR(&l_var_d), &l_var_d);
    printf("%s\t\t%p\n", STR(u_l_c_var_g), &u_l_c_var_g);
    printf("%s\t\t%p\n", STR(i_l_c_var_h), &i_l_c_var_h);
    printf("%s\t\t%p\n", STR(&l_var_s), &l_var_s);
    printf("%s\t\t\t%p\n", STR(&l_p_a), &l_p_a);
    printf("%s\t\t\t%p\n", STR(&l_p_b), &l_p_b);
    printf("%s\t\t\t%p\n", STR(&l_p_c), &l_p_c);
    printf("%s\t\t%p\n", STR(l_var_arr), l_var_arr);


    l_var_c = (int *)malloc(sizeof(int) * 4);
    l_var_d = (int *)malloc(sizeof(int) * 4);
    printf("-----------------------------------------------------\n");
    printf("堆区\n");
    printf("%s\t\t\t%p\n", STR(l_var_c), l_var_c);
    printf("%s\t\t\t%p\n", STR(l_var_d), l_var_d);

    printf("-----------------------------------------------------\n");
    printf("bss区\n");
    printf("%s\t\t%p\n", STR(u_s_g_var_a), &u_s_g_var_a);
    printf("%s\t\t%p\n", STR(u_g_var_c), &u_g_var_c);
    printf("%s\t\t%p\n", STR(u_s_l_var_e), &u_s_l_var_e);
    printf("%s\t\t%p\n", STR(u_g_c_var_e), &u_g_c_var_e);

    printf("-----------------------------------------------------\n");
    printf("data区\n");
    printf("%s\t\t%p\n", STR(i_s_g_var_b), &i_s_g_var_b);
    printf("%s\t\t%p\n", STR(i_g_var_d), &i_g_var_d);
    printf("%s\t\t%p\n", STR(i_s_l_var_f), &i_s_l_var_f);

    printf("-----------------------------------------------------\n");
    printf("text区\n");
    printf("常量\n");
    printf("%s\t\t%p\n", STR(i_g_c_var_f), &i_g_c_var_f);
    printf("%s\t\t\t%p\n", STR(l_var_s), l_var_s);

    printf("代码\n");
    printf("%s\t%p\n", STR(memory_layout_test), memory_layout_test);
    printf("%s\t\t%p\n", STR(func_test), func_test);

    free(l_var_c);
    l_var_c = NULL;
    free(l_var_d);
    l_var_d = NULL;

}

/* string.h */
void memset_test(void)
{
    int arr[10];
    int len = 10;

    /* wrong */
    memset(arr, 0, len);
    PRINT_ARRAY(arr, len, "%d ");

    /* wrong */
    /*  预期初始化数组每个元素为1，
        实际确是这样0b 00000001 00000001 00000001 00000001
        如果想初始化数组元素要用循环语句来初始化 */
    memset(arr, 1, len * sizeof(int));
    PRINT_ARRAY(arr, len, "%d ");
    PRINT_ARRAY(arr, len, "%08x ");

    /* right */
    memset(arr, 0, len * sizeof(int));
    PRINT_ARRAY(arr, len, "%d ");

    for (int i = 0; i < len; i++) {
        arr[i] = 1;
    }
    PRINT_ARRAY(arr, len, "%d ");
}

void hex2dec_test(void)
{
    char hex[128] = {0};

    printf("please input hex:\n");
    scanf("%s", hex);

    // PRINT_ARRAY(hex, 128, "%d ");
    int ret = hex2dec(hex);

    printf("output:%d\n", ret);
}

void dec2hex_test(void)
{
    int dec;

    printf("please input dec:\n");
    scanf("%d", &dec);

    char *ret = dec2hex(dec);

    printf("output:%s\n", ret);
    free(ret);
}

void main_test(void)
{
    printf("TEST ENTRY\n");
    printf("GNU libc version: %s %s\n", gnu_get_libc_version(), ENVIRONMENT);
    // memory_layout_test();
    memset_test();

    // stack_test();
    // queue_test();

    // hex2dec_test();
    // dec2hex_test();

}
