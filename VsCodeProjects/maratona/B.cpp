// Problem: B. Even Modulo Pair
// Contest: Codeforces - Codeforces Global Round 30 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2164/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

void solve(vector<int>v){
	int n=v.size();
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if((v[j]%v[i])%2==0){
				cout << v[i] << " " << v[j] << endl;
				return;
			}
		}			
	}
	cout << "-1" << endl;
}

signed main(){
	int t; cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int>v(n);
		for(int i=0;i<n;i++){
			cin >> v[i];
		}
		solve(v);
    }
    return 0;
}