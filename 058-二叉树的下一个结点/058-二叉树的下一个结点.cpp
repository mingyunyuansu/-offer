/*
#题意
题目描述

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。

注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
*/

//有点水的一题，似乎和算法没有太大关系
//没有父节点的话好像还真有点不会做，因为需要不定次的向上回溯，不用额外空间不太好做
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val):val(val), parent(NULL), left(NULL), right(NULL){}
};

TreeNode* find_the_next(TreeNode* root, TreeNode* given) {
    if (given->left) {
        return given->left;
    }
    else if (given->right){
        TreeNode* tmp = given->right;
        //右子树的最左叶子
        while (tmp->left) {
            tmp = tmp->left;
        }
        return tmp;
    }
    else if (given->parent->left == given) {
        return given->parent;
    }
    else {
        TreeNode* tmp = given->parent;
        while (tmp && tmp->parent && tmp->parent->left != tmp) {
            tmp = tmp->parent;
        }
        return tmp->parent;
    }
    return NULL;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->parent = root;
    root->right = new TreeNode(3);
    root->right->parent = root;
    root->left->left = new TreeNode(4);
    root->left->left->parent = root->left;
    root->left->right = new TreeNode(5);
    root->left->right->parent = root->left;
    root->left->right->right = new TreeNode(7);
    root->left->right->right->parent = root->left->right;
    root->right->right = new TreeNode(6);
    root->right->right->parent = root->right;    
    cout << find_the_next(root, root->right)->val << endl;
    if (find_the_next(root, root->right->right) == NULL) cout << "End of traversal.\n";
    return 0;
}