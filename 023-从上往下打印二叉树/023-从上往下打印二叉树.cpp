/*
题意
题目描述

从上往下打印出二叉树的每个节点，同层节点从左至右打印。
*/
//我感觉自己并没有学过层次遍历。
//再仔细想想，厦大应该不可能不教吧，大概又是数据结构课我自己忙着打dota所以没有学的那部分。
//看来这又是来自过去的试炼。
//层次遍历或者其他遍历都可以参考https://blog.csdn.net/gatieme/article/details/51163010#t10
//github上的题解也写得很棒了。
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
using namespace std;

class treeNode {
public:
	int val;
	treeNode* left;
	treeNode* right;
	treeNode(int v) {
		this->val = v;
		this->left = NULL;
		this->right = NULL;
	}
};
//法一，先搞定打印特定一层的写法，然后循环调用
int print_certain_level(treeNode* node, int level, int current_level) {
	if (!node) return 0;
	else if (level == current_level) {
		cout << node->val << " ";
		return 1;
	}
	else {
		return print_certain_level(node->left, level, current_level + 1) + print_certain_level(node->right, level, current_level + 1);
	}
}

void iterative_recur(treeNode* root) {
	for (int i = 1; ; ++i) {
		if (print_certain_level(root, i, 1) == 0) break;
	}
}
//法二，双队列，循环工作。这个比较巧妙，不过代码很容易懂
void deque_iterative(treeNode* root) {
	deque<treeNode*> queue1, queue2;
	queue1.push_back(root);
	while (!queue1.empty()) {
		while (!queue1.empty()) {
			treeNode* tmp = queue1.front();
			queue1.pop_front();
			cout << tmp->val << " ";
			if (tmp->left) {
				queue2.push_back(tmp->left);
			}
			if (tmp->right) {
				queue2.push_back(tmp->right);
			}
		}
		queue1.swap(queue2);//这个动作时间复杂度是O(1)，因为只交换指针
	}
}
//法三，思路与二差不多，但是将两个队列退化到只用一个vector，以及两个指针标定每层的起始位置
//但是这里我又踩坑了。因为我又用了迭代器。牢记不要在迭代的过程中修改数据源，不行就用下标访问。
//难怪答案这里用的下标。我不想改了，加了一句v.reserve(100)暂时解决。
//但是这也是个值得探究的问题，查了几篇博客，都写得不错：
//https://blog.csdn.net/wangshubo1989/article/details/50334297
//https://blog.csdn.net/ZX714311728/article/details/69944546
//https://blog.csdn.net/hl_zzl/article/details/84798804
//总之vector的内存大小是自动分配的，分配的办法是当v.capacity() == v.size()时，再有新元素插入时，
//开辟一块新的内存空间，原空间的内容复制过来，原空间销毁。也因此会导致原先的迭代器全部失效，所以才会报错。
//顺便一提，微软和GCC的分配实现不同，VS:1, 2, 3, 4, 6, 9, ... 即1.5倍，并截断取整。
//gcc则是按完全的两倍来进行，即1, 2, 4, 8, ...。
//也因为这种原因，追求性能的时候，可以提前用reserve申请一大段空间，省去不断重新分配的时间。
void vector_pointers(treeNode* root) {
	vector<treeNode*> v;
	v.reserve(100);
	v.push_back(root);
	vector<treeNode*>::iterator cur = v.begin(), end = v.begin() + 1;
	while (cur < end) {
		cout << (*cur)->val << " ";
		//cout << "\n" << v.capacity() << "\n";
		if ((*cur)->left) {
			v.push_back((*cur)->left);
			//cout << "\n" << v.capacity() << "\n";
		}
		if ((*cur)->right) {
			v.push_back((*cur)->right);
			//cout << "\n" << v.capacity() << "\n";
		}
		++cur;
		end = v.end();
	}
}

//法4，用两个变量来表示当前层和下一层的结点数，并不断迭代
//其实思路和法2和3依然差不多
void queue_child_parent_size(treeNode* root) {
	int parent_size = 1, child_size = 0;
	treeNode* tmp = NULL;
	queue<treeNode* > q;
	q.push(root);
	while (!q.empty()) {
		tmp = q.front();
		q.pop();
		cout << tmp->val << " ";
		if (tmp->left) {
			q.push(tmp->left);
			child_size++;
		}
		if (tmp->right) {
			q.push(tmp->right);
			child_size++;
		}
		parent_size--;
		if (parent_size == 0) {
			parent_size = child_size;
			child_size = 0;
		}
	}
}

//答案中还有一个法5，看了一下，真的是大同小异了，但是还是写一下吧
void with_NULL_termination(treeNode* root) {
	queue<treeNode*> q;
	q.push(root);
	q.push(NULL);
	while (!q.empty()) {
		treeNode* tmp = q.front();
		q.pop();
		if (tmp) {
			cout << tmp->val << " ";
			if (tmp->left) {
				q.push(tmp->left);
			}
			if (tmp->right) {
				q.push(tmp->right);
			}
		}
		else if (!q.empty()) {
			q.push(NULL);//这里注意，实际上碰到NULL的时候，
			//意味着上一层的子节点全部添加完毕了。所以碰到（上一层的）终止NULL时，（当前层）也添加终止NULL。
			//添加的NULL前面就是所有这层的元素了。
		}
	}
}

int main() {
	treeNode* root = new treeNode(1);
	root->left = new treeNode(2);
	root->right = new treeNode(3);
	root->left->left = new treeNode(4);
	root->left->right = new treeNode(5);
	root->right->left = new treeNode(6);
	root->right->right = new treeNode(7);
	iterative_recur(root);
	cout << endl;
	deque_iterative(root);
	cout << endl;
	vector_pointers(root);
	cout << endl;
	queue_child_parent_size(root);
	cout << endl;
	with_NULL_termination(root);
	return 0;
}