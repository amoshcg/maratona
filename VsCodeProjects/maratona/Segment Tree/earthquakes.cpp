#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define endl '\n'
#define int long long
#define ld long double
#define bg3 ios_base::sync_with_stdio(NULL); cin.tie(NULL); cout.tie(NULL);

struct segtree{
    
    vector<int> v;
    int size;

    void init(int n){
        int i=1;
        while(i < n) i *= 2;
        v.assign(2*i, LLONG_MAX);
        size = i;
    }

    void update(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x] = val;
            return;
        }
        int meio = (lx + rx) / 2;
        if(pos < meio) update(pos, val, 2*x+1, lx, meio);
        else update(pos, val, 2*x+2, meio, rx);
        v[x] = min(v[2*x+1], v[2*x+2]);
    }

    void update(int pos, int val){
        update(pos, val, 0, 0, size);
    }

    int earthquake(int l, int r, int power, int x, int lx, int rx){
        if(rx <= l || lx >= r) return 0;

        if(v[x] > power) return 0;

        if(rx - lx == 1) {
            v[x] = LLONG_MAX;
            return 1;
        }

        int soma = 0, meio = (lx+rx) / 2;

        soma += earthquake(l, r, power, 2*x+1, lx, meio);
        soma += earthquake(l, r, power, 2*x+2, meio, rx);

        v[x] = min(v[2*x+1],v[2*x+2]);

        return soma;
    }

    int earthquake(int l, int r, int power){
        return earthquake(l, r, power, 0, 0, size);
    }
};

signed main(){
    bg3;
    int n, m;
    cin >> n >> m;

    segtree seg;
    seg.init(n);

    for(int i=0;i<m;i++){
        int op;
        cin >> op;
        if(op == 1){
            int i, h;
            cin >> i >> h;
            seg.update(i, h);
        } else {
            int l, r, p;
            cin >> l >> r >> p;
            cout << seg.earthquake(l, r, p) << endl;
        }
        // for(int i=0;i<2*seg.size;i++){
        //     for(auto [f,s]:seg.v[i]){
        //         cout << "{" << f << ", " << s << "}" << " ";
        //     }
        //     cout << endl;
        // }
    }

    
    return 0;
}