#include <bits/stdc++.h>
using namespace std;

#define int long long

struct segtree{
    vector<int> k;
    int size;

    void init(int n){
        int i=1;
        while(i < n) i*=2;
        k.assign(2*i, 0);
        size = i;
    }

    void set(int pos, int x, int lx, int rx){
        if(rx-lx==1){
            k[x]=!k[x];
            return;
        }
        int meio = (lx+rx)/2;
        if(pos < meio) set(pos, 2*x+1, lx, meio);
        else set(pos, 2*x+2, meio, rx);
        k[x] = k[2*x+1] + k[2*x+2];
    }

    void set(int pos){
        set(pos, 0, 0, size);
    }

    int kth(int pos, int x, int lx, int rx){
        if(rx - lx == 1) return lx;
        int meio = (lx+rx)/2;
        int posicao;
        if(pos < k[2*x+1]) posicao = kth(pos, 2*x+1, lx, meio);
        else posicao = kth(pos-k[2*x+1], 2*x+2, meio, rx);
        return posicao;
    }

    int kth(int pos){
        return kth(pos, 0, 0, size);
    }
};

signed main(){
    int n,m;
    cin >> n >> m;
    segtree seg;
    seg.init(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x) seg.set(i);
    }

    for(int i=0;i<m;i++){
        int x, pos;
        cin >> x >> pos;
        if(x == 2) cout << seg.kth(pos) << endl;
        else seg.set(pos);
    }
    return 0;
}
