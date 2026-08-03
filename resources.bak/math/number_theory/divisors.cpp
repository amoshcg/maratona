#include<bits/stdc++.h>
using namespace std;

// Factor (mathematical definition): a whole number that divides another number evenly, without leaving a remainder

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

// Why taking all the i's and n / i works:
// The assumption: Let a and b be a factor pair of n, meaning a * b = n.
// The hyphotesis: Imagine if both a and b were strictly greater sqrt(n).
// The contradiction: if a > sqrt(n) and b > sqrt(n), then multiplying together would mean a * b > sqrt(n) * sqrt(n).
// This simplifies to a * b > n.
// Since we know that a * b must equal n, it is mathematically impossible for them to be greater than n.
// Therefore, our hypothesis is false: they cannot both be larger than sqrt(n).

// If n is a perfect square then the condition if(n / i != i) removes the duplicate n

// Fun fact: if n is not a perfect square then there are two times the number of divisors that are less than sqrt(n)
// Therefore every perfect square has an odd number of divisors
int main(){
	long long n;
	cin >> n;
	for(auto &ans:divisors(n)) cout << ans << " ";
	cout << endl;
	return 0;
}
