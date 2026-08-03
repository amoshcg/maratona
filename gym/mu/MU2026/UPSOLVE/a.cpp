#include <bits/stdc++.h>
using namespace std;

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

int main(){
	int n, q;
	cin >> n >> q;
	vector<string> v(n), query(q);
	for(int i = 0; i < n; i++){
		cin >> v[i];
	}

	for(int i = 0; i < q; i++){
		cin >> query[i];
	}

	sort(v.begin(), v.end());
	
	for(int i = 0; i < q; i++){
		auto it = lower_bound(v.begin(), v.end(), query[i]);
		auto it2 = upper_bound(v.begin(), v.end(), query[i] + '~');
		cout << it2 - it << endl;
	}

	return 0;
}
