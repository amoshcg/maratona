#include <bits/stdc++.h>
using namespace std;

// Variaveis globais
int n;
vector<int> v;
vector<vector<int>> subconjuntos;

void gerar_subconjuntos(int k = 0, vector<int> sub = {}){
    if (k == n){
        subconjuntos.push_back(sub);
    } else {
        sub.push_back(v[k]);
        gerar_subconjuntos(k+1, sub);
        sub.pop_back();
        gerar_subconjuntos(k+1, sub);
    }
}

int main(){
    cin >> n;
    v.resize(n, 0);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    gerar_subconjuntos();
    cout << endl << endl;
    for(auto sub:subconjuntos){
        for(auto s:sub){
            cout << s << " ";
        }
        cout << endl;
    }

}