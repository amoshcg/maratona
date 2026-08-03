#include <bits/stdc++.h>
using namespace std;

#define int long long

struct segtree{
    vector<int>v;
    int size;

    void init(int n){
        int i=1;
        while(i < n) i*=2;
        size = i;
        v.assign(2*i,0);
    }

    void add_to_segment(int l, int r, int val, int x, int lx, int rx){
        if(rx <= l || lx >= r) return;
        if(rx <= r && lx >= l) {
            v[x] += val;
            return;
        }
        int meio = (lx+rx)/2;
        add_to_segment(l, r, val, 2*x+1, lx, meio);
        add_to_segment(l, r, val, 2*x+2, meio, rx);
    }

    void add_to_segment(int l, int r, int val){
        add_to_segment(l, r, val, 0, 0, size);
    }

    int get_value(int pos, int x, int lx, int rx, int sum){
        if(rx - lx == 1) return sum + v[x];
        int meio = (rx+lx)/2;
        if(pos < meio) return get_value(pos, 2*x+1, lx, meio, sum + v[x]);
        else return get_value(pos, 2*x+2, meio, rx, sum + v[x]);
    }

    int get_value(int pos){
        return get_value(pos, 0, 0, size, 0);
    }
};

signed main(){
    int n, m;
    cin >> n >> m;
    segtree seg;
    seg.init(n);
    for(int i=0;i<m;i++){
        int op; cin >> op;
        if(op == 1){
            int l, r, val;
            cin >> l >> r >> val;
            seg.add_to_segment(l, r, val);
        } else {
            int pos; cin >> pos;
            cout << seg.get_value(pos) << endl;
        }
    }
    return 0;
}