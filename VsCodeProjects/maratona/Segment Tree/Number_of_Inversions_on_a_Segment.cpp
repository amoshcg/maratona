#include <bits/stdc++.h>
using namespace std;

struct segtree{
    vector<int> v;
    int size;

    void init(int n){
        int i=1;
        while(i<n)i*=2;
        size = i;
        v.assign(2*i,0);
    }

    void reset(){
        v.assign(2*size,0);
    }

    void set(int pos, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x]=1;
            return;
        }
        int meio=(lx+rx)/2;
        if(pos < meio) set(pos, 2*x+1, lx, meio);
        else set(pos, 2*x+2, meio, rx);
        v[x]=v[2*x+1]+v[2*x+2];
    }

    void set(int pos){
        set(pos, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l) return 0;
        if(lx >= l && rx <= r) return v[x];
        int meio = (lx+rx)/2;
        return get(l, r, 2*x+1, lx, meio) + get(l, r, 2*x+2, meio, rx);
    }

    int get(int l, int r){
        return get(l, r, 0, 0, size);
    }
};

signed main(){
    int n, m;
    cin >> n >> m;
    segtree seg;
    seg.init(40);
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }

    for(int i=0;i<m;i++){
        int op, x, y;
        cin >> op >> x >> y;
        x--;
        if(op == 1){
            int ans=0;
            // cout << "interval " << x << " " << y << endl;
            for(int i=x;i<y;i++){
                seg.set(v[i]-1);
                ans+=seg.get(v[i], seg.v.size());
            }
            cout << ans << endl;
            seg.reset();
        } else {
            v[x] = y;
        }
    }
    return 0;
}