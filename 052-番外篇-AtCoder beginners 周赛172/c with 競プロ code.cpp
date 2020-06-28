#include<bits/stdc++.h>
#define ll long long int
#define ld long double
#define vii vector<ll> 
#define pb push_back
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const int MOD = 1e9 + 7, N = 1e5 + 3;
 
int main(){
    fast;
    ll n, m, k;
    cin >> n >> m >> k;
    ll a[n+1], b[m+1], prefix_sum[n+1], prefix_sum1[m+1];
    prefix_sum[0] = 0;
    prefix_sum1[0] = 0;
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        prefix_sum[i] = prefix_sum[i-1] + a[i];
    }
    for(int i = 1; i <= m; ++i){
        cin >> b[i];
        prefix_sum1[i] = prefix_sum1[i-1] + b[i];
    }
    ll mx = 0;
    for(int i = 0; i <= n; ++i){
        ll diff = k - prefix_sum[i], ans = 0;
        if(diff < 0)
            break;
        ll low = 1, high = m;
        while(low <= high){
            ll mid = (low + high)/2;
            if(prefix_sum1[mid] <= diff){
                ans = mid;
                low = mid + 1; 
            }
            else
                high = mid - 1;
        }
        mx = max(mx, i+ans);  
        // cout << i << ' ' << ans << ' ';
    }
    cout << mx;
    return 0;
}
