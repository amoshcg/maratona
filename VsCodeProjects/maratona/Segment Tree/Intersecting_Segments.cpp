#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define int long signed int long
#define endl "\n"

struct segtree{
	vector<int> v;
	int size;
	void init(int n){
		int i=1;
		while(i < n) i *= 2;
		size = i;
		v.assign(2*i, 0);
	}
	
	void set(int pos, int x, int lx, int rx){
		if(rx - lx == 1){
			v[x]=!v[x];
			return ;
		}
		int meio=(lx+rx)/2;
		if(pos < meio) set(pos, 2*x+1, lx, meio);
		else set(pos, 2*x+2, meio, rx);
		v[x]=v[2*x+1]+v[2*x+2];
	}
	
	void set(int pos){
		set(pos, 0, 0, size);
	}
	
	int count(int l, int r, int x, int lx, int rx){
        // cout << l << " " << r << " " << x << " " << lx << " " << rx << endl;
		if(l >= rx || lx >= r) return 0;
		if(lx >= l && rx <= r) return v[x];
		int meio=(rx+lx)/2;
		return count(l, r, 2*x+1, lx, meio) + count(l, r, 2*x+2, meio, rx);
	}

    int count(int l, int r){
        return count(l, r, 0, 0, size);
    }
};

signed main() {
    // setIO("outofplace");
    int n;
    cin >> n;
    segtree seg;
    seg.init(2*n);
    map<int,int> mp;
    map<int,int> resposta;
    vector<int>v(2*n);
    for(int i=0;i<2*n;i++){
        cin >> v[i];
    }
    for(int i=0;i<2*n;i++){
        if(!mp.count(v[i])) seg.set(i); 
        mp[v[i]] = i;
    }
    for(int i=0;i<2*n;i++){
        int x = v[i];
        if(mp.count(x)) { // found the first one
            seg.set(mp[x]);
            seg.set(i);
            resposta[x] = seg.count(i, mp[x]);
            mp.erase(x);
        }
    }

    segtree seg2;
    seg2.init(2*n);
    map<int,int> mp2;

    for(int i=0;i<2*n;i++){
        int x = v[i];
        if(mp2.count(x)) {
            resposta[x]-=seg2.count(mp2[x]+1,i-1);
            seg2.set(mp2[x]);
        }
        else mp2[x] = i;
    }

    for(auto &[f,s]:resposta) cout << s << " ";
    cout << endl;
    return 0;
}
 


// if we save the second number 















