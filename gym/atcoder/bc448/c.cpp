#include <bits/stdc++.h>
using namespace std;

struct segtree{
    vector<int> seg;
    int size;

    void init(int n){
        int i = 1;
        while(i < n){
            i *= 2;
        }
        seg.assign(2*i,INT_MAX);
        size = i;
    }

    void build(vector<int> &v, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < v.size()){
                seg[x] = v[lx];
            }
            return;
        }
        int meio = (rx + lx) / 2;
        build(v, 2*x+1, lx, meio);
        build(v, 2*x+2, meio, rx);
        seg[x] = min(seg[2*x+1], seg[2*x+2]);
    }

    void build(vector<int> &v){
        build(v, 0, 0, size);
    }

    int query(){
        return seg[0];
    }

    void update(int pos, int val, int x, int lx, int rx){

        if(rx - lx == 1){
            seg[x] = val;
            return;
        }

        int meio = (rx + lx) / 2;

        if(pos < meio) update(pos, val, 2*x+1, lx, meio);
        else update(pos, val, 2*x+2, meio, rx);
        seg[x] = min(seg[2*x+1], seg[2*x+2]);
    }

    void update(int pos, int val){
        update(pos, val, 0, 0, size);
    }
};

int main(){
    int n, q;
    cin >> n >> q;
    segtree seg;
    seg.init(n);
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    seg.build(v);

    for(int i = 0; i < q; i++){
        int tam;
        cin >> tam;
        vector<int> aux(tam);
        for(int j = 0; j < tam; j++){
            cin >> aux[j];
        }

        for(int j = 0; j < tam; j++){
            seg.update(aux[j]-1, INT_MAX);
        }

        cout << seg.query() << endl;

        for(int j = 0; j < tam; j++){
            seg.update(aux[j]-1, v[aux[j]-1]);
        }
    }

    
    
}