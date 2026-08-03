#include <bits/stdc++.h>
using namespace std;

#define int long long

struct segtree{
    vector<int> v;
    int size;
    void init(int n){
        int i=1;
        while(i<n)i*=2;
        size = i;
        while(i<1e5)i*=2;
        v.assign(2*i,0);
    }

    void set(int pos, int x, int lx, int rx){
        if(rx-lx==1) {v[x]=!v[x]; return;}
        int meio = (rx+lx)/2;
        if(pos<meio) set(pos,2*x+1,lx,meio);
        else set(pos,2*x+2,meio,rx);
        v[x]=v[2*x+1]+v[2*x+2];
    }

    void set(int pos){
        set(pos-1, 0, 0, size);
    }

    int find(int inversions, int x, int lx, int rx){
        if(rx - lx == 1) return lx;
        int meio = (lx+rx)/2;
        if(inversions < v[2*x+2]) return find(inversions, 2*x+2, meio, rx);
        else return find(inversions - v[2*x+2], 2*x+1, lx, meio);
    }

    int find(int inversions){
        return find(inversions, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    segtree seg;
    seg.init(n);
    for(int i=1;i<=n;i++){
        seg.set(i);
    }
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    reverse(v.begin(),v.end());
    vector<int> resposta;
    for(int i=0;i<n;i++){
        int posicao = seg.find(v[i]);
        seg.set(posicao+1);
        resposta.push_back(posicao+1);
    }
    reverse(resposta.begin(),resposta.end());
    for(auto &r:resposta) cout << r << " ";
    cout << endl;
    return 0;
}