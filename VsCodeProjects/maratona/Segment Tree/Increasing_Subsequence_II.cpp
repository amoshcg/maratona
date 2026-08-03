#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define MOD (int)(1e9 + 7)

struct segtree{
    int size;
    vector<int> v;
    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1) {
            v[x] += val;
            return;
        }
        int meio = (rx + lx) / 2;
        if(pos < meio) set(pos, val, 2*x+1, lx, meio);
        else set(pos, val, 2*x+2, meio, rx);
        v[x] = (v[2*x+1] + v[2*x+2]) % MOD;
    }

    void set(int pos, int val){
        set(pos, val, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r) return v[x];
        int meio = (rx + lx) / 2;
        return (query(l, r, 2*x+1, lx, meio) + query(l, r, 2*x+2, meio, rx)) % MOD;
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    map<int,int> mp;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        mp[v[i]]++;
    }

    int pos = 0;
    for(auto &m:mp){
        m.second = pos++;
    }

    for(int i = 0; i < n; i++){
        v[i] = mp[v[i]];
    }

    segtree seg;
    seg.init(n);

    int ans = 0;
    for(int i = 0; i < n; i++){
        int subseq = 1 + seg.query(0, v[i]);
        ans = (ans + subseq) % MOD;
        seg.set(v[i], subseq);
    }
    cout << ans << endl;
    return 0;
}