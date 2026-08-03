#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)

const int INF = 1e18;

signed main(){
    fastio;
    int n, total;
    cin >> n >> total;
    vector<int> v(n+1, 0), original(n);
    for(int i = 1; i <= n; i++){
        cin >> v[i];
        original[i-1] = v[i];
    }

    sort(all(v));
    
    vector<vector<int>> dp(total+1, vector<int>(n+1, INF));

    dp[0][0] = 0;
    for(int i = 1; i < n+1; i++){
        int acc = 0;
        for(int j = i; j > 0; j--){
            acc += (v[i] - v[j]) * (v[i] - v[j]);
        }
        dp[0][i] = acc;
    }
    
    for(int k = 1; k < total; k++){
        for(int i = k + 1; i <= n; i++){
            int acc = 0;
            for(int j = i - 1; j >= k; j--){
                acc += (v[i] - v[j+1]) * (v[i] - v[j+1]);
                dp[k][i] = min(dp[k][i], dp[k-1][j] + acc);
            }
        }
    }

    vector<int> dias;
    dias.push_back(v[n]);
    int pos = n;

    for(int k = total - 2; k >= 0; k--){
        int acc = 0;
        for(int j = pos - 1; j >= k + 1; j--){
            if(dp[k+1][pos] == dp[k][j] + acc){
                pos = j;
                dias.push_back(v[pos]);
                break;
            }
            acc += (v[pos] - v[j]) * (v[pos] - v[j]);
        }
    }

    reverse(all(dias));

    for(int i = 0; i < n; i++){
        int j = 0;
        while(dias[j] < original[i]) j++;
        cout << dias[j] << " ";
    }
    cout << endl;
}