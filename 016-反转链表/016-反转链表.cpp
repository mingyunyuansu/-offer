/*题意
题目描述

输入一个链表，反转链表后，输出链表的所有元素。*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
	int val = 0;
	Node* next = NULL;
};

Node* con_list(int N) {
	if (N <= 0) { cout << "Invalid N, exiting.\n"; exit(-1); }
	Node* head = new Node();
	srand(time(NULL));
	head->val = rand() % 20;
	Node* p = head;
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
	cout << '\n';
}

Node* three_pointers(Node* head) {
	//记住翻转链表需要三个指针
	Node* prev, * cur, * after;
	if (head == NULL || head->next == NULL) return head;
	prev = NULL;
	cur = head;
	while (cur) {
		after = cur-> next;
		cur->next = prev;
		prev = cur;
		cur = after;
	}
	return prev;
}

Node* insert_to_head(Node* head) {
	//相当于创建新链表，每读一个节点就插入到新链表的head
	Node* new_head = NULL, *tmp = NULL;
	while (head) {
		tmp = head->next;
		head->next = new_head;
		new_head = head;
		head = tmp;
	}
	return new_head;
}

int main(){
	Node* head = con_list(5);
	print_list(head);
	print_list(three_pointers(head));
	head = con_list(5);
	print_list(head);
	print_list(insert_to_head(head));
	return 0;
}