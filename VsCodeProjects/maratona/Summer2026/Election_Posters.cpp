#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

struct segtree{
    vector<int> v, atualizar;
    int size;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        v.resize(2*size);
        atualizar.assign(2*size, 0);
    }

    void push(int lx, int rx, int x){
        if (atualizar[x] == 0 || rx - lx == 1) return;
        atualizar[2 * x + 1] = atualizar[x];
        v[2 * x + 1] = atualizar[x];
        atualizar[2 * x + 2] = atualizar[x];
        v[2 * x + 2] = atualizar[x];
        atualizar[x] = 0;
    }

    void post(int l, int r, int val, int x, int lx, int rx){
        // cout << x << " " << lx << " " << rx << endl;
        push(lx, rx, x);
        if(lx >= r || rx <= l) return;
        if(lx >= l && rx <= r){
            v[x] = val;
            atualizar[x] = val;
            push(lx, rx, x);
            return;
        }
        int meio = (rx + lx) / 2;
        post(l, r, val, 2*x+1, lx, meio);
        post(l, r, val, 2*x+2, meio, rx);
    }

    void post(int l, int r, int val){
        post(l, r, val, 0, 0, size);
    }

    void query(int x, int lx, int rx, set<int> &st){
        push(lx, rx, x);
        if(rx - lx == 1){
            if(v[x] != 0) st.insert(v[x]);
            return;
        }
        int meio = (rx + lx) / 2;
        query(2*x+1, lx, meio, st);
        query(2*x+2, meio, rx, st);
    }

    int query(){
        set<int> st;
        query(0, 0, size, st);
        return st.size();
    }
};

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        segtree seg;
        seg.init(1e7+5);
        int post = 1;
        for(int i = 0; i < n; i++){
            int l, r;
            cin >> l >> r;
            seg.post(l-1, r, post);
            post++;
        }
        cout << seg.query() << endl;
    }
}