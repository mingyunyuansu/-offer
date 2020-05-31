#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/*----------------------------------------------------------------
题目描述

给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
----------------------------------------------------------------*/

double ordinary (double base, int exp) {
    if (exp == 0) return 1;
    double res = 1;
    if (exp > 0) {
        for (int i = 0; i < exp; ++i) {
            res *= base; printf("ord\n");
        }
    }
    else {
        /*
        For EPSILON, you can use the constants FLT_EPSILON, which is defined for float as 1.192092896e-07F, or DBL_EPSILON, which is defined for double as 2.2204460492503131e-016. You need to include float.h for these constants. These constants are defined as the smallest positive number x, such that x+1.0 is not equal to 1.0. Because this is a very small number, you should employ user-defined tolerance for calculations involving very large numbers.
        */
        if (base >= -DBL_EPSILON && base <= DBL_EPSILON) {printf("Zero base with zero exponent.\n"); exit(-1);}
        base = 1/base;
        for (int i = 0; i < abs(exp); ++i) {
            res *= base;
        }
    }
    return res;
}

double recur (double base, int exp) {
    if (exp == 0) return 1;
    if (exp % 2 == 0) {
        return recur(base, exp/2) * recur(base, exp/2);
    }
    else {
        return recur(base, (exp-1)/2) * recur(base, (exp-1)/2) * base;
    }
}

double bit_opt(double base, int exp) {
    //这是上种方法的变种，与位操作结合了，效率是O(logn)
    //n^(101) = n^(100) * n^(001)
    //注意理解这里的权重
    if (exp == 0) return 1;
    double res = 1, weight = base;
    while (exp) {
        if (exp & 1 == 1) {
            res *= weight; printf("bit\n");
        }
        weight *= weight;printf("bit\n");
        exp >>= 1;
    }
    return res;
}

int main () {
    double base;
    int exponent;
    printf("%lf\n", ordinary(3, 60));
    printf("%lf\n", recur(3, 30));
    printf("%lf\n", bit_opt(3, 60));
    return 0;
}