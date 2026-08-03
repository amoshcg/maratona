#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    int size;
    vector<int> v;
    void init(int n){
        int i=1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
    }

    void set(int pos, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x] = 1;
            return;
        }
        int meio = (lx + rx) / 2;
        if(pos < meio) set(pos, 2*x+1, lx, meio);
        else set(pos, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void set(int pos){
        set(pos, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r) return v[x];
        int meio = (lx + rx) / 2;
        return query(l, r, 2*x+1, lx, meio) + query(l, r, 2*x+2, meio, rx);
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);

    for(int i=0;i<n;i++){
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(), v.end());

    vector<int> aux(n);
    for(int i=0;i<n;i++){
        aux[v[i].second] = i;
    }

    segtree seg;
    seg.init(n);
    
    vector<int> inversions;
    for(int i=0;i<n;i++){
        inversions.push_back(seg.query(aux[i],seg.size));
        seg.set(aux[i]);
        // for(int i=0;i<seg.size*2;i++){
        //     cout << seg.v[i] << " ";
        // }
        // cout << endl;
    }

    // for(auto inv:inversions) cout << inv << " ";
    // cout << endl;

    segtree other;
    other.init(n);

    vector<int> b(n);
    for(int i=n-1;i>=0;i--){
        b[i] = other.query(aux[i], other.size);
        other.set(aux[i]);
    }

    // for(auto bb:b) cout << bb << " ";
    // cout << endl;

    int ans = 0;
    for(int i=0;i<n;i++){
        ans += min(b[i], inversions[i]);
    }
    cout << ans << endl;

    return 0;
}

// Mando o valor para a direita ou para a esquerda