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

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double

int kadane(vector<int> const &v){
	int ans = -1e9;
	int curr = -1e9;
	for(int i = 0; i < v.size(); i++){
		if(curr + v[i] > v[i]) curr += v[i];
		else curr = v[i];
		ans = max(ans, curr);
	}
	return ans;
}

signed main(){
	fastio;
	int n;
	cin >> n;
	vector<int> v(n);
	cin >> v;
	cout << kadane(v) << endl;

	return 0;
}
