#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)


struct node{
    int p_min, p_max, sum;
};

struct segtree{
    vector<node> v;
    vector<int> lazy;
    int size;

    void push(int x, int lx, int rx) {
        if (lazy[x] == 0) return;

        int original_min = v[x].p_min;
        v[x].p_min = -v[x].p_max;
        v[x].p_max = -original_min;
        v[x].sum = -v[x].sum;

        if (rx - lx != 1) {
            lazy[2 * x + 1] ^= 1;
            lazy[2 * x + 2] ^= 1;
        }
        lazy[x] = 0; 
    }

    node merge(node a, node b) {
        node res;
        res.sum = a.sum + b.sum;
        res.p_max = max(a.p_max, a.sum + b.p_max);
        res.p_min = min(a.p_min, a.sum + b.p_min);
        return res;
    }

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        v.resize(2*i);
        lazy.assign(2*i, false);
        size = i;
    }

    void build(vector<char> &a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < a.size()){
                if(a[lx] == '(') v[x] = {1,1,1};
                else v[x] = {-1,-1,-1};
            }
            return;
        }
        int meio = (rx + lx) / 2;
        build(a, 2*x+1, lx, meio);
        build(a, 2*x+2, meio, rx);
        v[x] = merge(v[2*x+1], v[2*x+2]);
    }

    void build(vector<char> &a){
        build(a, 0, 0, size);
    }

    void invert(int l, int r, int x, int lx, int rx){
        push(x, lx, rx);

        if(rx <= l || lx >= r) return;

        if(lx >= l && rx <= r) {
            lazy[x] = 1;
            push(x, lx, rx);
            return;
        }

        int meio = (rx + lx) / 2;
        invert(l, r, 2*x+1, lx, meio);
        invert(l, r, 2*x+2, meio, rx);
        v[x] = merge(v[2*x+1], v[2*x+2]);
    }

    void invert(int l, int r){
        invert(l, r, 0, 0, size);
    }

    node query(int l, int r, int x, int lx, int rx){
        push(x, lx, rx);

        if(rx <= l || lx >= r) return {(int)1e9, (int)-1e9, 0};

        if(lx >= l && rx <= r) return v[x];

        int meio = (rx + lx) / 2;
        node esq = query(l, r, 2*x+1, lx, meio);
        node dir = query(l, r, 2*x+2, meio, rx);

        if (esq.p_min == 1e9) return dir;
        if (dir.p_min == 1e9) return esq;
        
        return merge(esq, dir);
    }

    bool query(int l, int r){
        node aux = query(l, r, 0, 0, size);
        if(aux.sum == 0 && aux.p_min >= 0) return true;
        else return false;
    }
};

signed main(){
    fastio;
    int n, q;
    cin >> n >> q;
    vector<char> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    segtree seg;
    seg.init(n);
    seg.build(v);
    
    for(int i = 0; i < q; i++){
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1){
            seg.invert(l-1, r);
        } else {
            if(seg.query(l-1, r)) cout << "sim" << endl;
            else cout << "nao" << endl;
        }
    }

    
    return 0;
}