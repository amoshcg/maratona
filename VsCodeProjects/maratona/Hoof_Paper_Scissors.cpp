#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

signed main(){
    int n, k;
    cin >> n >> k;
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k, vector<int>(3)));
    for(int i = 0; i < n; i++){
        char c; cin >> c;
        for(int j = 0; j < k; j++){
            if(c == 'P'){
                // Aqui ele ganha nao faz sentido trocar
                dp[i][j][0] = dp[i-1][j][0] + 1;
                dp[i][j][0]
                // Aqui ele perde
                dp[i][j][1] = dp[i-1][j][1];
                // Aqui ele perde
                dp[i][j][2] = dp[i-1][j][2];
            }
        }

    }
}

// Posso escolher P, H ou S
// No comeco posso escolher max()