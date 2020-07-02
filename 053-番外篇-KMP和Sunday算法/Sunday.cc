//应该是最完美的匹配算法了，又简单又高效（比KMP和BM都高）
//原理看这里https://wiki.jikexueyuan.com/project/kmp-algorithm/sunday.html
//但是进一步了解后才知道，即使有Sunday，KMP和BM还是很流行的原因在于，Sunday的最差时间复杂度可能会是O(m*n)。
//考虑
/*
主串：baaaabaaaabaaaabaaaa

模式串：aaaaa
*/
//匹配失败时只移动一个单位，时间复杂度很糟糕。
/*
BM
BM算法的预处理时间是O(m+ASIZE)
匹配时间最差是O(mn),引用论文的例子 (e.g. pattern = "CABABA," and string = "XXXXAABABAXXXXAABABA
..."). 可以看出每次最多只能移动2步，也就是运算（n-m）/2*（m-2）也就是O（mn）
最好的情况是 pattern:am-1b ,string:bn,(n-m)/m,也就是O（n/m）
对于无周期的模式串，时间复杂度不超过3n。
KMP
KMP的预处理时间是O(m)
匹配时间是比较稳定的是O(n)，证明如下：

循环体中”j = N[j];” 语句的执行次数不能超过 n 次。否则，由于“j = N[j]; ”
每执行一次必然使得j减少(至少减1)而使得 j 增加的操作只有“j++ ”那么，如果“j = N[j]; ”的执行次数超过n次，最终的结果必然
使得 j 为比-1小很多的负数。这是不可能的(j有时为-1,但是 很快+1回到0)。
*/

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