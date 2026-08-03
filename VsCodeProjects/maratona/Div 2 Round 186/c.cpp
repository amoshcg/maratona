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
        int n;
        cin >> n;
        vector<int> a(n), b(n), c(n), validA(n), validB(n);
        generate(all(a), nxt);
        generate(all(b), nxt);
        generate(all(c), nxt);
        int ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(a[i] >= b[j]) continue;
                for(int k = 0; k < n; k++){
                    if(b[j] >= c[k]) continue;
                    bool valid = true;
                    for(int v = 0; v < n; v++){
                        if(a[(v+i)%n] >= b[(v+j)%n]) {
                            valid = false;
                            break;
                        }
                        if(b[(v+j)%n] >= c[(v+k)%n]) {
                            valid = false;
                            break;
                        }
                    }
                    if(valid) ans++;

                }
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}