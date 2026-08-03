#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()

struct segtree{
    vector<int> sums;
    int tamanho=1;

    // Inicializa a segtree
    void init(int n){
        while(tamanho < n)tamanho*=2;
        sums.assign(2*tamanho,0LL);
    }

    void build(vector<int>&v,int x,int lx,int rx){
        if(rx-lx==1){
            if(lx < v.size()) sums[x] = v[lx];
            return;
        }
        int m=(lx+rx)/2;
        build(v,2*x+1,lx,m);
        build(v,2*x+2,m,rx);
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    segtree(vector<int>&v){
        init(v.size());
        build(v,0,0,tamanho);
    }

    void set(int pos, int valor, int x, int lx, int rx){
        if(rx-lx==1){
            sums[x] = valor;
            return;
        }
        int meio = (lx+rx)/2;
        if(pos < meio){
            set(pos,valor,2*x+1,lx,meio);
        } else {
            set(pos,valor,2*x+2,meio,rx);
        }
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    void set(int pos, int valor){
        set(pos, valor, 0, 0, tamanho);
    }

    int sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return sums[x];
        int meio=(lx+rx)/2;
        int s1=sum(l,r,2*x+1,lx,meio);
        int s2=sum(l,r,2*x+2,meio,rx);
        return s1+s2;
    }

    int sum(int l, int r){
        return sum(l, r, 0, 0, tamanho);
    }
};

int nxt(){
    int x;
    cin >> x;
    return x;
}

signed main(){
    int n, m;
    cin >> n >> m;
    vector<int>v(n);
    generate(all(v),nxt);
    segtree seg = segtree(v);
    for(int i=0;i<m;i++){
        int x, y, z;
        cin >> x >> y >> z;
        if(x==1) seg.set(y, z);
        else  cout << seg.sum(y,z) << endl;
    }
    return 0;
}
