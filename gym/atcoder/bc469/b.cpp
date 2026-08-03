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

signed main(){
    fastio;
    int n;
    string s;
    cin >> n >> s;
    int ans = 0;
    for(int i = 0; i < n; i++){
        bool empty = true;
        if(i - 1 >= 0 && s[i - 1] == 'o') empty = false;
        if(i + 1 < s.size() && s[i + 1] == 'o') empty = false;
        if(s[i] == 'o') empty = false;
        if(empty) ans++;
    }
    cout << ans << endl;
    return 0;
}