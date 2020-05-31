#include <stdio.h>
#include <stdlib.h>

#define SIZE 4096
/*
题目描述

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
*/
//s1用作输入栈，s2用作缓冲栈，输出当然也从缓冲栈s2走
//这里是优化解，即不论任何时候都入栈到s1，出栈时先检测s2是否为空，不为空则出一个，否则把s1
//全部倒到s2中，再出一个
//这样比较“惰性”，可以省去大量的从s1“倒入”s2的开销

typedef struct stack
{
    int *ss;
    int *sp;
} stack;

void Push(stack *s1, stack *s2, int element)
{
    *(s1->sp) = element;
    *(s1->sp)++;
}

int Pop(stack *s1, stack *s2)
{
    //判断输出栈为空
    if (s2->sp == s2->ss) {
        while (s1->ss < s1->sp) {
            //s1出栈
            (s1->sp) --;
            int t = *(s1->sp);
            //s2进栈
            *(s2->sp) = t;
            (s2->sp)++;
        }
    }
    (s2->sp)--;
    printf("Popped %d\n", *(s2->sp));
    return *(s2->sp);
}

stack *init_stack()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->ss = (int *)malloc(sizeof(int) * SIZE);
    s->sp = s->ss;
    if (!s || !(s->ss))
    {
        printf("Malloc error\n");
        return NULL;
    }
    return s;
}

int main()
{
    stack *s1 = init_stack();
    stack *s2 = init_stack();
    Push(s1, s2, 10);
    Push(s1, s2, 11);
    Pop(s1, s2);
    Push(s1, s2, 12);
    Pop(s1,s2);
    Pop(s1, s2);
    return 0;
}