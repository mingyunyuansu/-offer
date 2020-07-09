/*
#2 题意
题目描述

题目描述

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值

例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3

那么一共存在6个滑动窗口, 他们的最大值分别为{4,4,6,6,6,5}；

针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个 {[2,3,4],2,6,2,5,1}，最大值4 {2,[3,4,2],6,2,5,1}，最大值4 {2,3,[4,2,6],2,5,1}，最大值6 {2,3,4,[2,6,2],5,1}，最大值6 {2,3,4,2,[6,2,5],1}，最大值6 {2,3,4,2,6,[2,5,1]}，最大值5
*/
//比较直观的办法是维护一个最大堆
//但是答案说了一种单调队列的办法，感觉比较靠谱，都写一下吧。

//Github还有一种双栈法，大概和之前用栈记录最小值的方法有关，但是我暂时不看了，似乎是编程之美上的解法，太偏了。
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

//用最大堆。不过官方实现似乎都是STL自带的make_heap啥的或者priority_queue
//之后有时间看看。
vector<int> with_max_heap(vector<int>& num, unsigned int size) {
    class MaxHeap {
    public:
        void heapify(int index) {
            int l = index * 2, r = l + 1, largest = index;
            if (l < heap.size() && heap[largest] < heap[l]) {
                largest = l;
            }
            if (r < heap.size() && heap[largest] < heap[r]) {
                largest = r;
            }
            if (largest != index) {
                swap(heap[index], heap[largest]);
                heapify(largest);
            }
        }

        void insert(int val) {
            heap.push_back(val);
            int N = heap.size() - 1;
            for (int i = N / 2; i > 0 && heap[i] < heap[N]; N = i, i >>= 1) {
                swap(heap[i], heap[N]);
            }
        }

        void remove(int val) {
            for (int i = 1; i < heap.size(); ++i) {
                if (heap[i] == val) {
                    swap(heap[i], heap[heap.size() - 1]);
                    heap.pop_back();
                    heapify(i);
                    return;
                }
            }
            cout << "Not found to be removed number.\n";
        }

        int get_top() {
            if (heap.size() > 1) {
                return heap[1];
            }
            else {
                cout << "Empty heap!\n";
                return -1;
            }
        }
        MaxHeap() : heap({ 0 }) {}
    private:
        vector<int> heap;
    };
    if (num.size() == 0 || size < 1 || num.size() < size) return {};
    int i = 0;
    MaxHeap h;
    vector<int> ans;
    while (i < num.size()) {
        h.insert(num[i]);
        if (i + 1 > size) {
            h.remove(num[i - size]);
        }
        if (i + 1 >= size) {
            ans.push_back(h.get_top());
        }
        ++i;
    }
    return ans;
}

vector<int> mononymous_queue(const vector<int>& num, unsigned int size) {
    deque<int> indices;
    vector<int> ans;
    if (num.size() == 0 || size < 1 || num.size() < size) return ans;
    for (int i = 0; i < num.size(); ++i) {
        while (!indices.empty() && num[i] >= num[indices.back()]) {
            indices.pop_back();
        }
        indices.push_back(i);
        while (!indices.empty() && i - indices.front() >= size) {//注意这里，右边会被视为无符号整数，溢出得一个超大的正数，导致判断失效，以后无符号数最好别参加减法
            indices.pop_front();
        }
        if (i + 1 >= size) ans.push_back(num[indices.front()]);
    }
    return ans;
}

int main() {
    vector<int> v{ 2,3,4,2,6,2,5,1 };
    int size = 3;
    vector<int> ans = with_max_heap(v, 3);
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;
    ans = mononymous_queue(v, 3);
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}