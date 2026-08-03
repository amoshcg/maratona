#include <bits/stdc++.h>
using namespace std;

int main(){
    set<int> st;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int aux;
        cin >> aux;
        st.insert(aux);
        cout << "tamanho: " << st.size() << endl;
        cout << "valores: ";
        for(auto s:st) cout << s << " ";
        cout << endl << endl;
    }
}