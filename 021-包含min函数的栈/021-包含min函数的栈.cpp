/*
题意
题目描述

定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。

#分析
思路很简单，我们维持两个栈，

数据栈data，存储栈的数据用于常规的栈操作

最小栈min，保存每次push和pop时候的最小值，

在push-data栈的时候，将当前最小数据压入，

在pop-data栈的时候，将min栈栈顶的最小数据弹出

这样保证min栈中存储着当前现场的最小值，并随着数据栈的更新而更新
*/

//说实话我没有太搞清楚这题目还有他的分析在干嘛。可能是我面向对象的功夫不够？在类里面定义一个私有变量保存最小值不就完了吗？为啥重开一个变量。
//只不过每次pop最小值时把最小值变量更新，需要考量一下，但是应该也有办法（直接遍历栈不行吗，捂脸。。。
//于是我读了原书，恍然大悟。
//原书要求push, pop min函数的时间都是O(1)，这样的话更新次小值就肯定超时了。
//于是书里用了一种很不错的办法，空间换时间。
//创建一个最小值变量，再开一个辅助栈，每次主栈压入数字，就通过和当前最小值的比较，压入“此时”“应该”的最小值。
//类似于把每一个元素弹出时，最小值的正确答案都提前压在辅助栈里。
//比如主栈压入3，辅助栈压3，主栈再压4，辅助栈还压3，因为4<3，如果弹出4，最小值依然是3；主栈再压2，则辅助栈也压2。

#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

class O1stack {
private:
	int minimum;
	stack<int> stk;
	stack<int> min_stk;
public:
	void push(int val) {
		if (this->stk.empty() || minimum > val) {
			this->minimum = val;
			this->min_stk.push(val);
		}
		else {
			this->min_stk.push(minimum);
		}
		this->stk.push(val);
	}
	void pop() {
		assert(!this->min_stk.empty() && !this->stk.empty());
		this->stk.pop();
		int tmp = this->min_stk.top();
		this->minimum = tmp;
		this->min_stk.pop();
	}
	int top() {
		assert(!this->min_stk.empty() && !this->stk.empty());
		return this->stk.top();
	}

	int min() {
		assert(!this->min_stk.empty() && !this->stk.empty());
		return this->min_stk.top();
	}
};
//基本功能可以用了。
//原书是用了继承的，但因为我C++面向对象的部分依然不熟，就先这样吧。

int main() {
	O1stack stack_with_min;
	stack_with_min.push(3);
	stack_with_min.push(4);
	stack_with_min.push(2);
	cout << stack_with_min.min() << endl;
	stack_with_min.pop();
	cout << stack_with_min.min() << endl;
	stack_with_min.pop();
	cout << stack_with_min.min() << endl;
	stack_with_min.pop();
	return 0;
}