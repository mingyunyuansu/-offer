/*
#题目描述

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。

如果当前字符流没有存在出现一次的字符，返回#字符。
*/
//想到了用容器储存一个字符的个数，却没想到储存位置。
//个数的问题可以在第二次出现的时候置个-1就当做作废
//ASCII表只有128位，可以直接建一个128位数组来存，不过复习一下map也挺好

//

/*
int find_the_first_unique_pos(string& s) {
	unordered_map<char, int> m;
	for (int i = 0; i < s.size(); ++i) {
		if (m.find(s[i]) == m.end()) {
			m[s[i]] = i;
		}
		else {
			m[s[i]] = -1;
		}
	}
}

int main() {

}
*/
//仔细看了一下题目才发现是要从字符流中判断。。。
//然后跑去看了下题解，还蛮有意思，同时用到map和queue。
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

class Solution {
	public:
	void Insert(char ch) {
		q.push(ch);
		if (m.find(ch) == m.end()) {
			m[ch] = true;
		}
		else m[ch] = false;
	}
	char FirstAppearingOnce() {
		while(!q.empty() && m.find(q.front())->second == false) {
			q.pop();
		}
		return q.empty()? '#':q.front();
	}
	private:
	unordered_map<char, bool> m;
	queue<char> q;
};

int main() {
	Solution solu;
	string test = "google";
	for (char c: test) {
		solu.Insert(c);
		cout << solu.FirstAppearingOnce() <<"\n";
	}
	return 0;
}

