#include <stdio.h>
#include <stdlib.h>

/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减序列的一个旋转，输出旋转数组的最小元素。

例如

数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，

该数组的最小值为1。
*/
int brute_force(int arr[], int len) {
    if (!arr) {printf("NULL array.\n"); return 0;}
    int i = 1;
    int res = arr[0];
    while (i < len) {
        if (res > arr[i]) res = arr[i];
    ++i;
    }
    return res;
}

int the_one_that_descent (int arr[], int len) {
    if (!arr) {printf("NULL array.\n"); return 0;}
    int res = arr[0];
    int i = 1;
    while (i < len && arr[i] >= arr[i-1]) {
        ++i;
    }
    if (res > arr[i]) res = arr[i];
    return res;
}

//二分查找思路。在整个数组两端放两指针，考察位于正中的数。正中的数大于等于左指针，则说明中间数还在左边的数组上，把左边指针指向这个中间数重复；不然，则说明落在了右边数组上，则把右指针指向中间数。最终结果，两个指针会相邻，右指针会指向最小值。至于为什么一定是右指针指向，因为右边的数组总是小于左边数组，所以最小值一定会收束在右指针上。
int two_pointers_devision (int arr[], int len) {
    if (!arr) {printf("NULL array.\n"); return 0;}
    if (len <= 1 || arr[0] < arr[len-1]) return arr[0];//没旋转
    int l = 0, r = len-1;
    while (l + 1 != r) {
        int mid = (l + r) / 2;
        //特殊测试用例，考虑{1,0,1,1,1}。
        //mid l r三者值都为1，造成错误输出1（实际为0）
        //此时分治方法失效
        if (arr[mid] == arr[l] && arr[mid] == arr[r]) return the_one_that_descent(arr, 5);
        
        if (arr[l] <= arr[mid]) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    return arr[r];
}

int main () {
    int arr[] = {1,0,1,1,1};
    printf("%d\n", brute_force(arr, 5));
    printf("%d\n", the_one_that_descent(arr, 5));
    printf ("%d\n", two_pointers_devision(arr, 5));
    return 0;
}