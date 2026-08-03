#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    vector<int> v;
    int size;
    void init(int n){
        int i=1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < a.size()) v[x] = a[lx];
            return;
        }
        int meio = (rx + lx) / 2;
        build(a, 2*x+1, lx, meio);
        build(a, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void build(vector<int> &a){
        build(a, 0, 0, size);
    }

    void update(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1) {
            v[x] = val;
            return;
        }
        int meio = (rx + lx) / 2;
        if(pos < meio) update(pos, val, 2*x+1, lx, meio);
        else update(pos, val, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void update(int pos, int val){
        update(pos, val, 0, 0, size);
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
};

signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    segtree seg;
    seg.init(n);
    seg.build(v);
    for(int i=0;i<q;i++){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) seg.update(x-1, y);
        else cout << seg.query(x-1, y) << endl;
    }
    return 0;
}