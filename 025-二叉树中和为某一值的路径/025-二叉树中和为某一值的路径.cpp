/*题意
题目描述

输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径*/
//以前在leetcode上做过这道题，但最后似乎是没做出来。
//主要问题出在如何保存数据上。以前是用Python，但是Python递归传值时似乎是传引用，造成不同路径的递归访问的是同一个数组（还是菜啊）。
//C++就没这问题。传值时传值，引用是引用。
//答案上还说了一下用静态变量来储存答案的办法。
//其实我以前不太会用递归的时候，也喜欢用这种办法，我甚至是直接用全局变量，因为这样思路还比较顺畅。
//但是不用说，这样铁定容易出问题，而且很low。
//答案说会在后面展示这个问题，这题就先这样吧。

#include <iostream>
#include <vector>
using namespace std;

class treeNode {
public:
	int val;
	treeNode* left;
	treeNode* right;
	treeNode(int value): val(value), left(NULL), right(NULL){}
};

void print_vector(vector<int> ans) {
	for (int x : ans) {
		cout << x << " ";
	}
	cout << endl;
}

void recur(treeNode* root, vector<int> ans, int sum, int cur_sum) {
	if (!root) return;
	ans.push_back(root->val);
	cur_sum += root->val;
	if (cur_sum > sum) {
		return;
	}
	else if (cur_sum == sum ) {
		if (!root->left && !root->right) {
			print_vector(ans);
			return;
		}
		else return;
	}
	else {
		recur(root->left, ans, sum, cur_sum);
		recur(root->right, ans, sum, cur_sum);
	}
}

int main() {
	treeNode* root = new treeNode(1);
	root->left = new treeNode(2);
	root->right = new treeNode(3);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(4);
	root->right->left = new treeNode(3);
	root->right->left->left = new treeNode(1);
	root->right->right = new treeNode(5);
	vector<int> ans;
	recur(root, ans, 7, 0);
	return 0;
}