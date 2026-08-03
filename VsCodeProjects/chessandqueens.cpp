#include <bits/stdc++.h>
using namespace std;

int ans = 0;
vector<vector<int>> v;

void solve(int y, vector<bool> column, vector<bool> diag1, vector<bool> diag2){
    if (y == 8) {
        ans++;
        return;
    }
    for(int x = 0; x < 8; x++){
        if (v[y][x] == 1 || column[x] || diag2[x + y] || diag1[x - y + 15]) continue;
        column[x] = diag1[x - y + 15] = diag2[x + y] = true;
        solve(y + 1, column, diag1, diag2);
        column[x] = diag1[x - y + 15] = diag2[x + y] = false;
    }
}

int main(){
    v.resize(8, vector<int>(8, 0));
    vector<bool> diag1(31, false);
    vector<bool> diag2(31, false);
    vector<bool> column(8, false);

    for(int i = 0; i < 8; i++){ 
        for(int j = 0; j < 8; j++){
            char aux;
            cin >> aux;
            if (aux == '*') {
                v[i][j] = 1;  // mark as blocked
            }
        }
    }

    solve(0, column, diag1, diag2);
    cout << ans << endl;
    return 0;
}
