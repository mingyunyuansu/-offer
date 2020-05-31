/*
题目描述

给定一个数字N，打印从1到最大的N位数。

输入

每个输入文件仅包含一组测试样例。

对于每个测试案例，输入一个数字N(1<=N<=5)。 输出 对应每个测试案例，依次打印从1到最大的N位数。

样例输入

1

样例输出

1 2 3 4 5 6 7 8 9
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void simple(int N) {
    int i = 1;
    int max = 1;
    while (N) {
        max *= 10;
        --N;
    }
    while (i < max) {
        printf ("%d ", i);
        ++i;
    }
}

void with_string_increase(int N) {
    //解答说应利用字符串来解决变量溢出的问题，但是这里N<=5是明显不会溢出的
    //不管怎么样既然是练习就还是用字符串做一下吧
    //记得当初大一刚来就写过字符串加减，当时还觉得挺难的
    //所以这也是一场来自过去的试炼！
    char *str = (char *)malloc(sizeof(char) * (N+1));
    memset(str, '0', sizeof(char) * N);
    int start_point = N-1;
    str[N] = '\0';
    str[start_point] = '1';
    while (start_point >= 0) {
        printf("%s ", str+start_point);
        str[N-1] ++;
        int check_bit = N-1;
        while (str[check_bit] > '9' && check_bit >= 0) {
            str[check_bit] = '0';
            if (check_bit != 0) str[check_bit - 1] ++;//防止数组越界
            check_bit--;
            if (check_bit < start_point) {
                start_point--;
            }
            /*
            解释下，在数组中，数字是按左高位右低位的样子存放，即模拟书写的习惯
            start_point标定从哪数组一位开始打印，自然也是数字的最高位
            check_bit用来标定循环进位，当check_bit“超过”start_point时，start_point-1，表示最高位的进位。
            */
        }
    }
    free(str);
}   
//----------------------------------------------------------------------------------------------------------------------------
void recur_print(char * str, int N) {
    int i = 0;
    while (str[i] == '0' && i < N-1) {
        ++i;
    }
    printf("%s ", str+i);
}

void recur (char *str, int N, int index) {
    if (index == N - 1) {
        //got a number
        recur_print(str, N);
        return;
    }
    for (int i = 0; i < 10; ++i) {
        str[index+1] = '0' + i;
        recur(str, N, index+1);
    }
}

void permutation (int N) {
    //排列组合法，递归实现。
    //给定位数的话，所有的数字其实就是0到9的排列组合
    //以前似乎写过，总之就是靠index的增加来逐渐凑满一个数字的格子
    char *str = (char*)malloc (sizeof(char) * N+1);
    memset(str, 0, sizeof(char) * (N+1));
    str[N] = '\0';
    int i = '0';
    while (i <= '9') {
        str[0] = i++;
        recur(str, N, 0);
    }
    free(str);
}


int main(){
    int N = 4;
    //simple(N);
    //with_string_increase(N);
    permutation(N);
    return 0;
}