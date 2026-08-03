#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n';


struct segtree{
    int size;
    vector<int> v;

    void init(int n){
        int i=1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
    }

    void update(int l, int r, int val, int x, int lx, int rx){
        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r){
            v[x] = max(val, v[x]);
            return;
        }
        
        v[2*x+1] = max(v[2*x+1], v[x]);
        v[2*x+2] = max(v[2*x+2], v[x]);
        
        int meio = (rx + lx) / 2;
        update(l, r, val, 2*x+1, lx, meio);
        update(l, r, val, 2*x+2, meio, rx);
    }

    void update(int l, int r, int val){
        update(l, r, val, 0, 0, size);
    }

    int query(int pos, int x, int lx, int rx){
        if(rx - lx == 1) return v[x];
        
        v[2*x+1] = max(v[x], v[2*x+1]);
        v[2*x+2] = max(v[x], v[2*x+2]);

        int meio = (rx + lx) / 2;
        if(pos < meio) return query(pos, 2*x+1, lx, meio);
        else return query(pos, 2*x+2, meio, rx);
    }

    int query(int pos){
        return query(pos, 0, 0, size);
    }
};

signed main(){
    int n, m;
    cin >> n >> m;
    segtree seg;
    seg.init(n);
    for(int i=0;i<m;i++){
        int op;
        cin >> op;
        if(op == 1){
            int l, r, val;
            cin >> l >> r >> val;
            seg.update(l, r, val);
        } else {
            int pos;
            cin >> pos;
            cout << seg.query(pos) << endl;
        }
    }
    return 0;
}