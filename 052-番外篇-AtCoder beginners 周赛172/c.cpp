#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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