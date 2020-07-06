/*
题目描述
从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
*/
//就是层次遍历
#include <vector>
#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

void print_lines(TreeNode* root) {
    //双指针法
    vector<TreeNode*> v;
    if (!root) return;
    v.push_back(root);
    int curr = 0;
    while(curr < v.size()) {
        int end = v.size();
        while (curr < end) {
            cout << v[curr]->val;
            if (v[curr]->left) v.push_back(v[curr]->left);
            if (v[curr]->right) v.push_back(v[curr]->right);
            curr++;
        }
        cout << endl;
    }
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    print_lines(root);
    return 0;
}