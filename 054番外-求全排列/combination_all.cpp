#include <vector>
#include<iostream>
using namespace std;
//起因是actcoder的一个小周赛题需要求出1到n的所有组合
//我突然发现自己不太会这个
//网上递归的办法不少，但是好难懂，而且显然不如下面这个二进制的办法高效，这个真的是神仙想法

vector<int> get_each_result(vector<int> &arr, int curr, int total) {
    vector<int> one_result;
    for (int i = 0; i < total; ++i) {
        if ((curr >> i) & 1) {
            //这里其实是在依次检测每一位是否存在，存在则意味着该位映射的“项”被组合选中了
            one_result.push_back(arr[i]);
        }
    }
    return one_result;
}

vector<vector<int>> get_combination(vector<int> &arr, int total)//进一步扩散到求一个集合的所有组合，所以用vector
{
    vector<vector<int>> result;
    for (int i = 1; i < (1 << total); ++i) {
        //1 << total 得到用数字标识的bitmap，例如1,2,3就可以用111的二进制
        //来表示一个数。001到111,1分布的情况刚好可以不重复地映射每组结果
        vector<int> tmp = get_each_result(arr, i, total);
        if (!tmp.empty()) {
            result.push_back(tmp);
        }
    }
    return result;
}

int main() {
    int N = 5;
    vector<int> arr(N, 0);
    for (int i = 0; i < N; ++i) {
        arr[i] = i + 1;
    }
    vector<vector<int>> comb = get_combination(arr, N);
    for (auto item: comb) {
        for (auto x: item) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}