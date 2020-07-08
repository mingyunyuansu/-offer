/*
说来惭愧，数据结构课程大概是本科学的最不认真的课。
虽然很多东西在后来的算法和刷题中补起来了，但是唯独堆没有好好地补，虽然觉得总能动态得到一个最大最小值蛮不错，
但是总是没碰到。。
类似的还有迪杰斯特拉，这个似乎也和堆有关，之后也得补。

总之这篇是堆的练习和模板。
网上很多资料说得不清楚，最后还是看的英文资料
https://www.hackerearth.com/zh/practice/data-structures/trees/heapspriority-queues/tutorial/
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap {
public:
    void heapify(int index) {
        int left = index * 2, right = index * 2 + 1;
        int largest_index = index;
        if (right < vec.size() && vec[largest_index] < vec[right]) largest_index = right;
        if (left < vec.size() && vec[largest_index] < vec[left]) largest_index = left;
        if (index != largest_index) {
            swap(vec[index], vec[largest_index]);
            heapify(largest_index);
        }
    }
    void heap_insert(int val) {
        vec.push_back(val);
        int N = vec.size() - 1;
        for (int i = N / 2; i >= 1 && val > vec[i]; N = i, i /= 2) {
            swap(vec[i], vec[N]);
        }
    }
    void heap_remove(int val) {
        if (vec.size() <= 1) {
            cout << "Empty heap!\n";
            return;
        }
        int i = 1;
        while (i < vec.size() && vec[i] != val) {
            ++i;
        }
        if (i == vec.size()) {
            cout << "Not found.\n";
            return;
        }
        else {
            swap(vec[i], vec[vec.size() - 1]);
            vec.pop_back();
            heapify(i);
        }
    }
    void remove_top() {
        swap(vec[1], vec[vec.size() - 1]);
        vec.pop_back();
        heapify(1);
    }
    int find_max() {
        return vec[1];
    }
    MaxHeap(vector<int> already) {
        vec.resize(already.size() + 1);
        copy(already.begin(), already.end(), vec.begin() + 1);
        for (int i = (vec.size() - 1) / 2; i >= 1; --i) {
            heapify(i);
        }
    }
    MaxHeap() {
        vec = { 0 };
    }
private:
    vector<int> vec;
};

int main() {
    vector<int> v{ 3,4,1,2,6,4 };
    MaxHeap maxheap(v);
    maxheap.heap_insert(9);
    maxheap.remove_top();
    maxheap.heap_remove(6);
    cout << maxheap.find_max() << endl;
    return 0;
}