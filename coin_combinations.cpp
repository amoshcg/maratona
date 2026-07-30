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

const int MOD = 1e9 + 7;

signed main(){
    fastio;
    int n, x;
    cin >> n >> x;
    vector<int> dp(x+1), coins(n);
    for(auto &c:coins) cin >> c;

    sort(coins.begin(), coins.end());

    dp[0] = 1;
    for(int c = 0; c < n; c++){
        for(int i = 0; i <= x; i++){
            if(i + coins[c] <= x){
                dp[i + coins[c]] += dp[i];
                dp[i + coins[c]] %= MOD;
            }
        }
    }

    cout << dp[x] << endl;
    return 0;
}
