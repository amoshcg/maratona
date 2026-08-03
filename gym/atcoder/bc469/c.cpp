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
    vector<int> candie(n), vazio(n);
    
    candie[0] = s[0] == 'o';
    vazio[0] = s[0] == 'x';

    for(int i = 1; i < n; i++){
        candie[i] += candie[i - 1] + (s[i] == 'o');
        
        vazio[i] += vazio[i - 1] + (s[i] == 'x');
    }

    int cnt = 0;
    queue<int> bag;
    for(int i = 0 ; i < n; i++){

        bag.push(i);

        while(!bag.empty() && candie[bag.front()] <= vazio[i] - vazio[bag.front()]){
            cout << i + 1 << endl;
            bag.pop();
            cnt++;
        }
    }

    for(int i = 0; i < s.size() - cnt; i++) cout << s.size() << endl;
    return 0;
}

// Acaba quando o prefixo da posição é menor ou igual que o sufixo da posição