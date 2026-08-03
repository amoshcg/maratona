#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

int tamanho(int a){
    int i = 1;
    while(a /= 10){
        i *= 10;
    }
    return i;
}

int reverse(int a){
    int x = 0, i = tamanho(a);
    while(a){
        x += (a % 10) * i;
        a /= 10;
        i /= 10;
    }
    return x;
}

signed main(){
    fastio;
    int t;
    cin >> t;
    while(t--){
        int a, b;
        cin >> a >> b;
        cout << reverse(reverse(a) + reverse(b)) << endl;

    }
    return 0;
}