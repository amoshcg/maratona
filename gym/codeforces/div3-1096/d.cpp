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

struct segtree{
    vector<int>v, lazy;
    int size;

    void init(int n){
        int i=1;
        while(i < n) i*=2;
        size = i;
        v.assign(2*i,0);
        lazy.assign(2*i,0);
    }

    void update(int x){
        lazy[2*x+1] += lazy[x] / 2;
        lazy[2*x+1] += lazy[x] / 2;
        v[x] += lazy[x];
        lazy[x] = 0;
    }

    void add_to_segment(int l, int r, int x, int lx, int rx){

        update(x);

        if(rx <= l || lx >= r) return;
        if(rx <= r && lx >= l) {

            if(rx - lx != 1) {
                lazy[2*x+1] += (rx - lx) / 2;
                lazy[2*x+2] += (rx - lx) / 2;
            }

            v[x] += (rx - lx);
            return;
        }
        int meio = (lx+rx)/2;
        add_to_segment(l, r, 2*x+1, lx, meio);
        add_to_segment(l, r, 2*x+2, meio, rx);
    }

    void add_to_segment(int l, int r){
        add_to_segment(l, r, 0, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx){

        update(x);

        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) {
            return v[x];
        }
        int meio=(lx+rx)/2;
        int s1=query(l,r,2*x+1,lx,meio);
        int s2=query(l,r,2*x+2,meio,rx);
        return s1+s2;
    }

    int query(int l, int r){
        return query(l, r, 0, 0, size);
    }
};

signed main(){
	fastio;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		vector<int> v(n);
		cin >> v;

		segtree seg;

		seg.init(n);

		int ans = 0;

		vector<int> com(n), sem(n);

		for(int i = 0; i < n; i++){
			
			sem[i] = seg.query(v[i], n);
			seg.add_to_segment(0, v[i]);
			com[i] = seg.query(v[i], n);

			// cout << "arr ";
			cout << seg.v << endl;
		}

        for(int i = 0; i < seg.size; i++){
            seg.query(i, i+1);
        }

        cout << seg.v << endl;

		cout << ans << endl;
        cout << com << endl << sem << endl;
	}

	return 0;
}
