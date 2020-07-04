/*
#题意
题目描述

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"abaca"匹配，但是与"aa.a"和"ab*a"均不匹配

样例输入

"a","ab*a"

样例输出

false
*/
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

//试了试，没写出来，虽然有思路
/*
使用string和引用的版本，不过有点别扭
bool divide_recur(string& s, string& p) {
	if (s.empty() && p.empty()) {
		return true;
	}
	if (!s.empty() && p.empty()) return false;
	if (p[1] == '*') {
		int i = 0;
		while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
			string ns = s.substr(i++), np = p.substr(2);
			if (divide_recur(ns, np)) return true;
		}
		string np = p.substr(2);
		return divide_recur(s, np);
	}
	else {
		if ((p[0] == '.'&&s[0]) || s[0] == p[0]) {
			string ns = s.substr(1), np = p.substr(1);
			return divide_recur(ns, np);
		}
		else {
			return false;
		}
	}
}
*/
bool match(char *str, char *pattern)
{
	if (*str == 0 && *pattern == 0)
		return true;
	if (*str && *pattern == 0)
		return false;
	//首先分下一个是否是*
	if (pattern[1] == '*')
	{
		while (*str && (*str == *pattern || *pattern == '.'))
		{
			//*匹配一个或多个
			if (match(str++, pattern + 2))
				return true;
		}
		//*匹配了0个
		return match(str, pattern + 2);
	}
	else
	{
		if (*str == *pattern || (*pattern == '.' && *str))
		{
			//注意这里 . 必须和非空字符匹配
			return match(str + 1, pattern + 1);
		}
		else
			return false;
	}
}

//DP
//dp[i][j]表示前i个和前k个s(s[0...i-1])和p(p[0...j-1])能否匹配
bool dynamic_programming(char *s, char *p)
{
	int s_len = strlen(s), p_len = strlen(p);
	vector<vector<bool> > dp(s_len+1, vector<bool>(p_len+1, false));
	for (int i = 0; i <= s_len; ++i) {
		for (int j = 0; j <= p_len; ++j) {
			if (j == 0) dp[i][j] = (i == 0);
			else if (p[j - 1] != '*') {
				if (p[j- 1] == '.' || p[j - 1] == s[i - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
			}
			else {
				if (j >= 2) {
					dp[i][j] = (dp[i][j - 2] || dp[i][j]);
				}
				if (j >= 2 && (s[i - 1] == p[j - 2] || p[j - 2] == '.')) {
					dp[i][j] = (dp[i][j] || dp[i - 1][j]);
				}
			}
		}
	}
	return dp[s_len][p_len];
}

int main()
{
	char a[] = "aaa", b[] = "aaa*a";
	if (match(a, b))
		cout << "Yes\n";
	if (dynamic_programming(a, b)) {
		cout << "Yes\n";
	}
	return 0;
}