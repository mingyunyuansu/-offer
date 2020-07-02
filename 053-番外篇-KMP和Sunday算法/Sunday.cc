//应该是最完美的匹配算法了，又简单又高效（比KMP和BM都高）
//原理看这里https://wiki.jikexueyuan.com/project/kmp-algorithm/sunday.html
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "substring searching algorithm", sub = "search";
    int i = 0, tmp, cnt, newer, cnt_down;
    while (i < s.size() - sub.size()) {
        if (s[i] == sub[0]) {
            cnt = 1;
            tmp = i + 1;
            while (tmp < s.size() && cnt < sub.size() && s[tmp] == sub[cnt]) {
                cnt++;
                tmp++;
            }
            if (cnt == sub.size()) {
                    cout << i << endl;
                    return 0;
            }
            //not fully matched
            newer = s[i + sub.size()];
            cnt_down = sub.size() - 1;
            while (cnt_down >= 0 && sub[cnt_down] != newer) {
                cnt_down--;
            }
            i += (sub.size() - 1 - cnt_down);
        }
        else ++i;
    }
    cout << "Not found\n";
    return 0;
}