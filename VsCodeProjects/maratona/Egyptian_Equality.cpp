#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int count(vector<vector<char>> &v){
    int total = 0;
    for(auto &w:v){
        for(auto &z:w){
            if(z == 'C') total++;
        }
    }
    return total;
}

bool edge_case(vector<vector<char>> &v){
    int n = v.size();
    int m = v[0].size();
    if(v[n-1][m-1] == 'c' && v[n-1][m-2] == 'c' && v[n-1][0] == 'c' && v[n-1][1]){
        return true;
    }
    return false;
}

int last_count(vector<vector<char>> &v){
    int total = 0;
    int n = v.size();
    for(auto &w:v[n-1]){
        if(w == 'c') total++;
    }
    return total;
}   


signed main(){
    fastio;
    int n;
    cin >> n;
    vector<vector<char>> v(n, vector<char>(2*n-1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2*n-1; j++){
            cin >> v[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2*n-1; j++){
            cout << v[i][j];
        }
        cout << endl;
    }

    if(count(v) & 1){
        cout << "impossible" << endl;
        return 0;
    }

    cout << count(v) << endl;
    return 0;
}