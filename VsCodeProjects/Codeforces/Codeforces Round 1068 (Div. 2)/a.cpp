#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define endl '\n'
#define int long long
#define ld long double
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)


int nxt(){
    int x; cin >> x;
    return x;
}

signed main(){ 
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        int sleeping = 0;
        string s;
        cin >> s;
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') sleeping = k+1;
            else if (sleeping == 0) ans++;
            sleeping = max(sleeping-1, (int)0);
        }
        cout << ans << endl;
    }
    return 0;
}