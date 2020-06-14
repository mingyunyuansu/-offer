/*
#题意
题目描述

把只包含因子2、3和5的数称作丑数（Ugly Number）。

例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
*/
//典型的时间换空间
//但是书上的分析比较精彩。
//我们假设存在一个一个排好序的丑数序列，其最大值为M。
//则下一个最大值，一定是前面某个数乘2，或某个数乘3，或某个数乘5这三个结果中的最小值。因为数组已经有序，所以小于M的结果已经被包含，就不考虑。
//同时，不需要要每一次都从1开始乘，因为对于2来说，一定存在一个临界点数T2，使得所有小于T2的数*2都小于M，而所有大于T2的数*2都大于M。同理存在T3，T5，只需维护三个值并每次更新即可。
#include <iostream>
#include <vector>
using namespace std;

int my_min(int a, int b, int c) {
	return (a < b ? a : b) < c ? (a < b ? a : b) : c;
}

int ugly_number(int n) {
	int index = 1;
	vector<int> dp = { 1 };
	int t2 = 0, t3 = 0, t5 = 0;
	while (index < n) {
		int val = my_min(dp[t2] * 2, dp[t3] * 3, dp[t5] * 5);
		dp.push_back(val);
		index++;
		while (dp[t2] * 2 <= val) ++t2;
		while (dp[t3] * 3 <= val) ++t3;
		while (dp[t5] * 5 <= val) ++t5;
		
	}
	return dp[n - 1];
}

int main() {
	cout << ugly_number(1000);
	return 0;
}