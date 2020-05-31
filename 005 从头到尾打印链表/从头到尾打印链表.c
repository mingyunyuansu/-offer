#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
题目描述

输入一个链表，从尾到头打印链表每个节点的值。

输入描述:

输入为链表的表头

输出描述:

输出为需要打印的“新链表”的表头
*/
struct Node
{
    int val;
    struct Node *next;
};

struct Node *constructor(int num)
{
    srand(time(NULL));
    if (num <= 0)
        return NULL;

    int i = 0;
    struct Node *head = NULL;
    struct Node *p = head;
    for (i = 0; i < num; i++)
    {
        if (head == NULL)
        {
            int t = rand() % 100;
            head = (struct Node *)malloc(sizeof(struct Node));
            head->val = t;
            head->next = NULL;
            p = head;
        }
        else
        {
            struct Node *new_p = (struct Node *)malloc(sizeof(struct Node));
            new_p->val = rand() % 100;
            new_p->next = NULL;
            p->next = new_p;
            p = new_p;
        }
    }
    return head;
}

void view(struct Node *list)
{
    while (list)
    {
        if (list->next)
            printf(" %d ->", list->val);
        else
            printf(" %d\n", list->val);
        list = list->next;
    }
}

void using_stack(struct Node *list)
{
    // Build a stack of pointers to the struct nodes
    struct Node **ss = (struct Node **)malloc(sizeof(struct Node *) * 100);
    struct Node **sp = ss;
    struct Node *p = list;
    while (p)
    {
        *sp = p;
        sp++;
        p = p->next;
    }
    while (sp > ss) // Careful, no equal sign
    {
        sp--;
        printf("%d ", (*sp)->val);
    }
    printf("\n");
    free(ss);
}

void recursion(struct Node *list)
{

    if (list)
    {
        recursion(list->next);
        printf("%d ", list->val);
    }
}

int main()
{
    struct Node *head = constructor(5);

    view(head);
    using_stack(head);

    recursion(head);
    return 0;
}