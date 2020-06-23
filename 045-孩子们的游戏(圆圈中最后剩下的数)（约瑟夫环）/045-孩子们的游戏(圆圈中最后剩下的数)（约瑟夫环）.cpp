/*
#题意
题目描述

每年六一儿童节,NowCoder都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。

HF作为NowCoder的资深元老,自然也准备了一些小游戏。

其中,有个游戏是这样的:

首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。

每次喊到m - 1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,

并且拿到NowCoder名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。

请你试着想下,哪个小朋友会得到这份礼品呢？

样例输入

1 10

8 5

6 6

样例输出

1

3

4
*/
//我好像隐隐看到了约瑟夫环的名字
#include <iostream>
#include <vector>
#include <list>
using namespace std;

int simulation(int n, int m) {
	if (n <= 0 || m <= 0) return -1;
	list<int> v(n);
	list<int>::iterator iter = v.begin();
	for (int i = 0; i < n; ++i) {
		*iter = i;
		iter++;
	}
	iter = v.begin();
	while (v.size() > 1) {
		int offset = (m-1) % (v.size());
		while (offset) {
			iter++;
			if (iter == v.end()) iter = v.begin();
			offset--;
		}
		iter = v.erase(iter);
		if (iter == v.end()) iter = v.begin();
	}
	return *(v.begin());
}

//约瑟夫问题显然是有数学解的，但是推导稍微有点难懂
//看这篇，会比较清楚
//https://zhuanlan.zhihu.com/p/121159246
//里面涉及一些函数的转换
//最直观的理解方式，就是观察发现，f(n)的结果可以由f(n-1)的结果加上一个特定的数，也就是m，来得到（其实是因为下一轮的计数起始点偏移了m位），因为是循环，所以模n。
//最后推得f(n, m) = (f(n-1, m) + m) % n，注意这个结论适用于最最标准的问题，
//即编号为0~n-1，喊号是0到m-1，m-1号出列，再从m号开始。
//如果有加一减一的要求，可能要重新推导
int Joseph(int n, int m) {
	if (n <= 0 || m <= 0) return -1;
	int fn = 0;
	int i = 1;
	while (i <= n) {
		fn = (fn + m) % i++;
	}
	return fn;
}

int main() {
	cout << simulation(5, 2) << endl;
	cout << Joseph(5, 2);
	return 0;
}