#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    int size;
    vector<int> v;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        v.resize(2*i);
        size = i;
    }

    void set(int l, int r, int val, int x, int lx, int rx){
        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r) {
            v[x] = max(v[x], val);
            return;
        }
        int meio = (rx + lx) / 2;
        set(l, r, val, 2*x+1, lx, meio);
        set(l, r, val, 2*x+2, meio, rx);
    }

    void set(int l, int r, int val){
        set(l, r, val, 0, 0, size);
    }

    int get(int pos, int x, int lx, int rx){
        if(rx - lx == 1) return v[x];
        int meio = (rx + lx) / 2;
        if(pos < meio) return max(v[x], get(pos, 2*x+1, lx, meio));
        else return max(v[x], get(pos, 2*x+2, meio, rx));
    }

    int get(int pos){
        return get(pos, 0, 0, size);
    }
};

signed main(){
    int n, m;
    cin >> n >> m;
    segtree seg;
    seg.init(n);
    for(int i = 0; i < m; i++){
        int op;
        cin >> op;
        if(op == 1){
            int l, r, val;
            cin >> l >> r >> val;
            seg.set(l, r, val);
        } else {
            int pos;
            cin >> pos;
            cout << seg.get(pos) << endl;
        }
    }

}