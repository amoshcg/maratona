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
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 0; i < n; i++){
        for(int dice = 1; dice <= 6; dice++){
            if(i + dice <= n) {
                dp[i + dice] += dp[i];
                dp[i + dice] %= MOD;
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}
