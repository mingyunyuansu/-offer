/*
题目描述
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
*/
//跟跳台阶一样的思路。从边界竖着放一块，显然很好地缩减了问题规模。如果横着放一块，那就会发现这一块下方刚好缺一块，只能再塞一块，因此依然是一种方法，也同样缩减了问题规模。
//以矩形长n为变量，可得f(n) = f(n-1) + f(n-2)。显然f(1) = 1, f(2) = 2（因为分横竖），接下来同斐波那契数列。
#include <stdio.h>

long placement (int n) {
    if (n <= 2) return n;
    long f1 = 1, f2 = 2;
    int i = 3;
    long res = 0;
    while (i <= n) {
        res = f1 + f2;
        f1 = f2;
        f2 = res;
        ++i;
    }
    return res;
}

int main () {
    printf("%d\n", placement(4));
    return 0;
}