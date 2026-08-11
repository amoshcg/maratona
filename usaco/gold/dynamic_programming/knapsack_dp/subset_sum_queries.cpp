#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
    return is >> p.first >> p.second;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& elem: v){
        is >> elem;
    }
    return is;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
    return os << "{" << p.first << ", " << p.second << "}";
}

template <typename T>
concept IterableContainer = requires(T t) {
    begin(t);
    end(t);
} && !is_convertible_v<T, string_view>;

template<IterableContainer Container>

ostream& operator<<(ostream& os, const Container& c) {
    os << "[";
    bool first = true;
    for(const auto& elem : c){
    if(!first) os << ", ";
        os << elem;
        first = false;
    }
    return os << "]";
}

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double
#define endl '\n'

const int MOD = 998244353;

// signed main(){
//     fastio;
//     int q, k;
//     cin >> q >> k;
//     vector<int> dp(k + 1);
//     dp[0] = 1;
//     while(q--){
//         char op;
//         int x;
//         cin >> op >> x;
//         if(op == '-'){
//             for(int i = 0; i <= k; i++){
//                 if(i - x >= 0) dp[i] = (dp[i] + MOD - dp[i - x]) % MOD;
//             }
//         } else {
//             for(int i = k; i >= 0; i--){
//                 if(i - x >= 0) dp[i] = (dp[i] + dp[i -x]) % MOD;
//             }
//         }
//         cout << dp[k] << endl;
//     }
//     return 0;
// }

signed main(){
    int q, k;
    cin >> q >> k;
    vector<int> dp(k + 1);
    dp[0] = 1;
    while(q--){
        char op;
        int val;
        cin >> op >> val;
        
        if(op == '+'){
            for(int i = k; i >= 0; i--){
                if(i - val >= 0) dp[i] = (dp[i] + dp[i - val]) % MOD;
            }
        } else {
            for(int i = 0; i <= k; i++){
                if(i - val >= 0) dp[i] = (MOD + dp[i] - dp[i - val]) % MOD;
            }
        }
        cout << dp[k] << endl;
    }
}