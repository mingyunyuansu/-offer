/*
#题意
题目描述

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字

样例输入

2 4 3 6 3 2 5 5

样例输出

4 6
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//如果只有一个出现一次，那就很简单，但是现在有两个
//想了一下，没想出来，看了答案挺复杂
//但是好强，这个题得背下来
//首先数组连续异或一遍，得到两个不同的目标数的异或结果a^b
//从它的二进制中找到一个位为1（这位一定存在，因为a^b != 0)，且a的这位和b的这位必定不同。
//那么回去原数组，把原数组按这位为1或0分为两个组，就可以保证a和b落在不同的组，接下来就很简单了
void find_two_different_numbers(vector<int>& data) {
	int t = data[0];
	for (int i = 1; i < data.size(); ++i) {
		t ^= data[i];
	}
	int test_bit = 1;
	while ((test_bit & t) == 0) {
		test_bit <<= 1;
	}
	int stone = 0;
	for (int i = 0; i < data.size(); ++i) {
		if (test_bit & data[i]) {
			swap(data[i], data[stone++]);
		}
	}
	int a = data[0], b = data[stone];
	for (int i = 1; i < stone; ++i) {
		a ^= data[i];
	}
	for (int i = stone + 1; i < data.size(); ++i) {
		b ^= data[i];
	}
	cout << a << " " << b << endl;
}

//github那里介绍了一个很实用的小知识。计算机内存的全部是补码这个众所周知。
//一个负数的补码，其实就是其真值（正数的原码），从最低位开始往左数，一直到碰见第一个1
//这个1右边的全部保留（全零），左边的全取反，这个1保留
//所以确定一个位为1，可以用a & (-a)，得到从右往左数的第一个1，再左边因为是反的所以得0，右边本来就是0

int main() {
	vector<int> data{ 2, 4, 3, 6, 3, 2, 5, 5 };
	find_two_different_numbers(data);
	return 0;
}