/*
#题意
题目描述

LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...

他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票 ,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”, “Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。 上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。

LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何。为了方便起见,你可以认为大小王是0。

样例输入

3 5 1 0 4

3 5 4 7 6

3 5 7 4 8

样例输出

So Lucky!

So Lucky!

Oh My God!
*/
#include <iostream>
#include <vector>
#include <algorithm>

#define BIT_SET(num, pos) (num |= (1 << pos))
#define BIT_GET(num, pos) ((1<<pos) & num)

bool with_stl_sort(std::vector<int> v) {
	std::sort(v.begin(), v.end());
	int cnt = 0;
	while (v[cnt] == 0) cnt++;
	for (int i = cnt; i < v.size(); ++i) {
		if (i == 0) continue;
		if (v[i] - v[i - 1] != 1) {
			if (cnt - (v[i] - v[i - 1] - 1) >= 0) {
				cnt = cnt - (v[i] - v[i - 1] - 1);
			}
			else {
				return false;
			}
		}
	}
	return true;
}

//答案提醒了一种方法
//首先明确，一个顺子，除零外的整个数组的最大差值必须为4，且没有除零外的相同元素
//这两个条件同时卡主，就能确定是不是顺子
//同时因为牌的数字只到13，可以用bitmap来确定是否重复
bool time_comlexity_n(std::vector<int>& v) {
	int min = v[0], max = v[0], bitmap = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] == 0) continue;
		if (BIT_GET(bitmap, v[i]) != 0) {
			return false;
		}
		else {
			BIT_SET(bitmap, v[i]);
		}
		if (v[i] < min) min = v[i];
		if (v[i] > max) max = v[i];
		if (max - min > 4) return false;
	}
	return true;
}

int main() {
	std::vector<int> v1{ 3,5,1,0,4 };
	std::vector<int> v2{ 3,5,4,7,6 };
	std::vector<int> v3{ 3, 5, 7, 4, 8 };
	if (with_stl_sort(v1)) std::cout << "So lucky!\n"; else std::cout << "Oh My God!" << std::endl;
	if (with_stl_sort(v2)) std::cout << "So lucky!\n"; else std::cout << "Oh My God!" << std::endl;
	if (with_stl_sort(v3)) std::cout << "So lucky!\n" << std::endl; else std::cout << "Oh My God!" << std::endl;
	std::cout << "--------------------------------------" << std::endl; 
	if (time_comlexity_n(v1)) std::cout << "So lucky!\n"; else std::cout << "Oh My God!" << std::endl;
	if (time_comlexity_n(v2)) std::cout << "So lucky!\n"; else std::cout << "Oh My God!" << std::endl;
	if (time_comlexity_n(v3)) std::cout << "So lucky!\n"; else std::cout << "Oh My God!" << std::endl;

	return 0;
}