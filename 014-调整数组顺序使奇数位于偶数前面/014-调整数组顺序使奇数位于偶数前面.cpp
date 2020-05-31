/*
题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

样例输入

5 1 2 3 4 5

样例输出

1 3 5 2 4

下面我们考虑算法复杂度的同时还会考虑其稳定性，（排序的稳定型则是指相同元素在数组中的相对位置是否发生变化），这里的稳定性我们理解为，顺序交换后，各个奇数（或者偶数）在数组中的相对位置是否发生变化
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void simple(vector<int> arr);
void print(vector<int> arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << '\n';
}

void simple(vector<int> arr) {
    //类似冒泡，每遇到一个偶数，就扔到最后，并且移动数组
    int end = arr.size();
    for (int i = 0; i < end; ++i) {
        if (arr[i] % 2 == 0) {
            int tmp = arr[i];
            //start moving
            int move = i;
            while (move < arr.size() - 1) {
                arr[move] = arr[move + 1];
                move++;
            }
            arr[move] = tmp;
            end--;
            --i;
        }
    }
    print(arr);
}

void extra_space(vector<int> arr) {
    //用额外的空间按序存储找出来的偶数，原数组中的偶数删除，遍历结束后两个相接
    vector <int> even_arr;
    vector<int>::iterator arr_i;
    for (arr_i = arr.begin(); arr_i != arr.end();) {
        if (*arr_i % 2 == 0) {
            even_arr.push_back(*arr_i);
            arr_i = arr.erase(arr_i);//注意这里的写法，erase删除掉一个元素后，应手动赋值以使迭代器指向被删除的下一个元素
        }
        else {
            arr_i++;
        }
    }
    for (vector<int>::iterator even_b = even_arr.begin(), even_e = even_arr.end(); even_b != even_e; even_b++) {
        arr.push_back(*even_b);
    }
    print(arr);
}

/*
GitHub还提了一种所谓的第三种解法，即：
由于题目中只要求记奇数在偶数之前，那么我们在扫描这个数组的时候，如果发现一个偶数出现在奇数之前就交换他们的位置，这样一趟后就满足要求了。

因此我们

维护两个索引或者指针，一个指向数组的第一个元素，并向后移动，一个指向数组的最后一个元素，并向前移动。

如果第一个指针指向的元素是偶数，而第二个指针指向的元素是奇数，说明偶数在奇数前面，那么就交换这两个数。

直到两个指针相遇为止
很明显，这种算法不能保证相同类型数据的相对位置不变，因此不稳定

比如要求 测试用例:

[1,2,3,4,5,6,7]

对应的稳定输出

[1,3,5,7,2,4,6]

我们算法的输出

[1,7,3,5,4,6,2]

头尾指针交换这个思路值得肯定，但是这结果完全不符合题意，还不如第一种，无厘头。
*/

int main() {
    const int N = 5;
    vector<int> arr(N);
    /*
    for (int i = 0; i < N; ++i) {
        arr[i] = i;
    }
    */
    srand(time(NULL));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 15;
    }
    print(arr);
    simple(arr);
    extra_space(arr);
    return 0;
}