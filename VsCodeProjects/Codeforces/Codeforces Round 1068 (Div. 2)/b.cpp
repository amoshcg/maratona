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
        int n = nxt();
        vector<int> a(n);
        vector<int> b(n);
        generate(all(a), nxt);
        generate(all(b), nxt);
        vector<int> smallest(n+1);
        vector<int> biggest(n+1);
        for(int i = 1; i <= n; i++){
            smallest[i] = min({smallest[i-1] - a[i-1], biggest[i-1] - a[i-1], b[i-1] - smallest[i-1], b[i-1] - biggest[i-1]});
            biggest[i] = max({smallest[i-1] - a[i-1], biggest[i-1] - a[i-1], b[i-1] - smallest[i-1], b[i-1] - biggest[i-1]});
            // cout << smallest[i] << " " << biggest[i] << endl;
        }
        cout << biggest[n] << endl;
    }
    return 0;
}