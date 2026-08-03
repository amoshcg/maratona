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

struct segtree{
    vector<int> sums;
    int tamanho=1;

    // Inicializa a segtree
    void init(int n){
        while(tamanho < n)tamanho*=2;
        sums.assign(2*tamanho,0LL);
    }

    void build(vector<int>&v,int x,int lx,int rx){
        if(rx-lx==1){
            if(lx < v.size()) sums[x] = v[lx];
            return;
        }
        int m=(lx+rx)/2;
        build(v,2*x+1,lx,m);
        build(v,2*x+2,m,rx);
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    segtree(vector<int>&v){
        init(v.size());
        build(v,0,0,tamanho);
    }

    void set(int pos, int valor, int x, int lx, int rx){
        if(rx-lx==1){
            sums[x] = valor;
            return;
        }
        int meio = (lx+rx)/2;
        if(pos < meio){
            set(pos,valor,2*x+1,lx,meio);
        } else {
            set(pos,valor,2*x+2,meio,rx);
        }
        sums[x]=sums[2*x+1]+sums[2*x+2];
    }

    void set(int pos, int valor){
        set(pos, valor, 0, 0, tamanho);
    }

    int get(int pos, int x, int lx, int rx){
        if(rx-lx==1) return sums[x];
        int meio = (lx+rx)/2;
        int val;
        if(pos < meio) val = get(pos,2*x+1,lx,meio);
        else val = get(pos,2*x+2,meio,rx);
        return val;
    }

    int get(int pos){
        return get(pos, 0, 0, tamanho);
    }

    int sum(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return 0;
        if(lx >= l && rx <= r) return sums[x];
        int meio=(lx+rx)/2;
        int s1=sum(l,r,2*x+1,lx,meio);
        int s2=sum(l,r,2*x+2,meio,rx);
        return s1+s2;
    }

    int sum(int l, int r){
        return sum(l, r, 0, 0, tamanho);
    }
};

int aux(vector<int> &v, int esq, int dir){
	vector<int> temp;
	int meio = esq + (dir - esq) / 2, i = esq, j = meio, count = 0;
	while(i < meio && j < dir){
		if(v[i] <= v[j]){
			temp.push_back(v[i++]);
		} else {
			temp.push_back(v[j++]);
			count += (meio - i);
		}
	}

	while(i < meio) temp.push_back(v[i++]);
	while(j < dir) temp.push_back(v[j++]);

	for(int k = 0; k < temp.size(); k++) v[esq + k] = temp[k];
	return count;
}

int recursive(vector<int> &v, int esq, int dir){
	if(dir - esq <= 1) return 0;
	int meio = esq + (dir - esq) / 2;
	int count = recursive(v, esq, meio);
	count += recursive(v, meio, dir);
	count += aux(v, esq, dir);
	return count;
}

int inversions(vector<int> &v){
    return recursive(v, 0, v.size());
}

signed main(){
	fastio;
	int n, q;
	cin >> n >> q;
    vector<int> v(n);
	cin >> v;
    segtree seg(v);
    int inv = inversions(v);
    for(int i = 0; i < q; i++){
        int op, x;
        cin >> op >> x;
        if(op == 1){
            int esq = seg.get(x - 1), dir = seg.get(x);
            if(esq > dir) inv--;
            else inv++;
            seg.set(x, esq);
            seg.set(x - 1, dir);
        } else {
            cout << inv + x * (n + 1) - 2 * seg.sum(0, x) << endl;
        }
    }

	return 0;
}