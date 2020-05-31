#include <stdio.h>
#include <stdlib.h>
#define NUM 8
/*
题目描述

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。

假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

输入

前序遍历序列{1,2,4,7,3,5,6,8}

中序遍历序列{4,7,2,1,5,3,8,6}

则重建二叉树并返回。
*/
//关键在于想到，前序遍历数组最先的那个数是根，只要在中序数组中找到它，中序数组左边的部分就是左子树，右边就是右子树，并且这个过程可以递归进行
typedef struct TreeNode
{
    struct TreeNode *left;
    struct TreeNode *right;
    int val;
} TreeNode;

TreeNode *reconst(int pre[], int in[], int l, int r)
{
    if (l > r)
        return NULL;
    static int root_index = 0; //因为整个递归是把所有左子树建好才开始右子树
    //所以这里取个巧，递归函数的处理顺序就是pre数组的“根”的顺序
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    int root_val = pre[root_index++];
    int i = l;
    while (i <= r)
    {
        if (in[i] == root_val)
        {
            break;
        }
        i++;
    }
    root->left = reconst(pre, in, l, i - 1);
    root->right = reconst(pre, in, i + 1, r);
    root->val = root_val;
    return root;
}

void print_inorder(TreeNode *root)
{
    if (!root)
        return;
    print_inorder(root->left);
    printf("%d ", root->val);
    print_inorder(root->right);
}

int main()
{
    int pre[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int in[] = {4, 7, 2, 1, 5, 3, 8, 6};
    TreeNode *root = reconst(pre, in, 0, NUM - 1);
    print_inorder(root);
    return 0;
}