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

int main(){
	fastio;
	int n, m;
	cin >> n >> m;
	vector<int> v(n);
	vector<int> clothes(m);
	cin >> v;

	set<int> diff;
	for(auto p:v){
		diff.insert(p);
	}
	if(diff.size() == v.size()) cout << "Yes" << endl;
	else cout << "No" << endl;

	for(auto p:v){
		p--;
		clothes[p]++;
	}

	int count = 0;
	for(auto c:clothes){
		if(c) count++;
	}
	if(count == clothes.size()) cout << "Yes" << endl;
	else cout << "No" << endl;
	return 0;
}
