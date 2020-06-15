/*
#题意
题目描述

在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符的位置。若为空串，返回-1。位置索引从0开始
*/
//不知道是不是字符串的题比较直观，感觉最近的题都比较简单
#include <iostream>
#include <vector>
#include <map>
using namespace std;

//暴力法就不写了，因为这题直接能想到用map来解，遍历一遍统计每个字母出现的次数。
//但是做这题时顺便补了点知识，C++的std::map是平衡二叉树，查找时间是logN，并且元素以key来进行排序，默认升序。
//unorered_map是哈希表，里面的项没有任何特定顺序，只是为了最快而把元素放到一个计算出的bucket中。时间复杂度是O(1)，最差可以到O(N)但是极少。
//所以想把map和插入顺序关联起来，还需要一个数组记录插入元素的顺序。
int with_map(string& s) {
    if (s.empty()) return -1;
    map<char, int> my_map;
    vector<char> my_order;
    for (char c : s) {
        if (my_map.find(c) == my_map.end()) {
            my_order.push_back(c);
            my_map.insert(make_pair(c, 0));
        }
        my_map[c]++;
    }
    for (auto x : my_order) {
        if (my_map[x] == 1) return s.find(x);
    }
    return -1;
}
//答案提示用bitmap，其实这个跟一开始的设想差不多。
int with_bitmap(string& s) {
    if (s.empty()) return -1;
    int upper[26] = { 0 }, lower[26] = { 0 };
    //memset(upper, -2, sizeof(upper));
    //memset(lower, -2, sizeof(lower));
    for (int i = 0; s[i] != '\0'; ++i) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') {
            if (lower[c - 'a'] == 0) {
                lower[c - 'a'] = i + 1;//注意这里+1是为了区别目标出现在第一位（i=0）和这一位原本就是0的歧义
            }
            else {
                lower[c - 'a'] = -1;
            }
        }
        else {
            if (upper[c - 'A'] == 0) {
                upper[c - 'A'] = i + 1;
            }
            else {
                upper[c - 'A'] = -1;
            }
        }
    }

    int ans = 10001;
    for (auto x : lower) {
        ans = (ans > x && x != -1 && x) ? x : ans;
    }
    for (auto x : upper) {
        ans = (ans > x && x != -1 && x) ? x : ans;
    }
    return ans - 1;
}

int main() {
    string s = "google";

    cout << with_map(s) << endl;
    cout << with_bitmap(s) << endl;
    return 0;
}