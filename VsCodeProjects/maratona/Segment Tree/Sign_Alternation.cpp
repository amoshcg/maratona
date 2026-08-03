#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    vector<int> v;
    int size;
    void init(int n){
        int i=1;
        while(i<n)i*=2;
        size=i;
        v.assign(2*i,0);
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx-lx==1) {
            v[x]=val;
            return;
        }
        int meio=(lx+rx)/2;
        if(pos < meio) set(pos,val,2*x+1,lx,meio);
        else set(pos,val,2*x+2,meio,rx);
        v[x]=v[2*x+1]+v[2*x+2];
    }

    void set(int pos, int val){
        set(pos, val, 0, 0, size);
    }

    int get_sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l) return 0;
        if(lx >= l && rx <= r) return v[x];
        int meio=(lx+rx)/2;
        return get_sum(l, r, 2*x+1, lx, meio)+get_sum(l,r,2*x+2,meio,rx);
    }

    int get_sum(int l, int r){
        return get_sum(l, r, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    segtree segpar, segimpar;
    segpar.init(n), segimpar.init(n);
    for(int i=0;i<n;i++){
        int x; cin >> x;
        if(i % 2 == 0){
            segpar.set(i, x);
            segimpar.set(i, -x);
        } else {
            segpar.set(i, -x);
            segimpar.set(i, x);
        }
    }

    int m; cin >> m;
    for(int i=0;i<m;i++){
        int op, x, y;
        cin >> op >> x >> y;
        x--;
        if(op == 0){
            if(x % 2 == 0){
                segimpar.set(x,-y);
                segpar.set(x,y);
            } else {
                segimpar.set(x,y);
                segpar.set(x,-y);
            }
        } else {
            if(x % 2 == 0) cout << segpar.get_sum(x, y) << endl;
            else cout << segimpar.get_sum(x, y) << endl;
        }
    }
}