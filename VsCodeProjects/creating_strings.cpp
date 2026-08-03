#include<bits/stdc++.h>
using namespace std;

string s;
set<string> mt_s;
vector<string> mt;
int cnt = 0;

void create_strings(vector<bool> escolhido, string aux = {}){
    if (aux.size() == s.size()) {
        cnt++;
        mt_s.insert(aux);
        return;
    }
    else {
        for(int i = 0; i < s.size(); i++){
            if(escolhido[i]) continue;
            escolhido[i] = true;
            aux.push_back(s[i]);
            create_strings(escolhido, aux);
            aux.pop_back();
            escolhido[i] = false;
        }
    }
}

void create_strings_rep(vector<bool> escolhido, string aux = {}){
    if (aux.size() == s.size()) {
        cnt++;
        mt.push_back(aux);
        return;
    }
    else {
        for(int i = 0; i < s.size(); i++){
            if(escolhido[i]) continue;
            escolhido[i] = true;
            aux.push_back(s[i]);
            create_strings(escolhido, aux);
            aux.pop_back();
            escolhido[i] = false;
        }
    }
}

int main(){
    cin >> s;
    vector<bool> escolhido(s.size(), false);
    

    // Usando o vector
    create_strings_rep(escolhido);
    cout << mt.size() << endl;
    for(auto m:mt) cout << m << endl;


    // Usando o set
    // create_strings(escolhido);
    // cout << mt_s.size() << endl;
    // for(auto m:mt_s) cout << m << endl;
    return 0;
}