#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
	return is >> p.first >> p.second;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
	for(auto& elem: v){
		is >> elem;
	}
	return is;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
	return os << "{" << p.first << ", " << p.second << "}";
}

template <typename T>
concept IterableContainer = requires(T t) {
	begin(t);
	end(t);
} && !same_as<T, string> && !same_as<T, string_view>;

template<IterableContainer Container>
ostream& operator<<(ostream& os, const Container& c) {
	os << "[";
	bool first = true;
	for(const auto& elem : c){
	if(!first) os << ", ";
 		os << elem;
		first = false;
	}
	return os << "]";
}

#define int long long
#define MOD (int)(1e9 + 7)

int bit(int n){
	int i = 0;
	while(abs(n / 2) > 0){
		i++;
		n /= 2;
	}
	return i;
}

int bintodec(int bit){
	int ans = 1;
	for(int i = 0; i < bit; i++){
		ans *= 2;
		ans %= MOD;
	}
	return ans;
}

signed main(){
	int n;
	cin >> n;
	vector<int> v(n);
	cin >> v;
	int ans = 0, acc = 0, neg = -1, qnt = 0;
	for(int i = 0; i < n; i++){

		if (v[i] == 0) {
			acc = 0;
			neg = -1;
			qnt = 0;
			continue;
		}
		
		int val = bit(v[i]);

		// Negativo
		if (v[i] < 0){ // Se for negativo

			if(neg == -1){ // Se for o primeiro negativo
				neg = acc + val; // guardo o prefixo
			}

			qnt++;
		}


		
		acc += val;
		ans = max(ans, (qnt & 1 ? acc - neg : acc));

		cout << acc << endl;
	}
	cout << bintodec(ans) << endl;
	return 0;
}