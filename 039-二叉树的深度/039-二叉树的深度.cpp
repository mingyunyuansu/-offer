/*
#题意
题目描述

输入一棵二叉树，求该树的深度。

从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
*/
#include <iostream>
using namespace std;

struct node {
public:
	int val;
	node* left;
	node* right;
	node(int val) :val(val), left(NULL), right(NULL) {}
};

int recur(int curr, node* root) {
	if (root == NULL || root->left == NULL && root->right == NULL) return curr;
	int cnt = recur(curr + 1, root->left);
	int r_cnt = recur(curr + 1, root->right);
	cnt = (cnt > r_cnt) ? cnt : r_cnt;
	return cnt;
}

int main() {
	node* root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->right->left = new node(5);
	root->right->left->left = new node(7);
	root->right->right = new node(6);

	cout << recur(1, root) << endl;
	return 0;
}