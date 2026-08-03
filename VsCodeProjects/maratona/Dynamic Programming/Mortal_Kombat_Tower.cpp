#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

const int INF = 1e8;

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> hard(n);
        for(int i = 0; i < n; i++){
            cin >> hard[i];
        }

        // Guardo de quem e a vez e quantas vezes foi jogado
        // boss, de quem e a vez e quantas vezes ja foi jogado
        // 0 eu e 1 meu amigo
        int dp[n+1][2];

        for(int i = 0; i <= n; i++){
            for(int j = 0; j < 2; j++){
                dp[i][j] = INF;
            }
        }

        dp[0][1] = 0;

        for(int i = 0; i < n; i++){
            dp[i+1][1] = min(dp[i+1][1], dp[i][0]);
            dp[i+1][0] = min(dp[i+1][0], dp[i][1] + hard[i]);

            if(i + 2 <= n){
                dp[i+2][1] = min(dp[i+2][1], dp[i][0]);
                dp[i+2][0] = min(dp[i+2][0], dp[i][1] + hard[i] + hard[i+1]);
            }
        }
        cout << min(dp[n][1], dp[n][0]) << endl;
    }

    return 0;
}