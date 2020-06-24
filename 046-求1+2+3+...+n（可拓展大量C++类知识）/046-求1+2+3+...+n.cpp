/*
#题意
题目描述

求1+2+3+...+n，

要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

样例输入

3

5

样例输出

6

15
*/
//真是会玩
//初看直接懵逼，直接看答案

#include <iostream>
using namespace std;

//递归加短路终止
int recur_short_circuit(int n) {
	int ans = n;
	n && (ans += recur_short_circuit(n - 1));
	return ans;
}

//利用a和b相乘的位运算的规则，并用递归代替循环
int recur_with_bit(int a, int b) {
	int ans = 0;
	(a & 1) && (ans += b);
	a && (ans += recur_with_bit(a >> 1, b << 1));
	return ans;
}

int with_bit(int n) {
	return recur_with_bit(n, n + 1) >> 1;
}

//然后就看见C++的神仙操作开始了。。。
//见https://github.com/mingyunyuansu/CodingInterviews/tree/master/046-%E6%B1%821%2B2%2B3%2B...%2Bn
class tmp {
public:
	tmp() {
		++N;
		sum += N;
	}
	static void Reset() {
		N = 0;
		sum = 0;
	}
	static int GetSum() {
		return sum;
	}
private:
	int static N;
	int static sum;
};
int tmp::N = 0;//类静态变量只能在全局处初始化
int tmp::sum = 0;

int main() {
	cout << recur_short_circuit(5) << endl;
	cout << with_bit(2) << endl;

	//-------------------------------
	//多次初始化来加
	//顺便补习了一下C++的类静态成员
	int n = 5;
	tmp::Reset();//所以其实这行多余
	tmp* tmp_n = new tmp[n];
	delete[] tmp_n;//delete[]相比delete在于会依次对数组中的成员一个个调用析构函数
	//否则只delete掉a[0]
	tmp_n = NULL;	
	cout << tmp::GetSum() << endl;
	//-------------------------------

	return 0;
}