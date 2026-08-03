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
        while(i < 1e5)i*=2;
        v.assign(2*i,0);
    }

    void set(int pos, int x, int lx, int rx){
        if(rx - lx == 1) {v[x] = 1; return;}
        int meio=(rx+lx)/2;
        if(pos < meio) set(pos, 2*x+1, lx, meio);
        else set(pos, 2*x+2, meio, rx);
        v[x] = v[2*x+1] + v[2*x+2];
    }

    void set(int pos){
        set(pos-1, 0, 0, size);
    }

    int count(int pos, int x, int lx, int rx){
        if(rx <= pos) return 0;
        if(lx >= pos) return v[x];
        int meio=(lx+rx)/2;
        return count(pos, 2*x+1, lx, meio) + count(pos, 2*x+2, meio, rx);
    }

    int count(int pos){
        return count(pos, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    segtree seg;
    seg.init(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        seg.set(x);
        cout << seg.count(x) << " ";
    } cout << endl;
    return 0;
}