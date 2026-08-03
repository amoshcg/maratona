#include <bits/stdc++.h>
using namespace std;

// value -> position
// position -> value

vector<int> coord_compression(vector<int> v){
	vector<pair<int,int>> aux(v.size());
	for(int i = 0; i < v.size(); i++){
		aux[i].first = v[i];
		aux[i].second = i;
	}
	sort(aux.begin(), aux.end());
	vector<int> aux2;
	for(int i = 0; i < v.size(); i++){
		aux2.push_back(aux[i].second);
	}
	return aux2;
}



int main(){
	int n; cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n; i++) cin >> v[i];
	vector<int> a = coord_compression(v);
	for(auto aa: a) cout << aa << " ";
	cout << endl;
	return 0;
}
