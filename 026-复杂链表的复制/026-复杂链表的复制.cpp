/*
题意
题目描述

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点）。

要求你编写函数复制这个复杂链表
*/
//图例见https://github.com/mingyunyuansu/CodingInterviews/tree/master/026-%E5%A4%8D%E6%9D%82%E9%93%BE%E8%A1%A8%E7%9A%84%E5%A4%8D%E5%88%B6
#include <iostream>
#include <map>
using namespace std;

struct Node {
	char val;
	Node* next;
	Node* other;
	Node(int v) : val(v), next(NULL), other(NULL){}
};

void print_list(Node* head) {
	//打印骨架，同时把每个other结点用括号跟上
	while (head) {
		cout << head->val;
		if (head->other) {
			cout << "(" << head->other->val << ") ";
		}
		else {
			cout << " ";
		}
		head = head->next;
	}
	cout << endl;
}

//先是暴力方法，自己很简单就能写出来。
//先搭起骨架，然后通过两边的指针一起移动来定位每一个other所在的位置。
//查找位置，则是从head开始遍历，直到两个地址相等。
//因为构建other时每个都需要遍历所有时间复杂度O(N^2+N) = O(N^2)

Node* brutal(Node* head) {
	if (!head) return NULL;
	//先建好所有next
	Node* original_p = head->next;
	Node* new_head = new Node(head->val);
	Node* new_p = new_head;
	while (original_p) {
		new_p->next = new Node(original_p->val);
		new_p = new_p->next;
		original_p = original_p->next;
	}
	Node* p = head;
	new_p = new_head;
	//顺着建other
	while (p && new_p) {
		//find each *other
		if (p->other) {
			Node* q = head, *new_q = new_head;
			while (q != p->other) {
				q = q->next;
				new_q = new_q->next;
			}
			new_p->other = new_q;
		}
		p = p->next;
		new_p = new_p->next;
	}
	return new_head;
}

//然后是hash表的办法，其实也蛮简单的，与暴力法的区别就是创建other时直接定位
//因此时间复杂度是O(2N) = O(N)，不过有O(N)的空间复杂度。
Node* with_hashtable(Node* head) {
	if (!head) return NULL;
	map<Node*, Node*> m;
	Node* p = head->next;
	Node* new_head = new Node(head->val);
	m[head] = new_head;
	Node* q = new_head;

	while (p) {
		q->next = new Node(p->val);
		m[p] = q->next;
		q = q->next;
		p = p->next;
	}

	//构建other
	Node* k = head, * new_k = new_head;
	while (k && new_k) {
		new_k->other = m[k->other];
		k = k->next;
		new_k = new_k->next;
	}
	return new_head;
}

//还有第三种办法就比较厉害了，是答案介绍的。
//时间复杂度O(N)且不用额外空间。
//首先将每个新节点一次插入原对应结点后面，如
//A->A'->B->B'->C->C'
//这样遍历原链表时找到的other结点，其下一位即是新节点的other结点。
//拆分起来也不难，因为奇数位一定是原链表，偶数位一定是新链表
Node* better_one(Node* head) {
	if (!head) return NULL;
	Node* p = head;
	//合并
	while (p) {
		Node* tmp = p->next;
		p->next = new Node(p->val);
		p->next->next = tmp;
		p = p->next->next;
	}
	p = head;
	Node* new_head = NULL;
	Node* new_p = new_head;

	while (p) {
		if (p->other) p->next->other = p->other->next;
		Node* tmp = p->next->next;
		if (!new_head) {
			new_head = p->next;
			new_head->next = new_head->next->next;
			new_p = new_head->next;
		}
		else if (new_p->next) {
			new_p->next = new_p->next->next;
			new_p = new_p->next;
		}
		p->next = tmp;
		p = p->next;
	}
	return new_head;
}



int main () {
	Node* head = new Node('A');
	head->next = new Node('B');
	head->next->next = new Node('C');
	head->next->next->next = new Node('D');
	head->next->next->next->next = new Node('E');
	head->other = head->next->next;//A->C
	head->next->other = head->next->next->next->next;//B->E
	head->next->next->next->other = head->next;//D->B
	print_list(head);
	print_list(brutal(head));
	print_list(with_hashtable(head));
	print_list(better_one(head));
	return 0;
}