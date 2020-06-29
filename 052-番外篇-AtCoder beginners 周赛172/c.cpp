#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//这种写法是贪心，我又一次再贪心上吃亏了
//考虑(1,2,3)和(3,1,1)，可用时间是5分钟这种情况，如果一直采用贪心，那么就会只考虑A数组，这里应该用别人提供的考虑全局，prefix_sum，遍历A然后检索B来“凑”最大值的方法
//再次强调，贪心的使用只能在选择与顺序无关的情况下，或者已经被整顿（比如排序）。这里是有关的，因为不拿掉前一个数就无法考虑后面的数，实际上已经对选择产生了影响。
bool isPrime(long long x) {
    if (x == 2) return true;
    long long i = 2;
    while (i*i <= x) {
        if (x % i == 0) return false;
        ++i;
    }
    return true;
}

long long f(long long x, vector<long long> &v, long long N) {
    long long cnt = v[x];
    x *= x;
    while (x <= N) {
        v[x] = ++cnt;
        x *= x;
    }
    return cnt;
}

long long real_cnt(long long x, vector<long long> &v) {
    long long start = sqrt(x);
    while (x % start != 0) {
    start--;
    }
    v[x] = v[start]+1;
    return v[x];
}

int main() {
    long long N = 0;
    while (cin >> N) {
        vector<long long> v(N + 1, 0);
        v[1] = 1;
        v[2] = 2;
        long long i = 2;
        while (i <= N) {
            if (v[i] != 0) {++i; continue;}
            if (isPrime(i)) {
                v[i] = 2;
                f(i, v, N);
            }
            else {
                real_cnt(i, v);
            }
        }
        long long ans = 0;
        for (i = 1; i <= N; ++i)
            ans += i * v[i];
        cout << ans << endl;
    }
    return 0;
}