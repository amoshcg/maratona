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
#define ld long double

struct ponto{
	ld x, y;
};

ld dis(ponto a, ponto b){
	return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

ld retY(ponto a, ponto b, ld hip){
	if (b.y < a.y) return 0;
	ld proporcao = hip / dis(a, b);
	return proporcao * abs(a.y-b.y) + a.y;
}

signed main(){
	int n, k;
	cin >> n >> k;
	vector<ponto> v(n);
	for(int i = 0; i < n; i++){
		cin >> v[i].x >> v[i].y;
	}
	ld dis_percorrida = 0, y_max = v[0].y;
	for(int i = 1; i < n; i++){
		if(dis_percorrida + dis(v[i], v[i-1]) > k){
			y_max = max(y_max, retY(v[i-1], v[i], k - dis_percorrida));
			break;
		}
		dis_percorrida += dis(v[i], v[i-1]);
		y_max = max(y_max, v[i].y);
	}
	cout << fixed << setprecision(20) << y_max << endl;
	return 0;
}