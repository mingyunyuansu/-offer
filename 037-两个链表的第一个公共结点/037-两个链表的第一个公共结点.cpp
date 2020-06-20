/*
#题意
题目描述

输入两个链表，找出它们的第一个公共结点。
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <unordered_map>
#include <stack>
using namespace std;

struct node {
public:
	int val;
	node* next;
	node(int val) : val(val), next(NULL) {}
};

class llist {
public:
	node* head = NULL;
	llist(int n) {
		srand(time(NULL));
		int i = 0;
		node* p = head;
		while (i < n) {
			if (head == NULL) {
				head = new node(rand() % 10);
				p = head;
			}
			else {
				p->next = new node(rand() % 10);
				p = p->next;
			}
			++i;
		}
	}
};

//这种题型还不是很熟，我直觉想到的就是用map
//unordered_map的搜索插入删除时间复杂度均为O(1)
node* with_map(node* head1, node* head2) {
	unordered_map<node*, bool> m;
	node* p1 = head1, * p2 = head2;
	while (p1) {
		m.insert(make_pair(p1, true));
		p1 = p1->next;
	}
	while (p2 && m.find(p2) == m.end()) {
		p2 = p2->next;
	}
	if (m.find(p2) != m.end()) return p2;
	else return NULL;
}

//但是其实也可以用栈
node* with_stack(node* head1, node* head2) {
	stack<node*> s1, s2;
	while (head1) {
		s1.push(head1);
		head1 = head1->next;
	}
	while (head2) {
		s2.push(head2);
		head2 = head2->next;
	}
	node* ans = NULL;
	while (s1.top() == s2.top()) {
		ans = s1.top();
		s1.pop();
		s2.pop();
	}
	return ans;
}

//还有可以先对齐
node* align(node* head1, node* head2) {
	node* p1 = head1, *p2 = head2;
	while (p1 && p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	int cnt1 = 0, cnt2 = 0;
	while (p1) {
		p1 = p1->next;
		cnt1++;
	}
	while (p2) {
		p2 = p2->next;
		cnt2++;
	}
	p1 = head1;
	p2 = head2;
	while (cnt1) {
		p1 = p1->next;
		cnt1--;
	}
	while (cnt2) {
		p2 = p2->next;
		cnt2--;
	}
	while (p1 && p2 && p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p1 && p2 && p1 == p2) return p1;
}

//还有一种比较神奇的方法，
//解释看https://github.com/mingyunyuansu/CodingInterviews/tree/master/037-%E4%B8%A4%E4%B8%AA%E9%93%BE%E8%A1%A8%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AA%E5%85%AC%E5%85%B1%E7%BB%93%E7%82%B9
//我看了一遍没太理清楚，只能感受到这个和确定环的方法差不多
//不过我觉得有前面三种方式面试足够了
node* a_strange_way(node* leftHead, node *rightHead) {
	node* left = leftHead;
	node* right = rightHead;

	while (left != right)
	{

		left = (left == NULL ? rightHead : left->next);
		right = (right == NULL ? leftHead : right->next);
	}
	return left;
}

void print_list(node* head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

int main() {
	llist* l = new llist(5);
	node* head = l->head;
	
	//cout << head->val << endl;

	node* test_head = new node(3);
	test_head->next = new node(2);
	test_head->next->next = new node(1);
	test_head->next->next->next = head->next;
	print_list(test_head);
	print_list(head);
	cout << with_map(test_head, head)->val << endl;
	cout << with_stack(test_head, head)->val << endl;
	cout << align(test_head, head)->val << endl;
	cout << a_strange_way(test_head, head)->val << endl;
	return 0;
}