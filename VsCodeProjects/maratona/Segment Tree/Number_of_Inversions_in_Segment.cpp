#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct quarenta{
    int v[40], size=0;
    quarenta(){
        for(int i=0;i<40;i++) v[i] = 0;
    }
};

struct segtree{
    int v[262144][40]{};
    int inv[262144]{};
    int size;

    void init(int n){
        int qnt=1;
        while(qnt<n) qnt*=2;
        size = qnt;
    }

    void build(vector<int> &a, int x, int lx, int rx){
        // cout << x << " " << lx << " " << rx << endl;
        if(rx - lx == 1) {
            if(lx < a.size()) v[x][a[lx]-1]++;
            return;
        }
        // if(rx - lx == 4) return;
        int meio = (lx + rx) / 2;
        build(a, 2*x+1, lx, meio);
        build(a, 2*x+2, meio, rx);
        // cout << "bb" << endl;
        
        

        int dir = 0;
        for(int i=0;i<40;i++){

            inv[x] += v[2*x+1][i] * dir;

            dir += v[2*x+2][i];
            
            v[x][i] = v[2*x+1][i] + v[2*x+2][i];
        }
        inv[x] += inv[2*x+1] + inv[2*x+2];
    }

    void build(vector<int> a){
        build(a, 0LL, 0LL, size);
    }

    void update(int pos, int val, int ant, int x, int lx, int rx){
        if(rx - lx == 1){
            v[x][val]++;
            v[x][ant]--;
            return;
        }

        int meio = (rx+lx)/2;
        if(pos < meio) {
            update(pos, val, ant, 2*x+1, lx, meio);
        }
        else update(pos, val, ant, 2*x+2, meio, rx);

        int dir = 0; inv[x] = 0;
        for(int i=0;i<40;i++){
            inv[x] += v[2*x+1][i] * dir;
            dir += v[2*x+2][i];
            v[x][i] = v[2*x+1][i] + v[2*x+2][i];
        }
        inv[x] += inv[2*x+1] + inv[2*x+2];
    }

    void update(int pos, int val, int ant){
        update(pos, val, ant, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx,  quarenta &q){
        if(rx <= l || lx >= r) return 0;
        if(lx >= l && rx <= r) {
            int dir = 0, soma = 0;
            for(int i=0;i<40;i++){
                soma += v[x][i] * dir;
                dir += q.v[i];
            }
            for(int i=0;i<40;i++){
                q.v[i] += v[x][i];
            }
            return inv[x] + soma;
        }
        int meio = (lx + rx) / 2;
        return query(l, r, 2*x+2, meio, rx, q) + query(l, r, 2*x+1, lx, meio, q);
    }

    int query(int l, int r){
        quarenta q = quarenta();
        return query(l, r, 0, 0, size, q);
    }
};

signed main(){
    int n, q;
    cin >> n >> q;

    segtree seg;
    seg.init(n);

    vector<int> v(n);

    for(int i=0;i<n;i++){
        cin >> v[i];
    }

    seg.build(v);

    // for(int i=0;i<seg.size;i++){
    //     for(int j=0;j<40;j++){
    //         cout << seg.v[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // for(int i=0;i<2*seg.size;i++){
    //     cout << seg.inv[i] << " ";
    // }
    // cout << endl;

    for(int i=0;i<q;i++){
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1){
            cout << seg.query(x-1,y) << endl;
        } else {
            seg.update(x-1, y-1, v[x-1]-1);
            v[x-1] = y;
        }
    }

    // for(int i=0;i<seg.size;i++){
    //     for(int j=0;j<40;j++){
    //         cout << seg.v[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // for(int i=0;i<2*seg.size;i++){
    //     cout << seg.inv[i] << " ";
    // }
    // cout << endl;
    return 0;
}