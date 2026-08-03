#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

int solve(vector<int> &v, int pos = 0, int A = 0, int B = 0){
    if(pos == v.size()) return abs(A - B);
    return min(solve(v, pos+1, A + v[pos], B), solve(v, pos+1, A, B + v[pos]));
}

signed main(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &w:v) cin >> w;
    cout << solve(v) << endl;
    return 0;
}