/*
#题目描述
输入一个递增排序的数组和一个数字s，在数组中查找两个数，得它们的和正好是s。如果有多对数字的和等于s，输出乘积最小的即可。

举例说明

例如输入数组｛1 、2 、4、7 、11 、15 ｝和数字15.

由于4+ 11 = 15 ，因此输出4 和11 。
*/

//老熟人了
#include <iostream>
#include <vector>
using namespace std;

void two_sum(vector<int>& v, int k) {
	int b = v[0] - 1;
	for (int i = 0; i < v.size(); ++i) {
		int a = v[i];
		int l = i + 1, r = v.size() - 1;
		int mid = (l + r) / 2;
		while (l <= r && v[mid] != k - a) {
			if (v[mid] < k - a) {
				l = mid + 1;
			}
			else {
				r = mid - 1;
			}
			mid = (l + r) / 2;
		}
		if (v[mid] == k - a) {
			b = k - a;
			cout << a << " " << b << endl;
			return;
		}
	}
	cout << "Not found\n";
}

void two_sum_with_pointer(vector<int> &v, int k) {
	int i = 0, j = v.size() - 1;
	while (i < j && v[i] + v[j] != k) {
		if (v[i] + v[j] < k) {
			i++;
		}
		else {
			--j;
		}
	}
	if (i != j && v[i] + v[j] == k) {
		cout << v[i] << " " << v[j] << endl;
		return;
	}
	cout << "Not found\n";
}

int main() {
	vector<int> v{ 1,2 ,4,7,11 ,15 };
	two_sum(v, 15);
	two_sum_with_pointer(v, 15);
	return 0;
}