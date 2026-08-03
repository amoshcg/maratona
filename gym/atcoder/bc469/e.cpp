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
    int n, k;
    string s;
    cin >> n >> k >> s;
    
    ld o = 0, x = 0;
    ld ans = 0;

    int j = 0;
    for(int i = 0; i < n; i++){

        if(s[i] == 'o') o++;
        else x++;

        // cout << j << " " << i << endl;

        // cout << o << " " << x << " "  << (ld)o / ((ld)o + x) << endl;

        if(o >= k) {
            ans = max(ans, (ld) o / (o + x));
            // cout << "agora sim" << endl;
        }
    }
    for(; j < n; j++){
        
        if(s[j] == 'o') o--;
        else x--;
        
        if(o >= k) {
            ans = max(ans, (ld) o / (o + x));
            // cout << "agora sim" << endl;
        }
    }
    
    cout << fixed << setprecision(30) << ans << endl;
    return 0;
}