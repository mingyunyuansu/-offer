//KMP算法的解释参看http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
//实际上还有一些更深入的变种（自动后缀机啥的），或者BM算法。但是不准备搞了，面试准备一个KMP一个Sunday就够了
//KMP算法的核心就是部分匹配表(Partial Match Table)
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> create_table(string& s) {
    int i = 1, j, max_len; //只有一个字符的话前后缀都是空集
    vector<int> table(s.size(), 0);
    while (i < s.size()) {
        j = 0;
        max_len = 0;
        while (j < i) {
            if (s.substr(0, j + 1) == s.substr(i - j, j + 1)) {//C++的substr的第二个参数是“截取的字符串长度”
                if (j + 1 > max_len) {
                    max_len = j + 1;
                }
            }
            ++j;
        }
        table[i++] = max_len;
    }
    return table;
}

int main() {
    string s = "BBC ABCDAB ABCDABCDABDE";
    string sub = "ABCDABD";
    vector<int> table = create_table(sub);
    int cur = 0, cnt = 0, tmp;
    if (s == sub)
    {
        cout << 0 << endl;
        return 0;
    }
    while (cur < s.size()) {
        if (s[cur] == sub[0]) {
            cnt = 1;
            tmp = cur + 1;
            while (tmp < s.size() && cnt < sub.size() && s[tmp] == sub[cnt]) {
                tmp++;
                cnt++;
            }
            if (cnt == sub.size()) {
                cout << cur << endl;
                return 0;
            }
            else {
                //移位数 = 已匹配数 - 匹配表对应值
                cur += (cnt - table[cnt - 1]);
            }
        }
        else ++cur;
    }
    cout << "Not found\n";
    return 0;
}