#include <bits/stdc++.h>
using namespace std;

void ao_contrario(vector<int> &v, int pos = 0){
    if (pos == v.size()) return; // Caso base
    else {
        ao_contrario(v, pos+1);
        cout << v[pos] << " ";
    }
}

void imprimir(vector<int> &v, int pos = 0){ // Passagem por endereço e parâmetro sem argumento
    if(pos == v.size()) return; // Caso base
    else {
        cout << v[pos] << " ";
        imprimir(v, pos+1);
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    imprimir(v);
    cout << endl;

    ao_contrario(v);
    cout << endl;
    return 0;
}

// Explicar return void
// Explicar passagem de argumento por endereço ou cópia
// Explicar atribuição de parâmetros sem argumentos
