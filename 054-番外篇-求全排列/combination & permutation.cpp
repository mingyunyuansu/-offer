#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//经典老番，组合问题
//感觉现实中排列比较多，但是组合比较少
//今天强化两个标准的组合和排列方法

//排列，递归交换法，感觉要比prefix安全点
void perm_recur(vector<vector<int> >& result, vector<int>& arr, int curr) {
    if (arr.size() == curr) {
        vector<int> tmp(arr.size());
        copy(arr.begin(), arr.end(), tmp.begin());
        if (!tmp.empty()) result.push_back(tmp);
        return;
    }
    for (int i = curr; i < arr.size(); ++i) {
        swap(arr[i], arr[curr]);
        perm_recur(result, arr, curr + 1);
        swap(arr[i], arr[curr]);
    }
}

vector<vector<int> > permutation(vector<int>& arr) {
    vector<vector<int> > result;
    perm_recur(result, arr, 0);
    return result;
}
//但是STL的next_permutation似乎用的是数字交换的方法，
//如http://www.waitingfy.com/archives/971#3stlnext_permutation
//介绍的那样。

//组合，用了一个有点类似DP的，但是其实还是bitmap的方法来映射选择的元素
bool cmp(int a, int b) {
    return a > b;
}
vector<vector<int> > combination(vector<int>& arr, int N) {
    vector<vector<int> > result;

    vector<int> bitmap(arr.size());
    int i;
    for (i = 0; i < N; ++i) {
        bitmap[i] = 1;
        //创建一个“二进制数”
    }
    //刚进来就需要添加第一组，即最左边的取法
    vector<int> tmp;
    for (int j = 0; j < arr.size(); ++j) {
        if (bitmap[j]) {
            tmp.push_back(arr[j]);
        }
    }
    result.push_back(tmp);
    for (i = 0; i < bitmap.size() - 1; ++i) {
        if (bitmap[i] == 1 && bitmap[i + 1] == 0) {
            swap(bitmap[i], bitmap[i + 1]);
            //其实就是把对原数组的组合，抽象为一个0,1数组中，选任意个1的问题
            sort(bitmap.begin(), bitmap.begin() + i, cmp);
            vector<int>().swap(tmp);
            for (int j = 0; j < arr.size(); ++j) {
                if (bitmap[j]) {
                    tmp.push_back(arr[j]);
                }
            }
            result.push_back(tmp);
            i = -1;
        }
    }
    return result;
}

int main() {
    vector<int> arr = { 1,2, 3, 4, 5 };
    vector<vector<int> > ans = permutation(arr);
    for (auto item : ans) {
        for (auto x : item) {
            cout << x << " ";
        }
        cout << "\n";
    }
    ans = combination(arr, 3);
    for (auto item : ans) {
        for (auto x : item) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}