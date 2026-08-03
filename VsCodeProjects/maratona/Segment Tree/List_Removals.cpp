#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct segtree{
    int size;
    vector<int> kth;
    vector<int> val;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        kth.assign(2*i, 0);
        val.resize(n);
    }

    void build(int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < val.size()) kth[x] = 1;
            return;
        }
        int meio = (rx + lx) / 2;
        build(2*x+1, lx, meio);
        build(2*x+2, meio, rx);
        kth[x] = kth[2*x+1] + kth[2*x+2];
    }

    void build(){
        build(0, 0, size);
    }

    int get_kth(int pos, int x, int lx, int rx){
        if(rx - lx == 1) {
            kth[x] = 0;
            return val[lx];
        }
        int meio = (rx + lx) / 2;
        int ans;
        if(pos <= kth[2*x+1]) ans = get_kth(pos, 2*x+1, lx, meio);
        else ans = get_kth(pos - kth[2*x+1], 2*x+2, meio, rx);
        kth[x] = kth[2*x+1] + kth[2*x+2];
        return ans;
    }

    int get_kth(int pos){
        return get_kth(pos, 0, 0, size);
    }
};

signed main(){
    int n;
    cin >> n;
    segtree seg;
    seg.init(n);
    seg.build();
    for(int i = 0; i < n; i++){
        cin >> seg.val[i];
    }
    for(int i = 0; i < n; i++){
        int pos;
        cin >> pos;
        cout << seg.get_kth(pos) << " ";
    }
    cout << endl;
    return 0;
}