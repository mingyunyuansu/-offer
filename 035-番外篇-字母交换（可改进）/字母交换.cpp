/*
链接：https://www.nowcoder.com/questionTerminal/43488319efef4edabada3ca481068762
来源：牛客网

【编码题】字符串S由小写字母构成，长度为n。定义一种操作，每次都可以挑选字符串中任意的两个相邻字母进行交换。询问在至多交换m次之后，字符串中最多有多少个连续的位置上的字母相同？



输入描述:
第一行为一个字符串S与一个非负整数m。(1 <= |S| <= 1000, 1 <= m <= 1000000)


输出描述:
一个非负整数，表示操作之后，连续最长的相同字母数量。
示例1
输入
abcbaa 2
输出
2
说明
使2个字母a连续出现，至少需要3次操作。即把第1个位置上的a移动到第4个位置。
所以在至多操作2次的情况下，最多只能使2个b或2个a连续出现。
*/
//这题原来是字节2018的秋招笔试最后一题
//看着好像有思路，但是做不出来，看了答案是用区间动态规划
//ACM的老哥则提示利用数学性质其实有O(N)的办法
//但是考虑到泛用性，今天就先只看动规专场

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//大概思路是，令原串为s，先把每一个单独种类的char提出来。
//例如a的提取是，m(a) = [0, 4, 5]，里面是a的index。转移方程是f(i, j)，表示对应到原串中的完成s[i]到s[j]连续所需要的移动次数。
//一开始取的vector，LTE了，看了一下可能是vector::clear只清数据不释放capacity。
//可用和一个空数组swap来解决，但是这里先不表。今天先去B站九章算法听了一节DP入门，真是长进了不少dp技能，原来我之前的学习如此低效
int dp[1005][1005] = { 0 };
int dynamic_programming(string& str, int movement) {
	map<char, vector<int> > index_m;//每一个char种类的位置数组
	const int length = str.length();
	int ans = 0;
	//vector<vector<int> > dp;
	/*
	for (int i = 0; i < length; ++i) {//初始化二维dp
		vector<int> v(length);
		dp.push_back(v);
	}
	*/
	for (int i = 0; i < str.size(); ++i) {
		if (index_m.find(str[i]) == index_m.end()) {
			vector<int> v{};
			index_m.insert(make_pair(str[i], v));
		}
		index_m[str[i]].push_back(i);
	}//先做好所有的提取工作
	for (map<char, vector<int>>::iterator iter = index_m.begin(); iter != index_m.end(); ++iter) {
		//对每一个char
		for (int i = iter->second.size() - 1; i >= 0 ; --i) {
			//二重遍历，注意i和j的开始结束范围，很讲究，必须保证可以同时往两边扩张
			for (int j = i; j < iter->second.size(); ++j) {
				if (i == j) dp[i][j] = 0;
				else if (i == j - 1) {
					dp[i][j] = iter->second[j] - iter->second[i] - 1;
					//单纯地把j项和i项挪到一起需要的步数
				}
				else {
					dp[i][j] = dp[i + 1][j - 1] + iter->second[j] - iter->second[i] - 1 - (j - 1 - (i + 1) + 1);
					//注意这里的计算，中间已经排好顺序。加入[i]和[j]时本来只需要iter->second[j] - iter->second[i] - 1步，但是因为中间已经有排好的子序列，所以需要减去那些个数
				}
				if (dp[i][j] <= movement && j - i + 1 > ans) ans = j - i + 1;
			}
		}
		/*
		dp.clear();
		for (int i = 0; i < length; ++i) {
			vector<int> v(length);
			dp.push_back(v);
		}
		*/
	}

	return ans;
}

int main() {
	string str;
	int movement = 0;

	//while (cin >> str >> movement)
		//cout << dynamic_programming(str, movement) << endl;
	string t{ "hkdbqojqvxlfulshrhpysezhlyzolb" };
		cout << dynamic_programming(t, 20) << endl;
	return 0;
}
