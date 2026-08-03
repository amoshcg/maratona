#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()

struct segtree{
    vector<vector<int>> max_sums;
    int size;

    void init(int n){
        int i=1;
        while(i < n) i*=2;
        max_sums.assign(2*i, vector<int>(4,0));
        size = i;
    }

    void set(int pos, int val, int x, int lx, int rx){
        if(rx-lx==1){
            max_sums[x]={val,val,val,val};
            return;
        }
        int meio = (rx + lx)/2;
        vector<int> &esq = max_sums[2*x+1], &dir = max_sums[2*x+2];
        if(pos < meio) set(pos,val,2*x+1,lx,meio);
        else set(pos,val,2*x+2,meio,rx);
        max_sums[x] =  {max({esq[0],dir[0],esq[3]+dir[2]}), esq[1]+dir[1], max(esq[2], esq[1]+dir[2]), max(dir[3], dir[1]+esq[3])};
    }

    int set(int pos, int val){
        set(pos, val, 0, 0, size);
        return max(max_sums[0][0],0LL);
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
    segtree seg;
    seg.init(n);
    for(int i=0;i<n;i++){
        int val;
        cin >> val;
        seg.set(i,val);
    }

    cout << max(seg.max_sums.front().front(),0LL) << endl;

    for(int i=0;i<m;i++){
        int pos, val;
        cin >> pos >> val;
        cout << seg.set(pos,val) << endl;
    }

    return 0;
}