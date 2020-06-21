/*
题目描述

输入两颗二叉树A，B，判断B是不是A的子结构。

因为需要自己构造二叉树测试，不想太麻烦，就手动构建了https://leetcode-cn.com/problems/subtree-of-another-tree/
实例的二叉树
*/

//思路非常直接，我怀疑还有其他办法
//但是答案也只有一种解法
///不过蛮有意思的一题，与其说是在练二叉树，不如说是在练递归
//托它的福，对于递归是该用变量传值，还是直接用返回传值，
//稍微加深了点理解

#include <iostream>
using namespace std;

struct node {
	int val;
	node* left = NULL;
	node* right = NULL;
};

bool is_sub_tree(node* root1, node* root2) {
	if (root1 == NULL && root2 == NULL)return true;
	else if (root1 == NULL && root2) return false;
	else if (root1 && root2 == NULL) return false;
	else if (root1->val != root2->val) return false;

	return is_sub_tree(root1->left, root2->left) && is_sub_tree(root1->right, root2->right);
}

bool pre_search(node* root, node* root2) {
	if (!root2 || !root) return false;
	if (root2->val == root->val) {
		//find the possible starting point
		if (is_sub_tree(root, root2)) {
			return true;
		}
	}
	return pre_search(root->left, root2) || pre_search(root->right, root2);
}



int main(){
	//构造二叉树
	node* root1 = new node();
	root1->val = 3;
	root1->left = new node();
	root1->right = new node();
	root1->left->val = 4;
	root1->right->val = 5;
	root1->left->left = new node();
	root1->left->right = new node();
	root1->left->left->val = 1;
	root1->left->right->val = 2;

	node* root2 = new node();
	root2->val = 4;
	root2->left = new node();
	root2->right = new node();
	root2->left->val = 1;
	root2->right->val = 2;

	node* root3 = new node();
	root3->val = 3;
	root3->left = new node();
	root3->right = new node();
	root3->left->val = 4;
	root3->right->val = 5;
	root3->left->left = new node();
	root3->left->right = new node();
	root3->left->left->val = 1;
	root3->left->right->val = 2;
	root3->left->right->left = new node();
	root3->left->right->left->val = 0;

	if (post_search(root1, root2)) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
