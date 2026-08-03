#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    int size;
    vector<int> v;

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
    }

    void build(vector<int> &a){
        build(a, 0, 0, size);
    }

    void update(int l, int r, int val, int x, int lx, int rx){
        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r) {v[x] += val; return;}
        int meio = (rx + lx) / 2;
        update(l, r, val, 2*x+1, lx, meio);
        update(l, r, val, 2*x+2, meio, rx);
    }

    void update(int l, int r, int val){
        update(l, r, val, 0, 0, size);
    }

    int query(int pos, int x, int lx, int rx){
        if(rx - lx == 1) return v[x];
        int meio = (rx+lx)/2;
        int soma = 0;
        if(pos < meio) soma += query(pos, 2*x+1, lx, meio);
        else soma += query(pos, 2*x+2, meio, rx);
        return soma + v[x];
    }

    int query(int pos){
        return query(pos, 0, 0, size);
    }
};

signed main(){
    int n, q;
    cin >> n >> q;
    segtree seg;
    seg.init(n);
    vector<int>v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    seg.build(v);
    for(int i=0;i<q;i++){
        int op;
        cin >> op;
        if(op == 1){
            int x, y, val;
            cin >> x >> y >> val;
            seg.update(x-1, y, val);
        } else {
            int pos;
            cin >> pos;
            cout << seg.query(pos-1) << endl;
        }
    }
    return 0;
}