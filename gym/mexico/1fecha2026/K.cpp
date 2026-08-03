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

struct Point{
	ld x, y;
};

struct Disk{
	ld r;
	Point p;
};

double dist(Point p1, Point p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool inside(Disk disk, Point point){
	if(dist(disk.p, point) <= disk.r) return true;
	return false;
}

	

signed main(){
	fastio;
	int n;
	cin >> n;
	vector<Disk> disk(n);
	Point p;
	cin >> p.x >> p.y;
	for(int i = 0; i < n; i++){
		cin >> disk[i].p.x >> disk[i].p.y >> disk[i].r;
	}

	cout << inside(disk[2], p) << endl;


	return 0;
}
