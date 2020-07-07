/*
题目描述
请实现两个函数，分别用来序列化和反序列化二叉树

二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。

二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。

例如，我们可以把一个只有根节点为1的二叉树序列化为"1"，然后通过自己的函数来解析回这个二叉树
*/
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left, * right;
    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

char* recur_serialise(TreeNode* root, char* s, int& pos) {
    int v;
    if (!root) {
        s[pos++] = '#';
        return NULL;
    }
    string tmp = to_string(root->val);
    tmp += "!";
    for (char c: tmp) {
        s[pos++] = c;
    }
    recur_serialise(root->left, s, pos);
    recur_serialise(root->right, s, pos);
    return s;
}

char* serialise(TreeNode* root) {
    char* s = (char*)malloc(sizeof(char) * 5000);
    memset(s, 0, 5000*sizeof(char));
    int pos = 0;
    recur_serialise(root, s, pos);
    cout << "pos" << pos << endl;
    return s;
}

TreeNode* deserialise_recur(char* s, int& pos) {
    if (s[pos] != '\0' && s[pos] == '#') {
        pos++;
        return NULL;
    }
    int i = pos;
    while (s[i] != '!') {
        ++i;
    }
    string tmp(s+pos, s+i);
    pos = i + 1;
    i = stoi(tmp);
    TreeNode* root = new TreeNode(i);
    root->left = deserialise_recur(s, pos);
    root->right = deserialise_recur(s, pos);
    return root;
}

TreeNode* deserialise(char* s) {
    int n = 0;
    return deserialise_recur(s, n);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    char *s = serialise(root);
    int len = strlen(s);
    string ns(s, s + len);
    cout << ns << endl;

    TreeNode * proot = deserialise(s);
    cout << proot->left->left->val << endl;
    return 0;
}