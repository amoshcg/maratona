#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    int size;
    vector<int> v, inv;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
        inv.assign(2*i, 0);
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x] += val;
            return;
        }
        int meio = (rx + lx) / 2;
        if(pos < meio) set(pos, val, 2*x+1, lx, meio);
        else set(pos, val, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void set(int pos, int val){
        set(pos, val, 0, 0, size);
    }

    void set_inv(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1){
            inv[x] += val;
            return;
        }
        int meio = (rx + lx) / 2;
        if(pos < meio) set_inv(pos, val, 2*x+1, lx, meio);
        else set_inv(pos, val, 2*x+2, meio, rx);
        inv[x] = inv[2*x+1] + inv[2*x+2];
    }

    void set_inv(int pos, int val){
        set_inv(pos, val, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r) return v[x];
        int meio = (rx + lx) / 2;
        return query(l, r, 2*x+1, lx, meio) + query(l, r, 2*x+2, meio, rx);
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }

    int query_inv(int l, int r, int x, int lx, int rx){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r) return inv[x];
        int meio = (rx + lx) / 2;
        return query_inv(l, r, 2*x+1, lx, meio) + query_inv(l, r, 2*x+2, meio, rx);
    }

    int query_inv(int l, int r){
        return query_inv(l, r, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    segtree seg;
    seg.init(n);
    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += seg.query_inv(v[i], seg.size);
        seg.set_inv(v[i]-1, seg.query(v[i], seg.size));
        seg.set(v[i]-1, 1);
    }
    
    cout << ans << endl;
}