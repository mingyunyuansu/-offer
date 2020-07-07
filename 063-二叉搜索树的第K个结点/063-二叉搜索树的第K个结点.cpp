/*
#2 题意
题目描述

给定一颗二叉搜索树，请找出其中的第k大的结点。
*/

//题目真是越来越水了，不知道出了什么问题
//原本以为还有什么幺蛾子，没想到确实是靠（反向）中序遍历

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(int v): val(v), left(NULL), right(NULL) {

    }
};

TreeNode* the_Kth_number(TreeNode * root, int K, int &n) {
    //因为直接返回可能会和目标冲突，所以返回指针
    if (!root) return NULL;
    TreeNode* res = NULL;
    if (res = the_Kth_number(root->right, K, n)) return res;
    ++n;
    if (n == K) return root;
    if (res = the_Kth_number(root->left, K, n)) return res;
    return res;
}

int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);

    int n = 0;
    cout << the_Kth_number(root, 3, n)->val << endl;
    return 0;
}