/*
题意
题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
*/
//我又可耻的看了答案的分析了。
//很显然数组的最后一个元素即是根节点，而前面的部分又可以分为小与根（左子树）和大于根（右子树）。
//字数内部依然满足递归定义。
//和靠前序和中序构造原树是一样的思路，我应该想起来的，唉
//树的定义用的https://github.com/mingyunyuansu/CodingInterviews/tree/master/024-%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97
//题目的原图。
//另外，判断是否“符合”定义，只需要看根前面的数组是不是存在真正的分界点，而不是忽大忽小。
#include <iostream>
#include <vector>
using namespace std;


bool is_bin_search_tree(vector<int> & given_array, int l, int r) {
	if (l >= r) return true;
	//检测
	int i = l;
	for (; i < r && given_array[i] < given_array[r]; ++i) {
	};
	int j = r - 1;
	for (; j > i && given_array[j] > given_array[r]; --j) {
	};
	if (i < j) {
		return false;
	}
	else return is_bin_search_tree(given_array, l, i - 1) && is_bin_search_tree(given_array, j, r - 1);
}
//https://github.com/mingyunyuansu/CodingInterviews/tree/master/024-%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97
//这一题还有另外两种方法，但是我感觉有那么一点杂记的意思。
//而且我现在突然感觉时间有点紧了，这一题递归应该是最明晰的解，就到此为止吧。

int main() {
	//treeNode* root = new treeNode(1);
	vector<int> given_array{ 2, 9, 5, 16, 17, 15, 19, 18, 12 };
	vector<int> wrong{4,5,2,6,7,3,1 };
	if (is_bin_search_tree(given_array, 0, given_array.size()-1)) cout << "Yes\n";
	if (!is_bin_search_tree(wrong, 0, wrong.size()-1)) cout << "No\n";
	return 0;
}