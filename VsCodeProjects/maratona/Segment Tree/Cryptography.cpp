#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

int r;

vector<vector<int>> matrix_mult(vector<vector<int>> first, vector<vector<int>> second){
    vector<vector<int>> result(2, vector<int>(2));
    int a = first[0][0], b = first[0][1], c = first[1][0], d = first[1][1];
    int e = second[0][0], f = second[0][1], g = second[1][0], h = second[1][1];
    result[0][0] = (a * e + b * g)%r;
    result[1][0] = (c * e + d * g)%r;
    result[0][1] = (a * f + b * h)%r;
    result[1][1] = (c * f + d * h)%r;
    return result;
}

void print(vector<vector<int>> mat){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cout << mat[i][j]%r << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> read(){
    vector<vector<int>> mat(2,vector<int>(2));
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            cin >> mat[i][j];
        }
    }
    return mat;
}

struct segtree{
    vector<vector<vector<int>>> v;
    int size;
    vector<vector<int>> ident{{1,0},{0,1}};

    void init(int n){
        int i=1;
        while(i < n) i*=2;
        size = i;
        v.assign(2*i,ident);
    }

    void build(vector<vector<vector<int>>> &matrizes, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < matrizes.size()) v[x] = matrizes[lx];
            return;
        }
        int meio = (lx+rx)/2;
        build(matrizes, 2*x+1, lx, meio);
        build(matrizes, 2*x+2, meio, rx);
        v[x] = matrix_mult(v[2*x+1], v[2*x+2]);
    }

    void build(vector<vector<vector<int>>> &matrizes){
        build(matrizes, 0, 0, size);
    }

    vector<vector<int>> querie(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l) return ident;
        if(lx >= l && rx <= r) return v[x];
        int meio = (lx+rx)/2;
        return matrix_mult(querie(l, r, 2*x+1, lx, meio), querie(l, r, 2*x+2, meio, rx));
    }

    vector<vector<int>> querie(int l, int r){
        return querie(l, r, 0, 0, size);
    }
};

signed main(){
    int n, m;
    cin >> r >> n >> m;
    segtree seg;
    seg.init(n);
    vector<vector<vector<int>>> v(n, vector<vector<int>>(2, vector<int>(2)));
    for(int i=0;i<n;i++){
        v[i] = read();
    }

    seg.build(v);

    for(int i=0;i<m;i++){
        int l, r;
        cin >> l >> r;
        l--;
        print(seg.querie(l,r));
        cout << endl;
    }
    return 0;
}