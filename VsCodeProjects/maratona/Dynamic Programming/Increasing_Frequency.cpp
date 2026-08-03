#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

signed main(){
    fastio;
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    vector<int> dp_positive(1e5), dp_negative(1e5);

    for(int i = 0; i < n; i++){
        int val = k - v[i];
        if(val >= 0) dp_positive[val]++;
        else dp_negative[-val]++;
    }

    int ans = LLONG_MIN;
    for(int i = 0; i < 1e5; i++){
        ans = max({ans, dp_positive[i], dp_negative[i]});
    }
    cout << ans << endl;
    return 0;
}