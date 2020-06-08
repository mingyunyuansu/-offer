/*
题意
题目描述

输入n个整数，找出其中最小的K个数。

例如输入4,5,1,6,2,7,3,8这8个数字， 则最小的4个数字是1,2,3,4,。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//话说最直接的解法就是排序。。。简单又直接，
//快排那样的平均效率O(NlogN)，也不差了。
//太简单这里就不写了

//直接看答案，提到上一题，或者说快速排序的分治部分在这里依然适用。
//小于pivot的都在左边，大于的都在右边，那么当小于的个数<=K时，就可以把他们存进
//一个保留数组。存够K个即为答案。
void partition_recur(vector<int> &ans, vector<int> &arr, int K, int l, int r) {
	//这题可以加深对快速排序的认识。
	//任何时候，只要是pivot在一趟递归中定了下来，那么这个位置就完全确定了。
	//这个pivot在整个数组中，就是在这个位置。
	//同时，我写快速排序自然没问题，但是有可能因为粗心出现one-offset错误，是时候记一个模板了
	if (l >= r) {
		if (l == r && l == K) {
			for (int j = 0; j < K; ++j) {
				ans.push_back(arr[j]);
			}
		}
		return;
	}
	int index = rand() % (r - l + 1) + l;
	swap(arr[r], arr[index]);
	int pivot = arr[r];
	int small = l;
	for (int i = l; i < r; ++i) {
		if (arr[i] < pivot) {
			swap(arr[i], arr[small++]);
		}
	}
	swap(arr[small], arr[r]);
	index = small;
	if (K == small) {
		for (int j = 0; j < small; ++j) {
			ans.push_back(arr[j]);
		}
	}
	else if (small < K) {
		partition_recur(ans, arr, K, small + 1, r);
	}
	else {
		partition_recur(ans, arr, K, l, small - 1);
	}
	//这题折磨了我一天啊。。。一直是K的取值有几个数可用有几个数无输出
	//还以为是快排写错了，专门去记了模板快排
	//最后原来是l == r时，需要判断是不是这时恰好等于K，否则pivot就与K“错过”了
}


int main() {
	vector <int> v;
	v = { 4,5,1,6,2,7,3,8 };
	vector<int> ans;
	for (int i = 1; i < v.size() - 1; ++i)
	{
		v = { 4,5,1,6,2,7,3,8 };
		ans = {};
		partition_recur(ans, v, i, 0, v.size() - 1);
		for (auto x : ans) {
			cout << x << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}