/*
与正片类似，但是这次是，只有一个数出现了一次，剩下的都是三次
很显然或运算失效了
*/
//答案给出的办法牛逼炸了，不看我肯定写不出来
//基本思路是，对所有数，分别求它们二进制数的每一个位的和。
//因为有三个数是相同的，所以这位的和能被3整除是得到目标数是0，不能整除则为1

#include <vector>
#include <iostream>
using namespace std;

int find_the_unique_from_triple_duplicated(vector<int>& v) {
	int bits = sizeof(v[0]) * 8;
	int ans = 0;
	vector<int> tmp(bits);
	for (int i = 0, test = 1; i < bits; ++i) {
		for (auto x : v) {
			tmp[i] += (test & x);
		}
		if (tmp[i] % 3) ans += test;
		test <<= 1;
	}
	return ans;
}

int main() {
	vector<int> v{ 2,2,2,9,4,4,4,5,6,5,5,6,6 };
	cout << find_the_unique_from_triple_duplicated(v);
	return 0;
}