#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define endl '\n'
#define int long long
#define ld long double
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)


int nxt(){
    int x; cin >> x;
    return x;
}

int _2025(string &s){
    int qnt = 0;
    string seq = "2025";
    for(int i = 0, j = 0; i < s.size(); i++){
        if(s[i] == seq[j]){
            j++;
            if(j == seq.size()){
                j = 0;
                qnt++;
            }
        } else {
            j = 0;
        }
    }
    return qnt;
}

int _2026(string &s){
    int qnt = 0;
    string seq = "2026";
    for(int i = 0, j = 0; i < s.size(); i++){
        if(s[i] == seq[j]){
            j++;
            if(j == seq.size()){
                j = 0;
                qnt++;
            }
        } else {
            j = 0;
        }
    }
    return qnt;
}


signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n >> s;
        if(s.find("2025") == string::npos || s.find("2026") != string::npos) cout << 0 << endl;
        else cout << 1 << endl;
    }
    
    return 0;
}