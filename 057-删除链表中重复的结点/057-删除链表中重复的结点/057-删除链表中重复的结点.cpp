/*
#题意
题目描述

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。

例如，链表1->2->3->3->4->4->5

处理后为 1->2->5
*/
//显然一个map就能解决，不过既然给定了有序，那还能做点妖，采用逻辑判断
#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v):val(v), next(NULL){}
};
int main() {
    int arr[] = {1,1,2,2,2,3,4,4,5, 5};
    Node* head = NULL;
    Node* p = NULL;
    for (int x: arr) {
        if (!head) {
            head = new Node(x);
            p = head;
        }
        else {
            p->next = new Node(x);
            p = p->next;
        }
    }
    //以上构建链表
    //开始删除
    p = head;
    Node* pre = NULL;
    int tmp = arr[0];
    while (p && p->next) {
        if (p->next->val == p->val) {
            Node* t = p;
            while (t->next && t->val == t->next->val) {
                t = t->next;
            }
            t = t->next;
            if (!pre) {
                head = t;
                p = head;
            }
            else {
                pre->next = t;
                p = t;
            }
        }
        else {
            pre = p;
            p = p->next;
        }
    }
    p = head;
    while (p) {
        cout << p->val << "\n";
        p = p->next;
    }
    return 0;
}