/*
#2 题意
题目描述

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//仔细看了才发现这题找到最优解还蛮难的
//因为数字流不能保证有序，因此需要一个动态排序的办法
//暴力排序肯定太慢了，AVL树是答案提到的一个可选方法，插入logN，取中位数O(1)。
//但是AVL树实现非常难（原来不是因为我太笨）
//所以可以用两个堆来实现
//具体思路可以看pdf

void heapify_max(vector<int>& max, int index) {
    int l = 2 * index, r = l + 1;
    int largest = index;
    if (l < max.size() && max[largest] < max[l]) largest = l;
    if (r < max.size() && max[largest] < max[r]) largest = r;
    if (largest != index) {
        swap(max[index], max[largest]);
        heapify_max(max, largest);
    }
}

void heapify_min(vector<int> &min, int index) {
    int l = 2 * index, r = l + 1;
    int smallest = index;
    if (l < min.size() && min[smallest] > min[l]) smallest = l;
    if (r < min.size() && min[smallest] > min[r]) smallest = r;
    if (smallest != index) {
        swap(min[index], min[smallest]);
        heapify_min(min, smallest);
    }
}

void insert(vector<int>& max, vector<int>& min, int cnt, int num) {
    //必须保证最大堆和最小堆的元素个数最接近
    //且任意时刻最大堆中的所有元素（左半段）小于等于最小堆的所有元素（右半段）
    if (cnt & 1) {
        //希望在奇数的时候插入最小堆，则先插入最大堆，再把
        //最大堆的头插入最小堆。因为最大堆的头是左半段最大的数，这样就能保证
        //最小堆中所有数都大于最大堆
        max.push_back(num);
        int N = max.size() - 1;
        for (int i = N / 2; max[N] > max[i] && i > 0; N = i, i = N / 2) {
            swap(max[i], max[N]);
        }
        int maximum_in_left = max[1];
        //开始删除最大堆的top
        swap(max[1], max[max.size() - 1]);
        max.pop_back();
        //heapify the max one
        heapify_max(max, 1);
        //最大堆弹出完成
        //插入最小堆
        min.push_back(maximum_in_left);
        N = min.size() - 1;
        for (int i = N / 2; i > 0 && min[N] < min[i]; N = i, i <<= 1) {
            swap(min[i], min[N]);
        }
    }
    else {
        //此时为偶数，我们规定插入最大堆
        //则需要先插入最小堆，最小堆弹出到最大堆
        min.push_back(num);
        int N = min.size() - 1;
        for (int i = N / 2; min[N] < min[i] && i > 0; N = i, i = N / 2) {
            swap(min[i], min[N]);
        }
        int minimum_in_right = min[1];
        //开始删除最小堆的top
        swap(min[1], min[min.size() - 1]);
        min.pop_back();
        //heapify the max one
        heapify_min(min, 1);
        //最小堆弹出完成
        //插入最大堆
        max.push_back(minimum_in_right);
        N = max.size() - 1;
        for (int i = N / 2; i > 0 && max[N] > max[i]; N = i, i >>= 1) {
            swap(max[i], max[N]);
        }
    }
}

double get_midval(vector<int>& max, vector<int>& min, int cnt) {
    if (cnt & 1) {
        return min[1];
    }
    else {
        return (min[1] + max[1]) / 2.0;
    }
}

int main() {
    vector<int> max, min;
    max.push_back(0);
    min.push_back(0);
    for (int i = 1; i < 11; ++i) {
        insert(max, min, i, i);
        cout << get_midval(max, min, i) << "\n";
    }
    return 0;
}
//一把过，爽！