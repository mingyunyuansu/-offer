/*
题意
题目描述

输入一个字符串,按字典序打印出该字符串中字符的所有排列

例如输入字符串abc,

则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

结果请按字母顺序输出。

注意 输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母

样例输入

abc

BCA

样例输出

abc acb bac bca cab cba ABC ACB BAC BCA CAB CBA
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//熟悉的题目，不过我看了解答才知道原来这个叫前缀码全排列
void recur(string prefix, string s) {
	if (s.size() == 0) {
		cout << prefix << " ";
	}
	else {
		for (int i = 0; i < s.size(); ++i) {
			recur(prefix + s[i], s.substr(0, i) + s.substr(i+1));
		}
	}
}

void my_solution(string s) {
	recur("", s);
}

//基于交换的思路
void based_on_swap(string &s, int begin) {
	if (begin == s.length()) {
		cout << s << " ";
	}
	for (int i = begin; i < s.length(); ++i) {
		swap(s[begin], s[i]);
		based_on_swap(s, begin + 1);
		swap(s[begin], s[i]);
	}
}

//据介绍，STL有排列用的模板
void with_stl(string s) {
	sort(s.begin(), s.end());
	cout << s << " ";
	while (next_permutation(s.begin(), s.end())) {
		cout << s << " ";
	}
}

int main() {
	string s = "abcd";
	my_solution(s);
	cout << endl;

	s = "abcd";
	based_on_swap(s, 0);
	cout << "\n";

	s = "abcd";
	with_stl(s);
	cout << endl;
	return 0;
}