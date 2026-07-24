#include <bits/stdc++.h>
using namespace std;

int query(int r){
    int sum;
    cout << "? " << 1 << " " << r << endl;
    cin >> sum;
    return r - sum;
}

int main(){
    int n, t, k;
    cin >> n >> t >> k;
    int max_q = 1;
    while(2 * max_q < n) max_q *= 2;
    int l = 0;
    for(int i = max_q; i >= 1; i /= 2){
        if(l + i > n) continue;
        if(query(l + i) < k) l += i;
    }
    cout << "! " << l + 1 << endl;
}