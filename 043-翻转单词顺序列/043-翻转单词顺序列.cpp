/*
#题意
题目描述

牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？

样例输入

student. a am I

JOBDU! like I and Freshman a I'm

样例输出

I am a student.

I'm a Freshman and I like JOBDU!

*/
#include <iostream>
#include <string>
using namespace std;

void with_stl_reverse(string s) {
	int i = 0;
	while (i < s.size()) {
		if (s[i] == ' ') {
			++i;
			continue;
		}
		//find a word
		int k = i;
		while (k < s.size() && s[k] != ' ') {
			++k;
		}
		reverse(s.begin() + i, s.begin() + k);
		i = k;
	}
	reverse(s.begin(), s.end());
	cout << s << endl;
}

int main() {
	string s{ "student. a am I" };
	with_stl_reverse(s);
	with_stl_reverse("JOBDU! like I and Freshman a I'm");
	return 0;
}