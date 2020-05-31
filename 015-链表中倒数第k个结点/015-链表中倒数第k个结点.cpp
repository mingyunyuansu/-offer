/*
题意
题目描述

输入一个链表，输出该链表中倒数第k个结点。

分析
这道题我想大多数人都会有思路，因为我们已经见的很多了 最暴力的方式,两趟遍历，第一趟先求出list的长度length，然后进而length - k得到倒数第k个节点的位置 当然我们大多数都会知道另外一个更加高效的方法，双指针法 其实就是第一个指针right先向前走K步，然后left和right一起走，此时两个指针差别K步，那么当right走到链表尾部的时候，left指向的就是倒数第K个节点

期间要注意的问题有

链表可能为NULL

链表长度可能没有K个
*/
//确实是很直接的一题，我直接上双指针吧

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
	int val;
	Node* next = NULL;
};

Node* construct_list(int N) {
	if (N <= 0) {
		cout << "Non-positive N, exiting\n";
		exit(-1);
	}
	Node* head = new Node();
	srand(time(NULL));
	head->val = rand() % 20;
	Node* p = head, *q = head;
	for (int i = 1; i < N; ++i) {
		p->next = new Node();
		p = p->next;
		p->val = rand() % 20;
	}
	return head;
}

void print_list(Node* head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << "\n";
}

void find_k(Node* head, int K) {
	Node* fast = head, * slow = head;
	while (K && fast) {
		fast = fast->next;
		K--;
	}
	if (!fast && K) {
		cout << "Given K exceeds the length of linked list\n";
		return;
	}
	while (fast) {
		fast = fast->next;
		slow = slow->next;
	}
	cout << slow->val;
}

int main() {
	Node* head = construct_list(0);
	int K = 7;
	print_list(head);
	find_k(head, K);
	return 0;
}