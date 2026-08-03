#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

struct segtree{
    int size;
    vector<int> brackets;
    vector<int> prefix_min;

    void init(int n){
        int i = 1;
        while(i < n) i *= 2;
        size = i;
        brackets.assign(2* size, 0);
        prefix_min.assign(2*size, 0);
    }

    void build(vector<int> &v, int lx, int rx, int x){
        if(rx - lx == 1){
            if(lx < v.size()) {
                brackets[x] = v[lx];
                prefix_min[x] = v[lx];
            }
            return;
        }
        int meio = (rx + lx) / 2;
        build(v, lx, meio, 2*x+1);
        build(v, meio, rx, 2*x+2);
        brackets[x] = brackets[2*x+1] + brackets[2*x+2];
        // O prefixo do intervalo a esquerda ou todo o intervalo a esquerda mais o prefixo da direita
        prefix_min[x] = min(prefix_min[2*x+1], brackets[2*x+1] + prefix_min[2*x+2]);
    }

    void build(vector<int> &v){
        build(v, 0, size, 0);
    }

    void update(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l) return;
        if(lx >= l && rx <= r) {
            brackets[x] *= -1;
            prefix_min[x] *= -1;
            return;
        }
        int meio = (rx + lx) / 2;
        update(l, r, 2*x+1, lx, meio);
        update(l, r, 2*x+2, meio, rx);
        brackets[x] = brackets[2*x+1] + brackets[2*x+2];
        prefix_min[x] = min(prefix_min[2*x+1], brackets[2*x+1] + prefix_min[2*x+2]);
    }

    void update(int pos){
        update(pos, pos+1, 0, 0, size);
    }

    bool check(){
        if(prefix_min[0] >= 0 && brackets[0] == 0) return true;
        return false;
    }

    void print(){
        for(int i = 0; i < 2*size - 1; i++){
            cout << "imprime" << endl;
            cout << brackets[i] << " ";
        }
        cout << endl;
    }

};

signed main(){
    for(int i = 0; i < 10; i++){
        cout << "Test " << i+1 << ":" << endl;
        int n;
        cin >> n;
        segtree seg;
        seg.init(n);
        vector<int> v(n);
        for(int j = 0; j < n; j++){
            char c;
            cin >> c;
            if(c == ')') v[j] = -1;
            else v[j] = 1;
        }
        seg.build(v);

        // seg.print();

        int m;
        cin >> m;
        for(int j = 0; j < m; j++){
            int op;
            cin >> op;
            if(op){
                seg.update(op-1);
            } else {
                if(seg.check()) cout << "YES" << endl;
                else cout << "NO" << endl;
            }
            // seg.print();
        }
    }
}