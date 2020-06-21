/*
给定一个数s，输出所有和为s的连续正整数序列（至少有两个数）。
一个序列内递增排序，序列间按首数字大小递增排序。
*/
#include <iostream>
#include <vector>
using namespace std;

//稍微想了想就有思路了，又上牛客答案区装了一圈，
//发现他们对滑动指针方法叹为观止。。。
//emmm，我觉得稀松平常啊
//难道是我变厉害了？

void find_continuous_subarray_with_sum(vector<int>& v, int s) {
	int l = 1, r = 2;
	while (l < r && l <= s / 2) {
		int sum = (l + r)* ( r - l + 1 ) / 2;
		if (sum < s) {
			++r;
		}
		else  if (sum > s){
			++l;
		}
		else {
			int t = l;
			while (t <= r) {
				v.push_back(t++);
			}
			++l;
		}
	}
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
}

int main() {
	vector<int> ans;
	int s = 100;
	find_continuous_subarray_with_sum(ans, s);
}