/*
题意
题目描述

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct treeNode {
	int val;
	treeNode* left;
	treeNode* right;
	treeNode(int val) : val(val), left(NULL), right(NULL){}
};

//自己想了想，没什么好思路，感觉自己依然很弱，这个修改配上递归感觉脑海一片混乱。
//但是转念一想，我把中序遍历得到的排序结果存在一个数组里，然后在数组里顺着慢慢改，似乎可以。
//题目要求不创建新结点，我觉得勉强算过吧，虽然肯定不是好答案。
//自己写了下然后在牛客AC了。
void recur(treeNode* root, vector<treeNode*> & ans) {
	if (!root) return;
	recur(root->left, ans);
	ans.push_back(root);
	recur(root->right, ans);
}

treeNode* my_solution(treeNode* root) {
	if (!root || (root->left == NULL && root->right == NULL))
		return root;
	vector<treeNode* > ans;
	recur(root, ans);
	for (int i = 0; i < ans.size(); ++i) {
		if (i == 0) {
			ans[i]->left = NULL;
			ans[i]->right = ans[i + 1];
		}
		else if (i == ans.size() - 1) {
			ans[i]->left = ans[i - 1];
			ans[i]->right = NULL;
		}
		else {
			ans[i]->left = ans[i - 1];
			ans[i]->right = ans[i + 1];
		}
	}
	return ans[0];
}

//我自己试着想了一下递归的时候修改指针，并且已经很接近正确答案了，但是
//在保存前驱结点时没有想到取一个二级指针这么简单的办法
//采用二级指针的话，就好像得到了一个“全局”变量一样，不用考虑作用域的问题
void post_recur(treeNode* root, treeNode** last_node) {
	//if (!root) return;
	//注意这里，因为这里还没有发生对当前结点的操作，所以此处的前驱结点不更新
	treeNode* curr_node = root;
	if (root->left) post_recur(root->left, last_node);
	curr_node->left = *last_node;
	if (*last_node) (*last_node)->right = curr_node;
	*last_node = curr_node;
	if (root->right) post_recur(root->right, last_node);
}

treeNode* post(treeNode* root) {
	if (!post || (!root->left) && (!root->right)) return root;
	treeNode* last_node = NULL;
	treeNode** test = NULL;
	post_recur(root, &last_node);
	//post_recur(root,NULL);
	treeNode* p = root;
	while (p->left) {
		p = p->left;
	}
	return p;
}


//中序遍历非递归版，思路跟前一个很像
//我居然一时写不出中序遍历的非递归版。。。惭愧
treeNode* post_iterative(treeNode* root) {
	stack<treeNode*> stack_of_node;
	treeNode* p = root, * last_node = NULL;
	//stack_of_node.push(p);
	while (!stack_of_node.empty() || p) {
		while (p) {
			stack_of_node.push(p);
			p = p->left;
		}
		p = stack_of_node.top();
		p->left = last_node;
		if (last_node) last_node->right = p;
		stack_of_node.pop();
		last_node = p;
		p = p->right;
	}
	while (root->left) {
		root = root->left;
	}
	return root;
}

//答案提供了一种比较厉害的思路，彻底地利用了递归
//写这个方法时感觉状态不好，脑袋不太转
//需要好好体会一下这个方法
treeNode* real_recur(treeNode* root) {
	if (!root) return NULL;

	treeNode* last_node = NULL;
	if (root->left) {
		last_node = real_recur(root->left);
		while (last_node && last_node->right) {
			last_node = last_node->right;
		}
		root->left = last_node;
		last_node->right = root;
	}
	last_node = NULL;
	treeNode* next_node = NULL;
	if (root->right) {
		next_node = real_recur(root->right);
		while (next_node->left) {
			next_node = next_node->left;
		}
		root->right = next_node;
		next_node->left = root;
	}
	return root;
}
treeNode* real(treeNode* root) {
	root = real_recur(root);
	while (root->left) {
		root = root->left;
	}
	return root;
}

int main() {
	treeNode* root = new treeNode(10);
	root->left = new treeNode(8);
	root->right = new treeNode(12);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(9);
	root->right->left = new treeNode(11);
	root->right->right = new treeNode(13);
	//手动构建二叉搜索树
	treeNode* new_root = my_solution(root);
	while (new_root) {
		cout << new_root->val << " ";
		new_root = new_root->right;
	}
	cout << "\n";

	root = new treeNode(10);
	root->left = new treeNode(8);
	root->right = new treeNode(12);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(9);
	root->right->left = new treeNode(11);
	root->right->right = new treeNode(13);
	//手动构建二叉搜索树
	new_root = post(root);
	while (new_root) {
		cout << new_root->val << " ";
		new_root = new_root->right;
	}	
	cout << "\n";

	root = new treeNode(10);
	root->left = new treeNode(8);
	root->right = new treeNode(12);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(9);
	root->right->left = new treeNode(11);
	root->right->right = new treeNode(13);
	new_root = post_iterative(root);
	while (new_root) {
		cout << new_root->val << ' ';
		new_root = new_root->right;
	}
	cout << "\n";

	root = new treeNode(10);
	root->left = new treeNode(8);
	root->right = new treeNode(12);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(9);
	root->right->left = new treeNode(11);
	root->right->right = new treeNode(13);
	new_root = real(root);
	while (new_root) {
		cout << new_root->val << ' ';
		new_root = new_root->right;
	}
	cout << "\n";
	return 0;
}