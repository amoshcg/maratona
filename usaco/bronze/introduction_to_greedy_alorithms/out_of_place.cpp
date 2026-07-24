#include <bits/stdc++.h>
using namespace std;

// template <typename T, typename U>
// istream& operator>>(istream& is, pair<T, U>& p) {
// 	return is >> p.first >> p.second;
// }

// template <typename T>
// istream& operator>>(istream& is, vector<T>& v) {
// 	for(auto& elem: v){
// 		is >> elem;
// 	}
// 	return is;
// }

// template <typename T, typename U>
// ostream& operator<<(ostream& os, const std::pair<T, U>& p) {
// 	return os << "{" << p.first << ", " << p.second << "}";
// }

// template <typename T>
// concept IterableContainer = requires(T t) {
// 	begin(t);
// 	end(t);
// } && !same_as<T, string> && !same_as<T, string_view>;

// template<IterableContainer Container>
// ostream& operator<<(ostream& os, const Container& c) {
// 	os << "[";
// 	bool first = true;
// 	for(const auto& elem : c){
// 	if(!first) os << ", ";
//  		os << elem;
// 		first = false;
// 	}
// 	return os << "]";
// }

#define fastio ios_base::sync_with_stdio(false), cin.tie(nullptr);
#define int long long
#define ld long double
#define endl '\n'

void setIO(string s){
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

vector<int> v;
int inversions(int left, int right){

	if(right - left <= 1) return 0;

	int cnt = 0, middle = left + (right - left) / 2;
	cnt += inversions(left, middle);
	cnt += inversions(middle, right);

	vector<int> aux;
	int i = left, j = middle;
	while(i < middle && j < right){
		if(v[i] < v[j]){
			aux.push_back(v[i]);
			i++;
		} else {
			aux.push_back(v[j]);
			j++;
			cnt++;
		}
	}
	while(i < middle){
		aux.push_back(v[i]);
		i++;
	}
	while(j < right){
		aux.push_back(v[j]);
		j++;
	}
	for(i = left, j = 0; i < right; i++, j++){
		swap(v[i], aux[j]);
	}
	return cnt;
}

signed main(){
	fastio;
	setIO("outofplace");
	int n;
	cin >> n;
	v.resize(n);
	for(auto &w:v) cin >> w;
	vector<int> aux = v;
	sort(aux.begin(), aux.end());
	int cnt = 0;
	for(int i = 0; i < n; i++){
		if(v[i] != aux[i]) cnt++;
	}
	cout << cnt - 1 << endl;
	return 0;
}
