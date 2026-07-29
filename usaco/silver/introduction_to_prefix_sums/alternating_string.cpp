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

// signed main(){
//     fastio;
//     int t;
//     cin >> t;

//     while(t--){
//         int n;
//         cin >> n;
//         string s;
//         cin >> s;
//         vector<vector<int>> pref_odd(n+1, vector<int>(26)), pref_even(n+1, vector<int>(26));
//         vector<vector<int>> suff_odd(n+1, vector<int>(26)), suff_even(n+1, vector<int>(26));

//         for(int i = 0; i < n; i++){
//             pref_odd[i+1] = pref_odd[i];
//             pref_even[i+1] = pref_even[i];
//             int atual = s[i] - 'a';
//             if(i % 2 == 0) pref_even[i+1][atual]++;  
//             else pref_odd[i+1][atual]++;
//         }

//         for(int i = n - 1; i >= 0; i--){
//             suff_odd[i] = suff_odd[i+1];
//             suff_even[i] = suff_even[i+1];
//             int atual = s[i] - 'a';
//             if(i % 2 == 0) suff_even[i][atual]++;
//             else suff_odd[i][atual]++;
//         }

//         if(n % 2 == 0){
//             int max_a = 0, max_b = 0;
//             for(int i = 0; i < 26; i++){
//                 max_a = max(max_a, pref_even[n][i]);
//                 max_b = max(max_b, pref_odd[n][i]);
//             }
//             cout << n - max_a - max_b << endl;
//         } else {
//             int ans = 1e9;
//             for(int i = 0; i < n; i++){
//                 int atual = s[i] - 'a';
//                 int max_a = 0, max_b = 0;
//                 for(int j = 0; j < 26; j++){
//                     if(i % 2 == 0) max_a = max(max_a, pref_odd[i][j] + suff_even[i+1][j]);
//                     else max_a = max(max_a, pref_even[i][j] + suff_odd[i+1][j]);
//                 }
//                 for(int j = 0; j < 26; j++){
//                     if(i % 2 == 0) max_b = max(max_b, pref_even[i][j] + suff_odd[i+1][j]);
//                     else max_b = max(max_b, pref_odd[i][j] + suff_even[i+1][j]);
//                 }
//                 ans = min(ans, n - max_a - max_b);
//             }
//             cout << ans << endl;
//         }
//     }
//     return 0;
// }

// Para problemas onde é necessário ignorar uma posição do array
// É mais fácil em vem de calcular o prefixo e sufixo antes,
// calcular o total no sufixo e depois ir incrementando o prefixo e decrementando o sufixo
// Isso também otimiza o uso de memória, nesse problema vai de 2e5 * 26 para 26

signed main(){
    fastio;
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<vector<int>> prefix(2, vector<int>(26));
        vector<vector<int>> suffix(2, vector<int>(26));

        for(int i = 0; i < n; i++) suffix[i % 2][s[i] - 'a']++;

        if(n % 2 == 0){
            int max_a = 0, max_b = 0;
            for(int i = 0; i < 26; i++){
                max_a = max(max_a, suffix[0][i]);
                max_b = max(max_b, suffix[1][i]);
            }
            cout << n - max_a - max_b << endl;
        } else {
            int ans = 1e9;
            for(int i = 0; i < n; i++){
                int max_a = 0, max_b = 0;
                suffix[i % 2][s[i] - 'a']--;
                for(int j = 0; j < 26; j++){
                    max_a = max(max_a, prefix[0][j] + suffix[1][j]);
                    max_b = max(max_b, prefix[1][j] + suffix[0][j]);
                }
                prefix[i % 2][s[i] - 'a']++;
                ans = min(ans, n - max_a - max_b);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
