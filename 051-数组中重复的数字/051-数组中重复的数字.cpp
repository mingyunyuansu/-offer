/*
#题意
题目描述

在一个长度为n的数组里的所有数字都在0到n-1的范围内。

数组中某些数字是重复的，但不知道有几个数字是重复的。

也不知道每个数字重复几次。请找出数组中任意一个重复的数字。

例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是重复的数字2或者3。

样例输入

2, 3, 1, 0, 2, 5, 3

2, 1, 3, 1, 4

样例输出

2

1
*/
#include <algorithm>
#include <limits>
#include <iostream>
#include <vector>
using namespace std;

int bit_map(vector<int>& v) {
	vector<int> bitmap(v.size());
	for (int x : v) {
		if (bitmap[x] == 0) {
			bitmap[x] = 1;
		}
		else {
			return x;
		}
	}
}

//题目本身有点常规，bit map基本是通用解了，不过还想补充点骚的
//符号位储存bit
#define GET_ORIGINAL_NUM(num) ((~(1 << (sizeof(int) * 8 - 1)) & num))
#define SET_SIGN(num) (num |= (1 << (sizeof(int) * 8 - 1)))
#define GET_SIGN(num) (num & (1 << (sizeof(int) * 8 - 1)))

int without_extra_space(vector<int> v) {
	for (int i = 0; i < v.size(); ++i) {
		if (GET_SIGN(v[GET_ORIGINAL_NUM(v[i])]) != 0) return GET_ORIGINAL_NUM(v[i]);
		else {
			SET_SIGN(v[GET_ORIGINAL_NUM(v[i])]);
		}
	}
	return -1;
}

//剑指offer的方法，把元素放到他该在的位置上
//充分利用了数组的特性
int the_best(vector<int> v) {
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] != i) {
			if (v[i] == v[v[i]]) return v[i];
			else swap(v[i], v[v[i]]);
		}
	}
	return -1;
}
int main() {
	vector<int> v{ 2, 3, 1, 0, 2, 5, 3};
	cout << without_extra_space(v) << endl;
	cout << bit_map(v) << endl;
	cout << the_best(v) << endl;
	return 0;
}