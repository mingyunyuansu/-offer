/*
题意
题目描述

HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。

今天测试组开完会后,他又发话了:

在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。

但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？

例如:{6,-3,-2,7,-15,1,2,2}, 连续子向量的最大和为8(从第0个开始,到第3个为止)。 你会不会被他忽悠住？
*/
//这个应该算是常见题了，经典的DP，O(N)时间O(1)的典范。
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int my_solu(vector<int> arr) {
	//贪心
	if (arr.empty()) return 0;
	int sum = 0, ans = 0;
	for (vector<int>::iterator ite = arr.begin(); ite != arr.end(); ++ite) {
		sum += *ite;
		if (sum > ans) ans = sum;
		if (sum < 0) sum = 0;
	}
	return ans;
}

int dynamic_programming(vector<int> arr) {
	//f(i) = f(i-1) + arr[i], if f(i-1) > 0
	//f(i) = arr[i], if f(i-1) <= 0, or i == 0
	//动态规划
	int ans = 0;
	if (arr.empty()) return 0;
	vector<int> dp(arr.size());
	for (vector<int>::iterator ite = arr.begin(), ite_dp = dp.begin(); ite != arr.end(); ++ite, ++ite_dp) {
		if (ite_dp == dp.begin()) {
			if (*ite > 0) {
				*ite_dp = *ite;
			}
		}
		else {
			if (*(ite_dp - 1) > 0) {
				*ite_dp = *(ite_dp - 1) + *ite;
			}
			else {
				*ite_dp = *ite;
			}
		}
		if (ans < *ite_dp) ans = *ite_dp;
	}
	return ans;
}

//我个人认为贪心应该是最优解了，但是
//题目认为应该考虑数组全为负的情况。
//我认为这时答案取空集，但是题目认为应该取非空子集，所以有
int not_empty(vector<int> arr) {
	if (arr.empty()) return 0;
	int ans = INT_MIN, sum = 0;
	for (int x : arr) {
		sum += x;
		if (sum < 0) {
			sum = x;
		}
		if (sum > ans) {
			ans = sum;
		}
	}
	return ans;
}

int main() {
	vector<int> arr{ 6,-3,-2,7,-15,1,2,2 };
	vector<int> minuss{ -6,-3,-2,-7,-15,-1,-2,-2 };
	cout << my_solu(arr) << " " << my_solu(minuss) << endl;
	cout << dynamic_programming(arr) << " " << dynamic_programming(minuss) << endl;
	cout << not_empty(arr) << " " << not_empty(minuss) << endl;
	return 0;
}