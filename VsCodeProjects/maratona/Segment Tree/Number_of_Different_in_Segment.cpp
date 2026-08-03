#include <bits/stdc++.h>
using namespace std;

#define int long long

struct quarenta{
    int v[40]{};
};

struct segtree{
    int v[262144][40]{};
    int size;

    void init(int n){
        int i=1;
        while(i < n) i *= 2;
        size = i;
    }

    void build(vector<int> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < a.size()){
                v[x][a[lx]-1]++;
            }
            return;
        }
        int meio = (lx+rx)/2;
        build(a, 2*x+1, lx, meio);
        build(a, 2*x+2, meio, rx);
        for(int i=0;i<40;i++){
            v[x][i] = v[2*x+1][i] + v[2*x+2][i];
        }
    }

    void build(vector<int> &a){
        build(a, 0, 0, size);
    }

    void update(int pos, int val, int ant, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x][val]++;
            v[x][ant]--;
            return;
        }
        int meio = (lx + rx) / 2;
        if(pos < meio) update(pos, val, ant, 2*x+1, lx, meio);
        else update(pos, val, ant, 2*x+2, meio, rx);
        for(int i=0;i<40;i++){
            v[x][i] = v[2*x+1][i] + v[2*x+2][i];
        }
    }

    void update(int pos, int val, int ant){
        update(pos-1, val-1, ant-1, 0, 0, size);
    }

    void query(int l, int r, int x, int lx, int rx, quarenta &q){
        if(rx <= l || lx >= r) return;
        if(lx >= l && rx <= r) {
            for(int i=0;i<40;i++){
                q.v[i] += v[x][i];
            }
            return;
        }
        int meio = (rx+lx)/2;
        query(l, r, 2*x+1, lx, meio, q);
        query(l, r, 2*x+2, meio, rx, q);
    }

    int query(int l, int r){
        quarenta q;
        int ans=0;
        query(l-1, r, 0, 0, size, q);
        for(int i=0;i<40;i++){
            if(q.v[i] > 0) ans++;
        }
        return ans;
    }
};


signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }

    segtree seg;
    seg.init(n);

    seg.build(a);

    

    for(int i=0;i<q;i++){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 2){
            seg.update(x,y,a[x-1]);
            a[x-1] = y;
        } else {
            cout << seg.query(x, y) << endl;
        }
    }

    return 0;
}