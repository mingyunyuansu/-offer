/*
题意

样例输入

1 2 3 2 2 2 5 4 2

样例输出

2
*/
#include <iostream>
#include <vector>
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



int main() {
	vector<int> v{ 5, 5, 2, 2, 3, 3, 5, 5, 5 };
	intuitive(v);
	cout << endl;
	v = { 5, 5, 2, 2, 2};
	recur(v, 0, v.size()-1, v.size()/2);
	cout << endl;
	return 0;
}