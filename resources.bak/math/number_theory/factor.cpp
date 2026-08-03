#include<bits/stdc++.h>
using namespace std;

vector<long long> factor(long long n){
	vector<long long> ans;
	for(int i = 2; i * i <= n; i++){
		while(n % i == 0){
			n /= i;
			ans.push_back(i);
		}
	}
	if(n != 1) ans.push_back(n);
	return ans;
}

int main(){
	long long n;
	cin >> n;
	for(auto &ans:factor(n)) cout << ans << " ";
	cout << endl;
	return 0;
}
