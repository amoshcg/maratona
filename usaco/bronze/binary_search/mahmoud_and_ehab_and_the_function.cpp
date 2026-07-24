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
#define endl '\n'

signed main(){
	fastio;
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> a(n), b(m), sum;
	int soma_a = 0;

	for(auto &aa:a) cin >> aa;
	for(auto &bb:b) cin >> bb;


	for(int i = 0; i < n; i++){
		if(i % 2 == 0) soma_a += a[i];
		else soma_a -= a[i];
	}

	int sum_x = 0, sum_y = 0; 
	for(int i = 0, j = 0; i < m; i++){
		
		// faz a soma
		if(i % 2 == 0) sum_x += b[i];
		else sum_y += b[i];

		if(i - j + 1 == a.size()){

			if(j % 2 == 0) sum.push_back(sum_x - sum_y);
			else sum.push_back(sum_y - sum_x);

			// remove
			if(j % 2 == 0) sum_x -= b[j];
			else sum_y -= b[j];
			j++;
		}
	}

	sort(sum.begin(), sum.end());

	auto get_closest = [&](int target) {
        auto it = lower_bound(sum.begin(), sum.end(), target);
        int ans = 9e18; // safely large value for long long
        if(it != sum.end()) {
            ans = min(ans, abs(target - *it));
        }
        if(it != sum.begin()) {
            it--;
            ans = min(ans, abs(target - *it));
        }
        return ans;
    };

	// int maximo = 1;
	// while(maximo * 2 < sum.size()){
	// 	maximo *= 2;
	// }

	// int cnt = 0;
	// for(int i = maximo; i >= 1; i /= 2){
	// 	if(cnt + i >= sum.size()) continue;
	// 	if(abs(soma_a - sum[cnt + i]) < abs(soma_a - sum[cnt])){
	// 		cnt += i;
	// 	}
	// }

	// cout << abs(soma_a - sum[cnt]) << endl;

	cout << get_closest(soma_a) << endl;

	while(q--){
		int x, y, val;
		cin >> x >> y >> val;

		if((y - x + 1) % 2 != 0){
            if (x % 2 != 0) soma_a += val;
			else soma_a -= val;
        }

		// cnt = 0;
		// for(int i = maximo; i >= 1; i /= 2){
		// 	if(cnt + i >= sum.size()) continue;
		// 	if(abs(soma_a - sum[cnt + i]) < abs(soma_a - sum[cnt])){
		// 		cnt += i;
		// 	}
		// 	cout << abs(soma_a - sum[cnt]) << endl;
		// }

		cout << get_closest(soma_a) << endl;
	}

	return 0;
}