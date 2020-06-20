/*
#题意
题目描述

统计一个数字在排序数组中出现的次数。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int brutal_force(vector<int>& v, int n) {
	int cnt = 0;
	bool flag = false;
	for (int i = 0; i < v.size(); ++i) {
		while (v[i] == n) {
			flag = true;
			cnt++;
			++i;
		}
		if (flag) break;
	}
	return cnt;
}

//自己想了想，虽然不太聪明，但是二分法可以做，而且时间复杂度是O(logN + C) = O(logN)
int binary_search(vector<int>& v, int n) {
	int mid = v.size() / 2, left = 0, right = v.size() - 1;
	while (v[mid] != n) {
		if (v[mid] > n) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
		mid = (left + right) / 2;
	}
	int count = 0;
	if (v[mid] == n) {
		int t = mid;
		while (t >= 0 && v[t] == n) {
			count++;
			t--;
		}
		t = mid + 1;
		while (t < v.size() && v[t] == n) {
			count++;
			t++;
		}
	}
	return count;
}

//答案给了改进版的二分，理解了下也挺简单的
//修改二分mid的满足条件，定位最左和最右的位置，index相减+1
int get_first_one(vector<int>& v, int n, int l, int r) {
	if (l > r) return -1;
	int mid = (l + r) / 2;
	if (v[mid] > n) {
		r = mid - 1;
	}
	else if (v[mid] < n) {
		l = mid + 1;
	}
	else if (mid >= 0 && v[mid] == n) {
		if (mid == 0 || v[mid - 1] != n) {
			return mid;
		}
		else {
			r = mid - 1;
		}
	}
	return get_first_one(v, n, l, r);
}

int get_last_one(vector<int>& v, int n, int l, int r) {
	if (l > r) return -1;
	int mid = (l + r) / 2;
	if (v[mid] > n) {
		r = mid - 1;
	}
	else if (v[mid] < n) {
		l = mid + 1;
	}
	else {
		if (mid == v.size() - 1 || v[mid + 1] != n) {
			return mid;
		}
		else {
			l = mid + 1;
		}
	}
	return get_last_one(v, n, l, r);
}

int approved_bi_search(vector<int>& v, int n) {
	return get_last_one(v, n, 0, v.size() - 1) - get_first_one(v, n, 0, v.size() - 1) + 1;
}

/*
C++真是什么鬼方法都有哦
##STL的

　ForwardIter lower_bound(ForwardIter first, ForwardIter last,const _Tp& val)
算法返回一个非递减序列[first, last)中的第一个大于等于值val的位置。

ForwardIter upper_bound(ForwardIter first, ForwardIter last, const _Tp& val)
算法返回一个非递减序列[first, last)中第一个大于val的位置。
*/


int GetNumberOfK(vector<int> data ,int k)
{
    //在<algorithm>中，
    //返回的是迭代器
    auto upper = upper_bound(data.begin(),data.end(),k);
    auto low = lower_bound(data.begin(),data.end(),k);
    return upper - low;
}

int main() {
	int arr[] = { 1, 2, 3, 3, 3, 3,3, 4, 5 };
	vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
	cout << brutal_force(v, 3) << endl;
	cout << binary_search(v, 3) << endl;
	cout << approved_bi_search(v, 3) << endl;
    cout << GetNumberOfK(v, 3) << endl;
	return 0;
}