/*
题意

样例输入

1 2 3 2 2 2 5 4 2

样例输出

2
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

//直觉上思路很简单，先排序，然后位于数组中间的数一定是答案
void my_quick_sort(vector<int> &arr, int l, int r) {
	if (l >= r) return;
	int pivot = arr[r];
	int pivot_index = r, stone = l;
	int p = l, q = r;
	while (p < q) {
		if (arr[p] <= pivot) {
			swap (arr[stone++], arr[p]);
		}
		p++;
	}
	swap(arr[stone], arr[r]);
	pivot_index = p;
	my_quick_sort(arr, l, stone - 1);
	my_quick_sort(arr, stone + 1, r);
}

void intuitive(vector <int>& v) {
	my_quick_sort(v, 0, v.size()-1);
	cout << v[v.size() / 2];
}

//看了一圈，这个题目可以拓展得非常宽。原型其实是找第K大的数
//https://github.com/mingyunyuansu/CodingInterviews/tree/master/029-%E6%95%B0%E7%BB%84%E4%B8%AD%E5%87%BA%E7%8E%B0%E6%AC%A1%E6%95%B0%E8%B6%85%E8%BF%87%E4%B8%80%E5%8D%8A%E7%9A%84%E6%95%B0%E5%AD%97
//上面方法非常多，还有几个拓展的链接。
//不过还有一种比较有价值的办法，依然是分治，但是充分利用中位数的概念。
//即，模拟快排的过程，如果递归过程中左右两半数组长度相等，说明找到了中位数。
//否则中位数应该在长的那一半数组，继续递归。
void recur(vector<int> & arr, int l, int r, int half_size) {
	//注意，比较用的中位数坐标，是用整个数组算出来的
	//因为子串数组的中位数和母串不一定在同一个位置
	if (l >= r) return;
	int pivot = arr[r];
	int p = l, q = r;
	int pivot_index = r;
	while (p < q) {
		while (arr[p] <= pivot && p < q) {
			p++;
		}
		while (arr[q] > pivot && p < q) {
			q--;
		}
		if (p < q) {
			swap(arr[p], arr[q]);
		}
	}
	swap(arr[p], arr[pivot_index]);
	pivot_index = p;
	if (p == half_size) {
		cout<< arr[pivot_index];
		return;
	}
	else if (p < half_size) {
		recur(arr, p+1, r, half_size);
	}
	else {
		recur(arr, l, p-1, half_size);
	}
}

//上一种方法其实可以修改第四个形参，使得可以用作找第K大的数
//但是还有一种完全利用“比一半还多”的写法，叫做攻守阵地。
//有一点类似动态规划。以一个数为起点，count = 1，如果碰到不等的数count--，相同则count++。
//count归零则从下一个数开始重启。目标数因为个数过半，所以一定会以count>0的形式留下来。
//时间复杂度即O(N)
int fully_utilised(vector<int> arr) {
	if (arr.size() <= 1) return arr[0];
	int count = 0, ans = arr[0];
	for (int x : arr) {
		if (count == 0) ans = x;
		if (x == ans) {
			count++;
		}
		else {
			count--;
		}
	}
	return ans;
}

//答案也介绍了使用STL的方法
int with_count(vector<int> arr) {
	for (int i = 0; i < arr.size(); ++i) {
		if (count(arr.begin(), arr.end(), arr[i]) > arr.size() / 2)
			return arr[i];
	}
	return -1;
}

//也可以复习下使用map
int with_map(vector <int> arr) {
	map<int, int> cnt_map;
	for (auto x : arr) {
		cnt_map[x]++;
	}
	for (map<int, int>::iterator it = cnt_map.begin(); it != cnt_map.end(); ++it) {
		if (it->second > arr.size() / 2)
			return it->first;
	}
	return -1;
}

int main() {
	vector<int> v{ 5, 5, 2, 2, 3, 3, 5, 5, 5 };
	intuitive(v);
	cout << endl;

	v = { 5, 5, 2, 2, 2};
	recur(v, 0, v.size()-1, v.size()/2);
	cout << endl;

	v = { 5, 5, 2, 2, 3, 3, 5, 5, 5, 1,1,1,1,1,1,1,1,1,1,1,1,1, 5,5 };
	cout << fully_utilised(v) << endl;

	v = { 5, 5, 2, 2, 3, 3, 5, 5, 5, 1,1,1,1,1,1,1,1,1,1,1,1,1, 5,5 };
	cout << with_count(v) << endl;

	v = { 5, 5, 2, 2, 3, 3, 5, 5, 5, 1,1,1,1,1,1,1,1,1,1,1,1,1, 5,5 };
	cout << with_map(v);
	cout << endl;
	return 0;
}