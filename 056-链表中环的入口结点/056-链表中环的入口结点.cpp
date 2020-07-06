/*
#题目描述
一个链表中包含环，请找出该链表的环的入口结点。
*/
//经典老番，环形链表求入口，双指针

//不过证明需要费点口舌。https://blog.csdn.net/sinat_35261315/article/details/79205157
//说得很好
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct Node {
public:
    int val;
    Node* next;
    Node(int v): val(v), next(NULL){}
};

int main() {
    int L = 4;
    vector<int> v(L);
    Node* head = NULL, *p = NULL;
    iota(v.begin(), v.end(), 0);
    for (int i = 0; i < L; ++i) {
        if (!head) {
            head = new Node(v[i]);
            p = head;
        }
        else {
            p->next = new Node(v[i]);
            p = p->next;
        }
    }
    Node* entrance = p;
    cout << entrance->val << "\n";
    for (int i = 0; i < L - 1; ++i) {
        if (!head) {
            head = new Node(v[i]);
            p = head;
        }
        else {
            p->next = new Node(v[i]);
            p = p->next;
        }
    }
    p->next = entrance;
    //构建环形链表，入口为3
    Node* slow = head, *fast = head;
    if (head == NULL || head->next == NULL) return 0;
    do {
        slow = slow->next;
        fast = fast->next->next;
    } while (slow && fast && fast->next && slow != fast);
    if (!(slow && fast && fast->next)) return 0;//无环
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    cout << slow->val << endl;
    return 0;
}