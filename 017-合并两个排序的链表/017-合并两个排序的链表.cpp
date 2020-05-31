/*
题意
题目描述

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

样例输入

1 3 5 7 9 2 4

样例输出

1 2 3 4 5 7 9
*/

//我记得以前写这题也是被绕晕了，最后好像还是没写出来
//所以你也是来自过去的试炼
//不过就题解上的说法，他们是直接构造了一个新链表出来。。。那不就太简单了

#include <iostream>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <uinistd.h>
#endif

using namespace std;

struct node {
	int val = 0;
	node* next = NULL;
};

node *con_monotonously_increasing_list(int N) {
	if (N <= 0) { cout << "Invalid given N, exiting\n"; exit(-1); }
	srand(time(NULL));
	node* head = new node();
	head->val = rand() % 8;
	int last_num = head->val;
	node* p = head;
	for (int i = 1; i < N; ++i) {
		p->next = new node();
		p = p->next;
		p->val = last_num + rand() % 8;
		last_num = p->val;
	}
	return head;
}

void print_list(node* head) {
	while (head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << "\n";
}
//不过仔细想一想，重新构造一个链表，但是其实没有额外使用空间，因为是直接拿原结点插入的，这么来看空间和时间效率都是最佳了。
//非要追求合并到一根原来的链表反而比较反人类
node* simple(node* head1, node* head2) {
	node* p1 = head1, * p2 = head2;
	if (!p1 || !p2) { cout << "Empty linked list given\n"; exit(-1); }
	node* head = p1->val <= p2->val ? p1 : p2;
	if (p1->val <= p2->val) p1 = p1->next;
	else p2 = p2->next;
	node* p = head;
	while (p1 && p2) {
		p->next = p1->val <= p2->val ? p1 : p2;
		if (p1->val <= p2->val) p1 = p1->next;
		else p2 = p2->next;
		p = p->next;
	}
	if (p1) p->next = p1;
	else if (p2) p->next = p2;
	else p->next = NULL;
	return head;
}

node* recur_simple(node* head1, node* head2) {
	//上面方法的递归版
	if (!head1) {
		return head2;
	}
	else if (!head2) {
		return head1;
	}
	node* head = NULL;
	if (head1->val <= head2->val) {
		head = head1;
		head->next = recur_simple(head1->next, head2);
	}
	else {
		head = head2;
		head->next = recur_simple(head1, head2->next);
	}
	return head;
}

int main (){
	node* head1 = con_monotonously_increasing_list(6);
	Sleep(2000);
	node* head2 = con_monotonously_increasing_list(5);
	print_list(head1);
	print_list(head2);
	print_list(simple(head1, head2));

	Sleep(2000);
	head1 = con_monotonously_increasing_list(6);
	Sleep(2000);
	head2 = con_monotonously_increasing_list(5);
	print_list(head1);
	print_list(head2);
	print_list(recur_simple(head1, head2));
	return 0;
}