/*
题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
*/
#include <stdio.h>
//跳n级台阶的跳树可以看做先跳1级再跳n-1级的跳树+先跳2级再跳n-2级的跳树
//f(n) = f(n-1) + f(n-2)
//显然f(1) = 1，f(2) = 2，f(3) = f(2) + f(1) = 3, ...
//即规定f1 = 1, f2 = 2，开始递推


int main () {
    long long f1 = 1, f2 = 2;
    long long n = 50;
    int i = 3;
    long long res = 0;
    if (n <= 2) {printf ("%lld\n", n); return 0;}
    while (i <= n) {
        res = f1 + f2;
        f1 = f2;
        f2 = res;
        ++i;
    }
    printf ("%lld\n", res);
    return 0;
}