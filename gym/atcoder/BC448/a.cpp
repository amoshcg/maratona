#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    for(int i = 0; i < n; i++){
        if(v[i] < x){
            cout << 1 << endl;
            x = v[i];
        } else {
            cout << 0 << endl;
        }
    }
}