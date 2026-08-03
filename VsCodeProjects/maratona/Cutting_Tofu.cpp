#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

typedef __int128_t int128;

bool valid(vector<int> v, ld size, int k){

    if (size < 1e-10) return true;

    int total = 1;
    for(auto &w:v){
        total *= (w / size);
        if(total >= k) return true;
    }
    return false;
}

bool is_less(int a, int b, int c, int d){
    return (int128)a * d < (int128)c * b;
}

pair<int,int> best_fraction(vector<int> v, ld size){
    int p = v[0], q = max((int)(v[0] / size), (int)1);
    for (int i = 1; i < 3; i++) {
        int a = v[i];
        int b = max((int)(v[i] / size), (int)1);

        if (is_less(a, b, p, q)) {
            p = a;
            q = b;
        }
    }
    return {p,q};
}

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int k;
        vector<int> v(3);
        for(auto &w:v) cin >> w;
        cin >> k;

        ld low = 0, high = 1e9 + 5;
        for(int i = 0; i < 100; i++){
            ld mid = (low + high) / 2.0;

            if(valid(v, mid, k)){
                low = mid;
            } else high = mid;

        }

        pair<int,int> ans = best_fraction(v, low);
        int x = gcd(ans.first, ans.second);
        cout << ans.first / x << " " << ans.second / x << endl;
    }
    return 0;
}