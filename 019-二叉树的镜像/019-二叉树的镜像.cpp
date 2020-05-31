/*
题目描述

操作给定的二叉树，将其变换为源二叉树的镜像。
*/

//不好上图，但是题意蛮好理解的，就是左右子树全部互换
//测试的二叉树用的https://github.com/mingyunyuansu/CodingInterviews/tree/master/019-%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%95%9C%E5%83%8F
//的图

#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

class Node {
public:
	int val;
	Node* left = NULL;
	Node* right = NULL;

	Node(int value) {
		val = value;
	}
};

Node* construct_tree() {
	Node* root = new Node(8);
	root->left = new Node(6);
	root->right = new Node(10);
	root->left->left = new Node(5);
	root->left->right = new Node(7);
	root->right->left = new Node(9);
	root->right->right = new Node(11);
	return root;
}

void pre_print(Node* root) {
	if (root) {
		cout << root->val << " ";
		pre_print(root->left);
		pre_print(root->right);
	}
}

//--------------------------------------------------------------------
//以上为公共部分

void pre_recur(Node* root) {
	if (!root->left && !root->right) return;
	swap(root->left, root->right);
	pre_recur(root->left);
	pre_recur(root->right);
}

void pre_iterative(Node* root) {
	stack<Node*> stk;
	Node* p = root;
	while (p || stk.size()) {
		while (p) {
			swap(p->left, p->right);
			stk.push(p);
			p = p->left;
		}
		if (!stk.empty()) {
			p = stk.top()->right;
			stk.pop();
		}
	}
}

void pre_bfs(Node* root) {
	stack<Node*> stk;
	stk.push(root);
	Node* p = root;
	while (!stk.empty()) {
		p = stk.top();
		stk.pop();
		if (p->left || p->right) {
			swap(p->left, p->right);
		}
		if (p->left) {
			stk.push(p->left);
		}
		if (p->right) {
			stk.push(p->right);
		}
	}
}

void in_iterative(Node* root) {
	stack<Node*> stk;
	Node* p = root;
	while (p || !stk.empty()) {
		while (p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		stk.pop();
		if (p->left || p->right) swap(p->left, p->right);
		p = p->left;//交换后要要访问原来的右结点就需要左转
	}
}

void post_iterative(Node* root) {
	//注意后序遍历时不需要考虑交换之后对原本“标准的”遍历代码的影响。
	//因为当一个节点交换左右子树的时候，其左右子树内部已经完成了
	//所有需要的工作。
	stack<Node*> stk;
	Node* p = root, *last_visit = root;
	while (p || stk.empty() == false) {
		while (p) {
			stk.push(p);
			p = p->left;
		}
		p = stk.top();
		if (p->right == NULL || last_visit == p->right) {
			//cout << p->val << " ";
			if (p->left || p->right) {
				swap(p->left, p->right);
			}
			last_visit = p;
			stk.pop();
			p = NULL;
			
		}
		else {
			p = p->right;
		}
	}
}

//顺便复习一波后序遍历。
//本科学数据结构的时候天天打刀塔，导致数据结构全靠算法课时一起补，当时难以理解后序遍历，留下了阴影（考试前两天才开始学那要怎么学嘛）
//实际上后序遍历也是可以用递归解决了，而且真就跟前，中序长一样，没什么可怕的
//又完成了一波来自过去的试炼
void post_order(Node* root) {
	if (!root) return;
	post_order(root->left);
	post_order(root->right);
	cout << root->val << " ";
}


void bfs(Node* root) {
	//突然想起来这种写法，测试用的，与题目无关，可无视
	stack<Node*> stk;
	stk.push(root);
	Node* p = root;
	while (!stk.empty()) {
		p = stk.top();
		stk.pop();
		cout << p->val << " ";
		if (p->left) {
			stk.push(p->left);
		}
		if (p->right) {
			stk.push(p->right);
		}
	}
}



int main() {
	Node* root = construct_tree();
	pre_print(root);
	cout << endl;
	pre_recur(root);
	pre_print(root);
	cout << "\n" << endl;

	root = construct_tree();
	pre_print(root);
	cout << endl;
	pre_iterative(root);
	pre_print(root);
	cout << "\n" << endl;

	root = construct_tree();
	pre_print(root);
	cout << endl;
	pre_bfs(root);
	pre_print(root);
	cout << "\n" << endl;
	/*
	root = construct_tree();
	pre_print(root);
	cout << endl;
	bfs(root);
	cout << "\n" << endl;
	*/
	root = construct_tree();
	pre_print(root);
	cout << endl;
	in_iterative(root);
	pre_print(root);
	cout << "\n" << endl;

	root = construct_tree();
	pre_print(root);
	cout << endl;
	post_iterative(root);
	pre_print(root);
	cout << "\n" << endl;
	return 0;
}