#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct queries{
    int l, r, pos, res;
};

bool op(queries first, queries second){
        return first.r < second.r;
    }

struct segtree{
    int size;
    vector<int> v;

    void init(int n){
        int i = 1;
        while(i < n) i*=2;
        size = i;
        v.assign(2*i, 0);
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1) {v[x] = val; return;}
        int meio = (rx + lx) / 2;
        if(pos < meio) set(pos, val, 2*x+1, lx, meio);
        else set(pos, val, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void set(int pos, int val){
        set(pos, val, 0, 0, size);
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

    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    vector<queries> qr(q);

    for(int i = 0; i < q; i++){
        cin >> qr[i].l >> qr[i].r;
        qr[i].pos = i;
    }

    sort(qr.begin(), qr.end(), op);

    segtree seg;
    seg.init(n);

    map<int,int> mp; // para guardar as posicoes anteriores de cada valor
    int dir = 0;
    for(int i = 0; i < q; i++){

        // lida com a insercao
        while(dir < qr[i].r){
            if(mp.count(v[dir])){
                seg.set(mp[v[dir]], 0); // remove a posicao anterior
            }
            seg.set(dir, 1); // insere na seg a posicao nova
            mp[v[dir]] = dir; // coloca no map a posicao nova
            dir++;
        }

        qr[i].res = seg.query(qr[i].l - 1, qr[i].r);

    }

    vector<int> ans(q);
    for(int i = 0; i < q; i++){
        ans[qr[i].pos] = qr[i].res;
    }

    for(auto &a:ans) cout << a << endl;
    return 0;
}