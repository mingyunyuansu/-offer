/*
题目描述

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。 输入 例如输入数组

{3，32，321}

输出

则打印出这三个数字能排成的最小数字为

321323
*/
//按照整数来处理是不现实的，需要转为字符串。
//那么问题就可以转化为对一个字符串数组进行排序，顺序打印即为结果。
//尽管看起来字典序可以用，但是这种感觉是没有依据的，比如33+332 > 332+33，但是332 > 33的字典序（长度不一且前面都相等时时，记住结尾其实是0，所以长的那个串更大）
//这就需要自定义排序规则对于字符串，非常直接地定义ab > ba，则 a > b，ba > ab，则b > a。

//这题算法上不难，但是需要理解排序规则
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int my_compare(string a, string b) {
	return (a + b > b + a) ? 1 : -1;
}

void qsort(vector<string>& sv, int l, int r) {
	if (l >= r) return;
	srand(time(NULL));
	int pivot_index = rand() % (r - l + 1) + l;
	swap(sv[r], sv[pivot_index]);
	int stone = l;
	string pivot = sv[r];
	for (int i = l; i < r; ++i) {
		if (my_compare(sv[i], pivot) == -1) {
			//前者小
			swap(sv[stone++], sv[i]);
		}
	}
	swap(sv[stone], sv[r]);
	qsort(sv, l, stone - 1);
	qsort(sv, stone + 1, r);
}

void solu(vector<int>& v) {
	vector<string> sv;
	for (int x : v) {
		sv.push_back(to_string(x));
	}
	qsort(sv, 0, sv.size() - 1);
	for (auto s : sv) {
		cout << s;
	}
	cout << endl;
}

int main() {
	vector<int> v{ 3,32,321 };
	solu(v);
	return 0;
}