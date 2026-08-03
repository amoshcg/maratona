#include <bits/stdc++.h>
using namespace std;

vector<int> factor(int n){
	vector<int> v;
	for(int i = 2; i * i <= n; i++){
		while(n % i == 0){
			n /= i;
			v.push_back(i);
		}
	}
	if(n != 1) v.push_back(aux);
	return v;
}

vector<int> divisors(int n){
	vector<int> v;
	for(int i = 1; i * i <= n; i++){
		if(n % i == 0) {
			v.push_back(i);
			if (n / i != i) {
                		v.push_back(n / i);
            		}
		}
	}
	sort(v.begin(), v.end());
	return v;
}

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a % b);
}

int lcm(int a, int b){
	return (a / gcd(a, b)) * b;
}

int main(){
	int a, b;
	cin >> a >> b;
	for(auto &f:factor(a)) cout << f << " ";
	cout << endl;
	// cout << gcd(a, b) << " " << lcm(a, b) << endl;
	return 0;
}
