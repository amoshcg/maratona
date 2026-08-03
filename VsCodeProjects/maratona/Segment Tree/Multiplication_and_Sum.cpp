#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;

struct segtree{
    vector<int> v, changes;
    int size;
    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 1);
        changes.assign(2*i,1);
    }

    void build(int x, int lx, int rx){
        if(rx - lx == 1) {v[x] = 1; return;}
        int meio = (rx + lx) / 2;
        build(2*x+1, lx, meio);
        build(2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void build(){
        build(0, 0, size);
    }

    void add(int l, int r, int val, int x, int lx, int rx){

        // Update and push the changes to its children
        changes[x] = changes[x] % MOD;
        v[x] *= changes[x];
        v[x] = v[x] % MOD;
        if(rx - lx != 1){
            changes[2*x+1] *= changes[x];
            changes[2*x+2] *= changes[x];
            changes[2*x+1] = changes[2*x+1] % MOD;
            changes[2*x+2] = changes[2*x+2] % MOD;
        }
        changes[x] = 1;

        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r){
            v[x] *= val;
            v[x] = v[x] % MOD;

            // I push the changes its children
            if(rx - lx != 1){
                changes[2*x+1] *= val;
                changes[2*x+2] *= val;
                changes[2*x+1] = changes[2*x+1] % MOD;
                changes[2*x+2] = changes[2*x+2] % MOD;
            }
            
            return;
        }

        int meio = (rx + lx) / 2;

        add(l, r, val, 2*x+1, lx, meio);
        add(l, r, val, 2*x+2, meio, rx);

        v[x] = (v[2*x+1] + v[2*x+2]) % MOD;
    }

    void add(int l, int r, int val){
        add(l, r, val, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){

        // Update and push the changes to its children
        changes[x] = changes[x] % MOD;
        v[x] *= changes[x];
        v[x] = v[x] % MOD;
        if(rx - lx != 1){
            changes[2*x+1] *= changes[x];
            changes[2*x+2] *= changes[x];
            changes[2*x+1] = changes[2*x+1] % MOD;
            changes[2*x+2] = changes[2*x+2] % MOD;
        }
        changes[x] = 1;

        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r){
            return v[x];
        }

        int meio = (rx + lx) / 2;
        int ans = (query(l, r, 2*x+1, lx, meio) + query(l, r, 2*x+2, meio, rx)) % MOD;
        // v[x] = (v[2*x+1] + v[2*x+2]) % MOD;
        return ans;
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }
};

signed main(){
    int n, m;
    cin >> n >> m;
    segtree seg;
    seg.init(n);
    seg.build();
    for(int i=0;i<m;i++){
        int op;
        cin >> op;
        if(op == 1){
            int l, r, val;
            cin >> l >> r >> val;
            seg.add(l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r) << endl;
        }
        // for(int i=0;i<2*seg.size;i++){
        //     cout << seg.v[i] << " ";
        // } cout << endl;
        // for(int i=0;i<2*seg.size;i++){
        //     cout << seg.changes[i] << " ";
        // } cout << endl;
    }
    return 0;
}