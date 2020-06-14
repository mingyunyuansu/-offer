/*
032-从1到n整数中1出现的次数
*/
//解释一下，比如n为10，则1~10中，出现了有1和10包含有1。

#include <iostream>
#include <vector>
#include <cmath>
#include<ctime>
using namespace std;

//暴力法，时间复杂度为O(N*lgN)，这里lg是10为底
int count(int each_i) {
	int cnt = 0;
	while (each_i) {
		if (each_i % 10 == 1) cnt++;
		each_i /= 10;
	}
	return cnt;
}

int brutal_force(int n) {
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		cnt += count(i);
	}
	return cnt;
}

//自己不看答案推导了一下，可以用排列组合方法直接计算，但是代码没写出来，需要分情况讨论的太多了。
//感觉也可以尝试递归
//但是我自己没写出来，看了答案醍醐灌顶

//记住以后递归尽量先用数学符号，f(n)的形式来抽象出表达式，会好做很多
//这道题看了好半天终于搞清楚。无论是剑指offer原书的解法，还是
//https://github.com/mingyunyuansu/CodingInterviews/tree/master/032-%E4%BB%8E1%E5%88%B0n%E6%95%B4%E6%95%B0%E4%B8%AD1%E5%87%BA%E7%8E%B0%E7%9A%84%E6%AC%A1%E6%95%B0
//的解法都非常精彩。我基本上是看懂了。以下解释为搬运：
/*
**任意一个n位数中"1"的个位可以分解为两个n-1位数中"1"的个数的和，最后再加上一个与最高位数相关的常数C**
例如，

对于n=12，可以拆分为0109,1012，即 f(12) = f(10 - 1) + f(12 - 10) + 3,其中3是表示最高位为1的数字个数，这里就是10,11,12；

对于n=132，可以拆分为099，100132，即f(132)=f(100 -1) + f(132 - 100) + 33，33代表最高位为1的数字的个数，这里就是100~132百位数字的1出新了33次

对于232，可以拆分为099，100232，即f(232) = 2*f(100 - 1) + f(32) + 100，因为232大于199，所以它包括了所有最高位为1的数字即100~199，共100个。

综上，我们分析得出，最后加的常数C只跟最高位n1是否为1有关

当最高位为1时，常数C为原数字N去掉最高位后剩下的数字+1，如N=12时，$C = 2 + 1 = 3$，N=132时，$C = 32 + 1 = 33$

当最高位大于1时，常数C为$10^(bit-1)$，其中bit为N的位数，如N=232时，bit=3，$C = 10^(bit-1) = 10^2 = 100$。 于是，我们可以列出递归方程如下：

if(n1 == 1)
	f(n) = f(10bit-1) + f(n - 10bit) + n - 10bit+ 1;
else
	f(n) = n1*f(10bit-1) + f(n – n1*10bit) + 10bit;
进一步可以归结为

f(n) = n1*f(10bit-1) + f(n – n1*10bit) + LEFT;
其中
if(n1 == 1)
	LEFT = n - 10bit+ 1;
else
	LEFT = 10bit;
*/
//我的理解：
//对于21345，分解为1~1345，和1346~21345，后者又可分为1346~11345，和11346到21345。
//我们需要计数的，可以认为是每一个位上出现的1的次数，万位的1的次数，加千位的1的次数。。。etc.
//看1346~11345，和11346到21345。
//他们的万位，出现1的次数是10000~19999的所有数，即10000个。不过，也要注意，如果万位就是1，比如11345，那么万位1的个数就是右边剩下的1345+1个。
//然后不考虑万位，1346~11345，和11346到21345又可以认为是两“份”相同的东西。后四位数，他们出现1的个数都是固定住1位为1，剩下取0~9，所以有10^3*4个取法。
//又因为有两份，所以是2*4*10^3。
//不知道别人如何，我肯定会考虑会不会重复数多了的问题，比如1xxx的第一个位已经取了一个1，到x1xx时，它（第一个位）又取了一次1。
//关于这一点，就像一开始说的，我们需要计数的，可以认为是每一个位上出现的1的次数。当固定住一个位时，只计数了这个位的1的数量，与其他位的值是多少无关，其他位的变动只是为了给这个位带来更多的1。

int recur(int n) {
	if (n == 0) return 0;
	if (n < 10) return 1;
	int digit = 0, t = n, cnt = 0;
	while (t) {
		digit++;
		t /= 10;
	}
	int first_digit = n / pow(10, digit - 1), other_part = n % (unsigned)pow(10, digit - 1);
	if (first_digit == 1) {
		cnt += other_part + 1;
	}
	else {
		cnt += pow(10, digit - 1);
	}
	cnt += (unsigned int)first_digit * (digit - 1) * pow(10, digit - 2);
	//或cnt += (unsigned)first_digit * recur((unsigned)(pow(10, digit - 1) - 1));也可以。
	//这里也就是f(232) = 2*f(100 - 1) + f(32) + 100中的f(99)
	return recur(other_part) + cnt;
}
//到此这个算法已经很快了，时间复杂度是O(lgN)（10为底），测试可以看出相当快。
//github那个答案还给出了一种解法，通过找规律并用分治实现。
//但是我认为到此为止即可，贪多嚼不烂，面试能做出递归就已经不错了。
int main() {
	int n = 2134569;
	clock_t t = clock();
	cout << brutal_force(n) << endl;
	t = clock() - t;
	cout << (double)t/CLOCKS_PER_SEC << "s consumed\n";
	//cout << my_solu(n) << endl;
	t = clock();
	cout << recur(n) << endl; 
	t = clock() - t;
	cout << ((double)t) / CLOCKS_PER_SEC << "s consumed\n";
	return 0;
}