/*
题目描述

大家都知道斐波那契数列， 现在要求输入一个整数n， 请你输出斐波那契数列的第n项。

f(0) = 0, f(1) = 1
*/

#include <stdio.h>

int naive (int n) {
    if (n < 0) {printf ("Illegal input.\n"); return 0;}
    if (n <= 1) return n;
    return naive(n-1) + naive(n-2);
}//会爆栈

int iterative(int n) {
    if (n < 0) {printf ("Illegal input.\n"); return 0;}
    if (n < 2) return n;
    int i = 2;
    int res = 0;
    int f0 = 0, f1 = 1;
    while (i <= n) {
        res = f1 + f0;
        f0 = f1;
        f1 = res;
        ++i;
    }
    return res;
}

//这里再介绍一种数学解法，效率为O(n*logn)。首先有一个公式：
//矩阵  [f(n) f(n-1)   = [1 1 ^(n-1)，即转化为零一矩阵的n-1次方。
//      f(n-1) f(n-2)]    1 0]
//这样可以直接用矩阵计算的方式求得f(n)项，但是我今生已经与数学无缘，就不展开了  

int main () {
    int n = 30;
    //printf("%d\n", naive(n));
    printf ("%d\n", iterative(n));
    return 0;
}