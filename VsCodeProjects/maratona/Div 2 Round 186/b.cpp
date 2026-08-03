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

int blk(int black, int white){
    int qnt = 1, type = 0, ans = 0;
    while(1){
        if(type){
            white -= qnt;
        } else {
            black -= qnt;
        }
        ans++;
        qnt *= 2;
        
        if(type && black < qnt) break;
        if(!type && white < qnt) break;
        type = !type;
    }
    return ans;
}

int whit(int black, int white){
    int qnt = 1, type = 1, ans = 0;
    while(1){
        if(type){
            white -= qnt;
        } else {
            black -= qnt;
        }
        ans++;
        qnt *= 2;
        
        if(type && black < qnt) break;
        if(!type && white < qnt) break;
        type = !type;
    }
    return ans;
}



signed main(){
    // fastio;
    int t;
    cin >> t;
    while(t--){
        int white, black;
        cin >> white >> black;
        cout << max(blk(black, white), whit(black, white)) << endl;
    }
    
    return 0;
}