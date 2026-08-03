#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

signed main(){
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    int ans = 0;
    for(int i = 1; i < n; i++){
        if(v[i] < v[i-1]){
            ans += v[i-1] - v[i];
            v[i] = v[i-1];
        }
    }
    cout << ans << endl;
    return 0;
}
