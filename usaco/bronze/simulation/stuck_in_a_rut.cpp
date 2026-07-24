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
//     begin(t);
//     end(t);
// } && !is_convertible_v<T, string_view>;

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

signed main(){
	fastio;
	int n;
	cin >> n;
	set<pair<int,int>> north, east;
	map<pair<int,int>, int> pos;
	for(int i = 0; i < n; i++){
		char dir;
		int x, y;
		cin >> dir >> x >> y;
		dir == 'N' ? north.insert({x, y}) : east.insert({x,y});
		pos[{x, y}] = i;
	}

	priority_queue<pair<int,pair<pair<int,int>,pair<int,int>>>> pq;
	vector<int> ans(n);
	for(auto [nx, ny]:north){
		for(auto [ex, ey]:east){
			if(ny > ey || ex > nx) continue;
			if(ey - ny > nx - ex) pq.push({-(ey - ny), {{nx, ny}, {ex, ey}}});
			if(nx - ex > ey - ny) pq.push({-(nx - ex), {{ex, ey}, {nx, ny}}});
		}
	}

	while(!pq.empty()){
		int x = pq.top().second.first.first;
		int y = pq.top().second.first.second;
		int blkx = pq.top().second.second.first;
		int blky = pq.top().second.second.second;
		int dis = -pq.top().first;
		
		pq.pop();
		if(ans[pos[{x, y}]]) continue;
        int blocker_dist;
        if (north.count({x, y})) blocker_dist = x - blkx;
        else blocker_dist = y - blky;
		
		// Se a vaca que bloqueia nao foi bloqueda ainda ou
		// nao chegou na posicao onde é bloqueada
        if(ans[pos[{blkx, blky}]] == 0 || ans[pos[{blkx, blky}]] >= blocker_dist) {
            ans[pos[{x, y}]] = dis;
        }
	}

	for(auto a:ans){
		if(a == 0) cout << "Infinity" << endl;
		else cout << a << endl;
	}
	return 0;
}