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

// Aqui vamos chutar um valor M para a maior probabilidade possível
// Isso gera um erro de 'o' / ('o' + 'x') - M = 0
// 'o' = M * ('o' + 'x')
// 'o' = M * 'o' + M * 'x'
// 'o' - M * 'o' - M * 'x' = 0
// 'o' * (1 - M) + 'x' * (-M) = o
// quando s[i] for 'o', então 'o' é 1 e 'x' é 0
// Então sobra 1 - M
// quando s[i] for 'x', entao 'o' e 0 e 'x' e 1
// Entao sobra - M
// Se substituirmos cada posição por esses valores,
// O somatório se torna a probabilidade do intervalo
// Agora é só achar o mínimo desse intervalo
// Então, faz-se uma busca binária com o valor M

// Para calcular usamos a soma de prefixos para descobrir o menor intervalo
// encontramos o melhor l (menor possivel)
// E calculamos para todo r
// Basicamente removemos um prefixo para toda posicao

// Caso a diferença seja >= 0, então aumentamos M
// Caso contrário diminuimos M

ld calculate(string &s, ld m, int k){
    vector<ld> prefix(s.size() + 1);
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'o') prefix[i + 1] = prefix[i] + 1 - m;
        else prefix[i + 1] = prefix[i] - m;
    }

    // cout << prefix << endl;

    ld melhor = 0, ans = 0, acertos = 0;
    for(int i = 1, j = 1; i < s.size() + 1; i++){

        if(s[i - 1] == 'o') acertos++;
        
        // Aqui podemos encontrar o melhor prefixo
        while(acertos > k || j - 1 < i && s[j - 1] == 'x'){

            melhor = min(melhor, prefix[j]);

            if(s[j - 1] == 'o') acertos--;
            j++;
            // cout << j << endl;
        }

        if(acertos >= k) ans = max(ans, prefix[i] - melhor);
        
        
        // cout << fixed << setprecision(30) << melhor << " " << j << " " << ans << endl;
    }
    // cout << ans << endl;
    return ans;
}

signed main(){
    fastio;
    int n, k;
    string s;
    cin >> n >> k >> s;
    // calculate(s, 0.875, k);

    ld esq = 0, dir = 1, meio = 0.5, val;
    for(int i = 0; i < 70; i++){
        // cout << "meio " << meio << endl;
        val = calculate(s, meio, k);
        if(val > 0){
            esq = meio;
        } else {
            dir = meio;
        }
        meio = (esq + dir) / (ld)2;
        // cout << " " << val << endl;
    }

    cout << fixed << setprecision(30) << meio << endl;
    return 0;
}