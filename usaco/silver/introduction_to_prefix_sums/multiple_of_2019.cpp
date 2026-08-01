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
} && !is_convertible_v<T, string_view>;

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

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double
#define endl '\n'

const int MOD = 2019;

signed main(){
	// fastio;
	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	vector<int> suffix(MOD);
	int value = 0, power = 1, ans = 0;
	suffix[value]++;
	for(int i = 0; i < s.size(); i++){
		int digit = s[i] - '0';
		value = (value + digit * power) % MOD;
		power = 10 * power % MOD;
		ans += suffix[value];
		suffix[value]++;
	}
	cout << ans << endl;
	return 0;
}
