#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    cin >> s;
    vector<stack<int>> pilha(3);
    int ans = 0;
    for(int i = 0; i < s.size(); i++){
        pilha[s[i] - 'A'].push(i);
    }
    while(true){
        if(pilha[0].empty() && pilha[1].empty()) break;
        while(!pilha[1].empty() && pilha[1].top() > pilha[2].top()) pilha[1].pop();
        while(!pilha[0].empty() && pilha[0].top() > pilha[1].top()) pilha[0].pop();
        for(auto &p:pilha) {
            if(p.empty()) {
                cout << ans << endl;
                return 0;
            }
        }
        for(auto &p:pilha) p.pop();
        ans++;
    }
    cout << ans << endl;
}