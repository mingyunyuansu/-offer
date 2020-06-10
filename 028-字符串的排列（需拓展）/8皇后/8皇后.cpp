/*
经典的八皇后问题。
一个八行八列的棋盘，八个皇后，互相不能攻击的放法一共有多少种。
首先不在同行同列是自然，那么创建一个数组[0~7]，每个下标i代表行i，arr[i]的值表示
行i的皇后所在的列数。这样就转化为了对0到7的全排列，并且还要验证对角线符合规则。
*/
#include <vector>
#include <iostream>
using namespace std;

void solution(vector<int> prefix, vector<int> layout, int &cnt);

void recur() {
    vector<int> layout(8);
    for (int i = 0; i < layout.size(); ++i) {
        layout[i] = i;
    }
    int cnt = 0;
    solution({}, layout, cnt);
    cout << "\ncount: " << cnt;
}

void solution(vector<int> prefix, vector<int> layout, int &cnt) {
    if (layout.size() == 0) {
        //验证合法性    
        for (int i = 0; i < prefix.size() - 1; ++i) {
            for (int j = i + 1; j < prefix.size(); ++j) {
                if (abs(prefix[i] - prefix[j]) == abs(i - j)) {
                    return;
                }
            }
        }
        cnt++;
        for (int x : prefix) {
            cout << x << " ";
        }
        cout << endl;
        return;
    }
    for (int i = 0; i < layout.size(); ++i) {
        //注意这里，同层的递归多次调用下级递归，需要恢复现场
        int tmp = layout[i];
        layout.erase(layout.begin() + i);
        prefix.push_back(tmp);
        solution(prefix, layout, cnt);
        prefix.pop_back();
        layout.insert(layout.begin() + i, tmp);
    }
}

int main() {
    recur();
    return 0;
}