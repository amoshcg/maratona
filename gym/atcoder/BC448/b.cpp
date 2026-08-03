#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    vector<pair<int,int>> v(n);
    for(int i = 0; i < m; i++){
        cin >> a[i];
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        int type, maximum;
        cin >> type >> maximum;
        if(a[type-1] - maximum >= 0){
            a[type-1] -= maximum;
            ans += maximum;
        } else {
            ans += a[type-1];
            a[type-1] = 0;
        }
    }
    cout << ans << endl;

}