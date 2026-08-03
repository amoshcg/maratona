#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct queries{
    char type;
    int x, y;
};

struct segtree{
    int size;
    vector<int> v;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        v.assign(2*i, 0);
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x] = val;
            return;
        }
        int meio = (rx + lx) / 2;
        if(pos < meio) set(pos, val, x, lx, meio);
        else set(pos, val, x, meio, rx);
        v[x = v[2*x+1]] + v[2*x+2];
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

// valor -> posicao na arvore

signed main(){
    int n, q;
    cin >> n >> q;
    vector<pair<int,int>> v(n);
    vector<pair<int,int>> v2(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].first;
        v[i].second = i;
        v2[i].first = v[i].first;
    }

    vector<queries> query(q);
    for(int i = 0; i < q; i++){
        cin >> query[i].type >> query[i].x >> query[i].y;
        if (query[i].type == '!') {
            // v2.push_back(query[i].y);
        }
    }

    sort(v2.begin(), v2.end());

    map<int,int> mp;
    // for(int i = 0; i < v2.size(); i++){
    //     mp[v2[i]] = i;
    // }

    segtree seg;
    seg.init(v2.size());

    for(int i = 0; i < n; i++){
        // seg.set(mp[v[i]], 1);
        // cout << mp[v[i]] << endl;
    }

    for(int i = 0; i < seg.size * 2; i++){
        cout << seg.v[i] << " ";
    }
    cout << endl;

    // for(int i = 0; i < q; i++){
    //     if(query[i].type == '?'){
    //         cout << seg.query(lower_bound(v2.begin(), v2.end(), query[i].x - 1) - v2.begin(), upper_bound(v2.begin(), v2.end(), query[i].y) - v2.begin()) << endl;
    //     } else {
    //         seg.set(mp[v[query[i].x-1]], 0);
    //         seg.set(mp[query[i].y], 1);
    //     }
    // }
    return 0;
}