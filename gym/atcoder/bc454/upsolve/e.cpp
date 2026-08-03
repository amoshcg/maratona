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

// UPSOLVE:
// Basicamente, pinta-se de preto onde i + j e par, o resto pinta-se de branco
// Depois remove o (1, 1), (N, N) e (A, B)
// Assim, sobra N * N - 3 casas

// Removendo (1, 1) e (N, N), preciso fazer um caminho branco -> preto -> ... -> branco
// ou seja, preciso comecar em uma casa branca e terminar em uma casa branca
// entao nas N * N - 3 casas, preciso de uma casa branca a mais (preta + 1 = branca)

// No caso em que N for impar, existe uma casa branca a mais
// Como esse e o estado que eu procuro entao remover mais uma casa eu saio desse estado
// Portanto, e impossivel quando N for impar

// No caso em que N for par, existem duas casas brancas a mais
// Entao se eu remover uma casa branca eu chego no estado em que e possivel

string normal(int n){
	string aux;
	for(int i = 0; i < n - 1; i++) aux += 'R';
	aux += 'D';
	for(int i = 0; i < n - 1; i++) aux += 'L';
	aux += 'D';
	return aux;
}

int main(){
	fastio;
	int t;
	cin >> t;
	while(t--){
		int n, a, b;
		cin >> n >> a >> b;

		if(n % 2 == 0 && (a + b) % 2 == 1){
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
			continue;
		}

		a--, b--;

		string left, right;
		for(int i = 0; i < n / 2 - 1; i++){
			string aux = normal(n);
			if(a >= 2){
				left += aux;
				a -= 2;
			} else {
				// reverse(aux.begin(), aux.end());
				right += aux;
			}
		}

		for(int i = 0; i < n / 2 - 1; i++){
			string aux = "DRUR";
			if(b >= 2){
				left += aux;
				b -= 2;
			} else {
				// reverse(aux.begin(), aux.end());
				right += aux;
			}
		}

		if(a == 0 && b == 1) left += "DR";
		else left += "RD";

		reverse(right.begin(), right.end());

		cout << left + right << endl;
	}
	
	return 0;
}
// Normalmente DRUR
// Se do lado tiver o (A,B) e nao estiver em n faz o DRRU
// Se do lado tiver o (A,B) e estiver em n faz o DR