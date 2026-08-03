#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

signed main(){
    long double x = 1, y = 1, z = 1;
    while(1){
        cin >> x >> y >> z;
        if(x == 0 && y == 0 && z == 0) return 0;
        if(z - y == y - x) cout << "AP " << z + z - y << endl;
        else cout << "GP " << z * (z / y) << endl;
    }
    return  0;
}