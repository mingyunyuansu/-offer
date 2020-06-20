/*
#题意
题目描述

输入一棵二叉树，判断该二叉树是否是平衡二叉树。
*/

//书上和网上的答案说的很复杂一串，但是其实就是我的方法的翻版
//在之前计算深度的那个办法基础上加一个判断，然后指针bool就行
//他们最优化的那个方法变成了返回bool，指针化深度，就有点麻烦
#include <iostream>
using namespace std;

struct node {
public:
	int val;
	node* left;
	node* right;
	node(int val) :val(val), left(NULL), right(NULL) {}
};

int recur(int curr, node* root, bool* isBal) {
	if (root == NULL || root->left == NULL && root->right == NULL) return curr;
	int cnt = recur(curr + 1, root->left, isBal);
	int r_cnt = recur(curr + 1, root->right, isBal);
	if (cnt - r_cnt > 1 || r_cnt - cnt > 1) *isBal = false;
	cnt = (cnt > r_cnt) ? cnt : r_cnt;
	return cnt;
}
//不过看了一下书上给出的最优解其实是用后序遍历，
//感觉也很不错，这样的话，用指针存深度也可以很简洁
int main() {
	node* root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->right->left = new node(5);
	root->right->left->left = new node(7);
	root->right->right = new node(6);
	bool isBal = true;
	cout << recur(1, root, &isBal) << endl;
	cout << isBal << endl;
	return 0;
}