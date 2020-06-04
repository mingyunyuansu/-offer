/*
题意
题目描述

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。

假设压入栈的所有数字均不相等。

例如序列1,2,3,4,5是某栈的压入顺序，

序列4，5,3,2,1是该压栈序列对应的一个弹出序列，

但4,3,5,1,2就不可能是该压栈序列的弹出序列。
*/

//我在网易的笔试题见过类似的选择题，第一眼看到这个问题是感觉还是挺难的。
//因为压栈和入栈是同步进行的，可能的排列组合非常多。
//但是原书指出了一种不错的思路。有点类似用栈对正反括号进行查错。
//首先创建一个辅助栈，顺着压栈序列把数字依次进栈，直到遇到出栈序列的第一个数；
//这时把这个数出栈，然后出，入栈序列的指针都移到下一个数
//再顺着压栈直到遇到出栈序列的下个元素，遇到则出栈；
//如果把压栈序列都遍历完了，依然没有碰到该出栈的那个数，则说明不可能；
//最后栈为空，则说明可能。

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

bool is_possible(vector<int> in_arr, vector<int> out_arr) {
	stack<int> tmp;
	vector<int>::iterator in_ite = in_arr.begin(), out_ite = out_arr.begin();
	while (in_ite != in_arr.end()) {
		tmp.push(*in_ite++);
		while (out_ite != out_arr.end() && tmp.top() == *out_ite) {
			cout << tmp.top() << " ";
			tmp.pop();
			out_ite++;
		}
	}
	if (out_ite == out_arr.end() && tmp.empty()) {
		cout << "Yes" << endl;
		return true;
	}
	else {
		cout << "No, stuck at " << *out_ite << endl;
		return false;
	}
}

//同样的思路其实也可以只用O(1)空间来做
bool less_space(vector<int> pushV, vector<int> popV) {
	//vector<int>::iterator pop_i = popV.begin();
	/*
	for (vector<int>::iterator top = pushV.begin() - 1; top != pushV.end();) {
		++top;
		if (*top == *popV.begin()) {
			top = pushV.erase(top);
			top -= 1;
			popV.erase(popV.begin());
		}
			
	}
	return popV.empty();
	*/
	//在使用修改数组时用迭代器会出现意外的麻烦。
	//正确的做法是ite = v.erase(v)，会自动指向下一个有效的位置。
	//我的上面的代码在release版本下可以正常工作，但是debug模式认为我的迭代器在模拟栈开始时指向了begin()-1。
	//总之如果涉及遍历，又需要修改数组，还是用下标吧。
	for (int i = 0; i < pushV.size();)
	{
		if (pushV[i] == popV[0])
		{
			pushV.erase(pushV.begin() + i);
			popV.erase(popV.begin());
			i--;                                // 模拟出栈
		}
		else
		{
			i++;                                //  模拟入栈
		}
	}

	return pushV.empty();
}


int main() {
	vector<int> in = { 1,2,3,4,5 };
	vector<int> out = { 4,5,3,2,1 };
	vector<int> wrong = { 4,5,3,1,2 };
	is_possible(in, out);
		
	is_possible(in, wrong);

	if (less_space(in, out)) cout << "Yes\n";
	if (!less_space(in, wrong)) cout << "No\n";
	return 0;
}