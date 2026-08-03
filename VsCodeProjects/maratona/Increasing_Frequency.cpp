#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int MAX = 5e5+5;
int dp[MAX];

signed main(){
    int n, c, c_count = 0, ans = 0;
    cin >> n >> c;

    for(int i = 0; i < n; i++){
        int val; cin >> val;

        if(val == c) c_count++;
        else dp[val] = max(dp[val], c_count) + 1;

        ans = max(ans, dp[val] - c_count);
    }
    cout << c_count + ans << endl;
    return 0;
}