/*
#题意
题目描述

汇编语言中有一种移位指令叫做循环左移（ROL）

现在有个简单的任务，就是用字符串模拟这个指令的运算结果。 对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。

例如，字符序列S=”abcXYZdef”, 要求输出循环左移3位后的结果，即“XYZdefabc”。

是不是很简单？OK，搞定它！
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void with_extra_space(string s, int k) {
	if (s.size() == 0 || k == 0) return;
	k %= s.length();
	int i = k, t = 0;
	string tmp(s.begin(), s.begin() + k);
	while (i < s.length()) {
		s[i - k] = s[i];
		++i;
	}
	i = i - k;
	while (i < s.length()) {
		s[i++] = tmp[t++];
	}
	cout << s << endl;
}
//github上的方法这题还有其他奇技淫巧
//感觉没必要。。。单纯的swap也是有在内部使用额外空间的
//不过有一个用reverse的有点骚
/*
#通过翻转直线循环移位
通过reverse操作 一个序列abcdefg，如果向左循环移动n位， 例如3位，则会编程(defg)(abc)，我们把原序列分成两部分，A=(abc)，B=(defg)，原序列为AB，我们要的结果为BA，则可以这么做：(ArBr)r = ((B)r)r((A)r)r=BA 假设原序列有n位，循环左移i位的过程如下：

reverse(0,i-1);

reverse(i,n-1);

reverse(1,n-1);

例如原序列：abcdefg，循环左移3位：

abc defg -=> cba defg

cba defg -=> cba gfed

cba gfed -=> defg abc
*/

void by_stl_reverse(string s, int k) {
	reverse(s.begin(), s.begin() + k);
	reverse(s.begin()+k, s.end());
	reverse(s.begin(), s.end());
	cout << s << endl;
}

int main() {;
string s{ "abcXYZdef" };
	with_extra_space(s, 3);
	by_stl_reverse(s, 3);
	return 0;
}