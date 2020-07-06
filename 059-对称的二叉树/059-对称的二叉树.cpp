/*
#题意
题目描述

请实现一个函数，用来判断一颗二叉树是不是对称的。

注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的
*/

//分别打印左右子树比较费空间，可以用迭代分别前根左右，根右左地遍历左右子树
//一次比较每一步
#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(int v):val(v), left(NULL), right(NULL){}
};

bool is_mirrored(TreeNode* root) {
    if (!root || root->left->val != root->right->val) {
        return false;
    }
    stack<TreeNode*> left_s, right_s;
    TreeNode* left_root = root->left, *right_root = root->right;
    TreeNode* lp = left_root, *rp = right_root;
    while (lp && rp && lp->val == rp->val) {
        if (lp->left) {
            if (lp->right) left_s.push(lp->right);
            lp = lp->left;
        }
        else if (!left_s.empty()) {
            lp = left_s.top();
            left_s.pop();
        }
        else lp = NULL;
        if (rp->right) {
            if (rp->left) right_s.push(rp->left);
            rp = rp->right;
        }
        else if (!right_s.empty()) {
            rp = right_s.top();
            right_s.pop();
        }
        else rp = NULL;
    }
    return lp == NULL && rp == NULL && left_s.empty() && right_s.empty();
}

//当然啦递归也是可以的
bool recur(TreeNode* l, TreeNode* r) {
    if (!l && !r) {
        return true;
    }
    else if (!l || !r) {
        return false;
    }
    else if (l->val != r->val) {
        return false;
    }
    return recur(l->left, r->right) && recur(l->right, r->left);
}

bool is_mirrored_recur(TreeNode* root) {
    if (root->left == NULL && root->right != NULL || root->left && !root->right) {
        return false;
    }
    return recur(root->left, root->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    if (is_mirrored(root)) cout << "YES from stack iteration\n";
    if (is_mirrored_recur(root)) cout << "YES from recursion\n";
    root->right->right->right = new TreeNode(5);
    if (is_mirrored(root)) cout << "YES from stack iteration after\n";
    if (is_mirrored_recur(root)) cout << "YES from recursion after\n";
    return 0;
}