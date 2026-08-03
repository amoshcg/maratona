#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> v;
vector<vector<int>> permutacoes;

void gerar_permutacoes(vector<bool> escolhido, vector<int> perm = {}){
    if (perm.size() ==  n) {
        permutacoes.push_back(perm);
        return;
    }
    else {
        for(int i = 0; i < n; i++){
            if (escolhido[i]) continue;
            escolhido[i] = true;
            perm.push_back(v[i]);
            gerar_permutacoes(escolhido, perm);
            escolhido[i] = false;
            perm.pop_back();
        }
    }
}

int main(){
    cin >> n;
    v.resize(n, 0);
    for(auto &w:v) cin >> w;
    vector<bool> escolhido(n, false);
    gerar_permutacoes(escolhido);
    cout << endl << endl;
    for(auto perm:permutacoes){
        for(auto p:perm){
            cout << p << " ";
        }
        cout << endl;
    }
    return 0;
}