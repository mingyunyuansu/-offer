/*
#题意
题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。 输入一个数组，求出这个数组中的逆序对的总数

样例输入

7 5 6 4

样例输出

5
*/
#include <iostream>
#include <vector>
using namespace std;

int brutal(vector<int>& v) {
	int ans = 0;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) ans++;
		}
	}
	return ans;
}

//因为学了DP，所以想拿DP写，结果转移方程写不出来
//看了答案才知道应该用归并排序法来做
//思想比较巧妙，建议看原书的解答
//关键操作就是，在准备合并两个子数组时，两个指针都指向两个数组最右（最大）
//若左指针数大于右指针，则说明右指针起的一堆数都是左指针数的逆数对，加上即可
//另一方面，已经数过一次后就排序排好，之后不再需要数已经排好序的内部数组了
int recur(vector<int>& v,int l, int r) {
	int count = 0;
	if (l >= r) return 0;
	vector<int> tmp(r - l + 1);
	int mid = (l + r) / 2;
	count += recur(v, l, mid);
	count += recur(v, mid + 1, r);
	int left = mid, right = r, cursor = tmp.size()-1;
	while (left >= l && right > mid) {
			if (v[left] > v[right]) {
				count += right - mid;
				tmp[cursor--] = v[left--];
			}
			else {
				tmp[cursor--] = v[right--];
			}
	}
	while (left >= l) {
		tmp[cursor--] = v[left--];
	}
	while (right > mid) {
		tmp[cursor--] = v[right--];
	}
	for (int i = l, c = 0; i <= r; ++i) {
		v[i] = tmp[c++];
	}
	return count;
}

int merge(vector<int> &v) {
	int ans = 0;
	ans += recur(v, 0, v.size() - 1);
	for (auto x : v) {
		cout << x << " ";
	}
	cout << endl;
	return ans;
}

int main() {
	vector<int> v{ 7, 5, 6, 4, 3, 2, 1, 9, 7, 5, 4, 4,3 ,2, 1};

	cout << brutal(v) << endl;;
	cout << merge(v) << endl;
	return 0;
}