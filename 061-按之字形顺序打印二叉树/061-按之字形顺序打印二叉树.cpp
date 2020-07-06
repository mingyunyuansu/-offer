/*
题意
题目描述

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
*/

//是因为修行的成果开始显现了吗。。。最后几题好水
//跟上一题换汤不换药，答案上用了reverse，不用的话专门做一个特例的反向循环
//也没问题。但是没什么意思，就用reverse

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left, * right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

void zip_zap_print_tree(TreeNode* root) {
    if (!root) return;

    vector<TreeNode* > vec = { root };
    int curr = 0;
    bool rev = true;
    while (curr < vec.size()) {
        int end = vec.size(), start = curr;
        while (curr < end) {
            if (vec[curr]->left) vec.push_back(vec[curr]->left);
            if (vec[curr]->right) vec.push_back(vec[curr]->right);
            curr++;
        }
        if (rev) { reverse(vec.begin() + start, vec.begin() + end); }
        while (start < end) {
            cout << vec[start++]->val << " ";
        }
        cout << "\n";
        if (rev) { reverse(vec.begin() + start, vec.begin() + end); rev = false; }//还原
        else rev = true;
    }
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    zip_zap_print_tree(root);
    return 0;
}

