#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_odd_trivial(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    for(int i = 1; i <= n; i++) {
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        if(i <= r) {
            p[i] = min(r - i, p[l + (r - i)]);
        }
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

int mex(vector<int> a){
	int n = a.size();
	for(int i = 0; i < n; i++){
		while(a[i] >= 0 && a[i] < n && a[a[i]] != a[i]){
			swap(a[i],a[a[i]]);
		}
	}
	for(int i = 0; i < n; i++){
		if(a[i] != i){
			return i;
		}
	}
	return n;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        n = 2*n;
        vector<int> v(n + 2);
        v[0] = -1;
        v[n+1] = -2;

        


        for(int i = 1; i <= n; i++){
            cin >> v[i];
        }

        int ans = 0;
        vector<int> count(n + 2);
        for(int i = 1; i < n; i++){
            vector<int> aux;
            while(v[i + count[i]] == v[i - count[i]]){
                aux.push_back(v[i + count[i]]);
                count[i]++;
            }

            ans = max(ans, mex(aux));
        }
        cout << ans << endl;
    }
}