/*
题目描述

输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。

样例输入

3 4 5 -1

样例输出

1 2 32
*/
#include <stdio.h>

int count (int n) {
    //左移flag，一位一位测试
    //一共测32次，移了31次，第一次测时还没移位（以int为例）
    int i = 0, count = 0;
    int flag = 1;
    while (i < sizeof(int)*8) {
        if ((flag & n) != 0) {
            count++;
        } 
        flag <<= 1;
        ++i;
    }
    return count;
}

int lowbit(int n) {
    //可以优化，使得有几个1就只循环几次
    //举例a = 1100，b = 1100 - 1 = 1011
    //a & b = 1000，即这个操作一定能准确地去掉原数a的最右一位1
    //利用这个特性来不断去1
    int t = n, count = 0;
    while (t) {
        t = t & (t - 1);
        count ++;
    }
    return count;
}

int main () {
    printf("%d\n", count(1<<31));
    printf("%d\n", lowbit(1<<31));
    return 0;
}
//C++有bit这个STL来专门做个事，C的limits.h中也有BITSET之类的宏