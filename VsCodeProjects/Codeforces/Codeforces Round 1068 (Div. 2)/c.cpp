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
        vector<int> v(n);
        set<int> st, qnt;
        for(int i = 0; i < n; i++){
            cin >> v[i];
            st.insert(v[i]);
        }

        set<int> ans, skipped;
        sort(all(v));

        for(int i = 0; i < n; i++){

            if(skipped.count(v[i])) continue;

            int val = v[i];

            bool flag = true;

            while(val <= k){
                if(!st.count(val)) flag = false;
                val += v[i];
            }

            val = v[i];

            if(flag){
                ans.insert(v[i]);
                while(val <= k){
                    skipped.insert(val);
                    val += v[i];
                }
            }
            
            if(skipped.size() == st.size()) break;
        }

        if(skipped.size() == st.size()){
            cout << ans.size() << endl;
            for(auto &a:ans) cout << a << " ";
            cout << endl;
        } else cout << -1 << endl;
    }
    return 0;
}