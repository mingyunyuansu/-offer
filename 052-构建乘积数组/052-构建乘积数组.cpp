/*
#题意
题目描述

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]A[1]...*A[i-1]A[i+1]...*A[n-1]。

不能使用除法。

样例输入

[1, 2, 3, 4, 5]

样例输出

[120, 60, 40, 30, 24]
*/
//刷题已有小成感觉
//想了一下有了基本思路了，看了下答案果然是这样
#include <vector>
#include <iostream>
using namespace std;

void my_solution(vector<int>& v, vector<int>& ans) {
	for (int i = 0, tmp = 1; i < v.size(); ++i) {
		ans[i] = tmp;
		tmp *= v[i];
	}
	for (int i = v.size() - 1, tmp = 1; i >= 0; i--) {
		ans[i] *= tmp;
		tmp *= v[i];
	}
}

int main() {
	vector<int> v{ 1, 2, 3, 4, 5 };
	vector<int> ans(v.size());
	my_solution(v, ans);
	for (auto x : ans) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}