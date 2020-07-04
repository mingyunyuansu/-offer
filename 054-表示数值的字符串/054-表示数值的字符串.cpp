/*
#题目描述
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

例如， 字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
*/
//感觉比较无趣的一题，跟编译原理的自动机似的，感觉更在于理清逻辑，
//与编程技巧关系不大
#include <iostream>
#include <string>
using namespace std;

bool is_expotential_legal(string& s, int pos) {
	int start = pos + 1;
	int i = start;
	bool has_point = false;
	while (i < s.size()) {
		if (s[i] == '+' || s[i] == '-') {
			if (i != start) return false;
			else ++i;
		}
		else {
			if (s[i] < '0' || s[i] > '9') {
				if (s[i] == '.' && i != start && has_point == false) {
					has_point = true;
					++i;
				}
				else return false;
			}
			else ++i;
		}
	}
	return true;
}

bool is_number(string& s) {
	bool has_point_in_left = false;
	int digits_in_left = 0;
	int i = 0;
	while (i < s.size()) {
		if (s[i] == '+' || s[i] == '-') {
			if (i != 0) {
				return false;
			}
			else {
				++i;
				continue;
			}
		}
		if (s[i] == '.') {
			if (i == 0 || has_point_in_left) {
				return false;
			}
			else {
				has_point_in_left = true;
				++i;
				continue;
			}
		}
		if (s[i] < '0' || s[i] > '9') {
			if (s[i] != 'e' && s[i] != 'E') {
				return false;
			}
			else {
				if (digits_in_left >= 2 || !is_expotential_legal(s, i)) {
					return false;
				}
				else break;
			}
		}
		else {
			++i; 
			if (!has_point_in_left) digits_in_left++;
		}
	}
	return true;
}

int main() {
	string s = "12e+4.3";
	if (is_number(s)) cout << "Yes" << endl;
	return 0;
}