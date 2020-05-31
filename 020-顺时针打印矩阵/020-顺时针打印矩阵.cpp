/*
题目描述

题目描述

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，

例如， 如果输入如下矩阵：

1 2 3 4 
5 6 7 8 
9 10 11 12 
13 14 15 16

则依次打印出数字

1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10
*/
//初看比较弱智，但是实际做了发现又是蛮烦的一道题。
//更像是考你有没有见过这种题，而与数据结构算法之类的无关。
//不过这题让我想起大一写解迷宫，一个人在食堂吃着土豆牛肉想了三个半小时，为什么这样的我却学不好编程呢？

#include <iostream>
#include <vector>
using namespace std;

void straight(vector<vector<int>> m) {
	int count = 0, max = m[0].size() * m.size();
	int left = 0, right = m[0].size(), up = 0, down = m.size();//boundaries
	int x = 0, y = 0; //coordinate
	while (count < max) {
		up++;
		while (y < right && count < max) {
			cout << m[x][y++] << " ";
			count++;
		}
		--y;
		++x;
		--right;
		while (x < down && count < max) {
			cout << m[x++][y] << " ";
			count++;
		}
		--x;
		--y;
		--down;
		while (y >= left && count < max) {
			cout << m[x][y--] << " ";
			count++;
		}
		++y;
		--x;
		++left;
		while (x >= up && count < max) {
			cout << m[x--][y] << " ";
			count++;
		}
		++x;
		++y;
	}
	cout << endl;
}

//我想说明一下。
//这题就尼玛离谱。
//https://github.com/mingyunyuansu/CodingInterviews/tree/master/020-%E9%A1%BA%E6%97%B6%E9%92%88%E6%89%93%E5%8D%B0%E7%9F%A9%E9%98%B5
//上面的解法还有一个利用方向数组来解的方法，以前我走迷宫时也用过这种方法，如下：
/*class Solution
{
    int n, m;
    vector<vector<bool> > v;
    bool judge(int i, int j)
    {
        return 0 <= i && i < n && 0 <= j && j < m && !v[i][j];
    }

public:
     vector<int> printMatrix(vector<vector<int> > a)
     {
        vector<int> r;
        if((n = a.size()) == 0 || (m = a[0].size()) == 0)
            return r;

        v = vector<vector<bool> >(n, vector<bool>(m, false));
        const int D[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int i = 0, j = 0, d = 0, count = m * n;
        while(count--)
        {
            r.push_back(a[i][j]);
            v[i][j] = true;
            if(!judge(i + D[d][0], j + D[d][1]))
            {
                (++d) %= 4; //转弯
            }
            i += D[d][0];
            j += D[d][1];//前进
        }
        return r;
    }
};*/
/*
可以看到他的解法似乎蛮巧妙，但是缺乏解释，特别是judge函数的return让人一时费解。于是我去看了原书中的解法，原书直接就离谱了。

原书中把这题搞得极为复杂，因为他不用count来做终止条件的判断，改为找规律。
首先定义每一次绕圈为一圈，即从[0,0]走到[1,1]。并且发现每一圈的起点一定是[n,n]两个n相等。
于是，很显然终止点的下标x，y应该刚好为行数m，列数n的二分之一。这样以start < m/2 && start < n/2才找到了终止条件。

之后，在每一圈中，也是把动作分解成了4段，并且需要考虑这一圈是否“坍塌”成了向量的问题，以决定是否只遍历一行就结束。
我服了，这题就到此为止吧，我寻思研究这种题意义也不太大。就算是大一新生也不该老拿这种题来折磨人。
*/

int main (){
	vector<vector<int>> matrix;
	for (int i = 0; i < 4; ++i) {
		vector<int> l;
		for (int j = 1; j <= 4; ++j) {
			l.push_back(j + i * 4);
		}
		matrix.push_back(l);
	}
	vector<vector<int>> matrix2 = { { 1,2,3,4 } };
	vector<vector<int>> matrix3 = { {1} };
	vector<vector<int>> matrix4 = { {1}, {2}, {3}, {4} };
	straight(matrix);
	straight(matrix2);
	straight(matrix3);
	straight(matrix4);
	
	return 0;
}