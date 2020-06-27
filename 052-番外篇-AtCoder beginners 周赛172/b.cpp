#include <iostream>
#include <string>
//#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

long long solu (vector<long long> &A, vector<long long> &B, long long K) {
    long long i = 0, j = 0;
    while (i < A.size() && j < B.size() && (A[i] <= K || B[j] <= K)) {
        if (A[i] <= B[j] && A[i] <= K) {
            K -= A[i];
            ++i;
        }
        else if (A[i] >= B[j] && B[j] <= K){
            K -= B[j];
            ++j;
        }
    }
    while (i < A.size() && A[i] <= K) {
        K -= A[i];
        ++i;
    }
    while (j < B.size() && B[j] <= K) {
        K -= B[j];
        ++j;
    }
    return i+j;
}

int main() {
    long long N = 0, M = 0, K= 0;
    vector<long long> A, B;
    while (cin >> N >> M >> K) {
        long long a = 0, b = 0, tmp = 0;
        while (a < N) {
            cin >> tmp;
            A.push_back(tmp);
            a++;
        }
        while (b < M) {
            cin >> tmp;
            B.push_back(tmp);
            b++;
        }
        cout << solu(A, B, K) <<endl;
        vector<long long> ().swap(A);
        vector<long long> ().swap(B);
    }
    return 0;
}