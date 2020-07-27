/*
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m] 。请问 k[0]k[1]...*k[m] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//DP稍微有点迷惑。主要是要区分多出来一个状态，也就是剪一刀就不再箭了
//即j * (i - j)和j * dp[i - j]，右边的i - j可减可不减，但是dp[i - j]只储存一定减的状态。
int dynamic_programming (int n) {
    vector<int> dp(n + 1);
    dp[2] = 1;
    dp[3] = 2;
    for (int i = 4; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = max({j * (i - j), j * dp[i - j], dp[i]});
        }
    }
    return dp[n];
}

//Greedy。其实我是没想到贪心原来是这么难的。数学推导可看
//https://leetcode-cn.com/problems/jian-sheng-zi-lcof/solution/mian-shi-ti-14-i-jian-sheng-zi-tan-xin-si-xiang-by/
//把绳子分为每段长为x的a段，设总长度为n，则转化为求x^(n/x)的极值。
//复习一波极值求法和链式法则，总之最后求出极值存在于x = e处，要么2要么3。
//所以就是想办法取3的长度，余数为2则乘上去，为1则需要把最后一段3掐下来凑成2x2，因为2x2 > 1 x 3

int greedy(int number) {
    if (number < 1) return 0;
    else if (number == 2) return 1;
    else if (number == 3) return 2;
    int remainder = number % 3;
    int cut = number / 3;
    return remainder == 1 ? pow(3, cut - 1) * 4 : pow(3, cut) * 2;
}

int main() {
    cout << dynamic_programming(3) << endl;
    cout << greedy(8);
    return 0;
}