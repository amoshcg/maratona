#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
// #define int long signed int long
 
#define endl "\n"
 
/*debug foda mas sem cor*/
namespace dbg {
    template<typename T1, typename T2>
    ostream& operator<<(ostream& os, const pair<T1, T2>& p) { return os << '{' << p.first << ", " << p.second << '}'; }
 
    template<typename T_container, typename T = typename enable_if<!is_same_v<T_container, string> && !is_same_v<T_container, string_view>, typename T_container::value_type>::type>
    ostream& operator<<(ostream& os, const T_container& v) {
        os << '{';
        bool first = true;
        for (const T& x : v) { os << (first ? "" : ", ") << x, first = false; }
        return os << '}';
    }
 
    void debug_out(string_view) { cerr << endl; }
    template<typename H, typename... T>
    void debug_out(string_view s, H h, T... t) {
        auto cpos = s.find(',');
        cerr << s.substr(0, cpos) << " = " << h;
        if constexpr (sizeof...(t) > 0) {
            cerr << ", ";
            auto nx = s.find_first_not_of(" \t\n\r", cpos + 1);
            debug_out(s.substr(nx), t...);
        } else {
            cerr << endl;
        }
    }
}
 
int nxt() { int x; cin >> x; return x; }
void setIO(string s){ freopen((s + ".in").c_str(), "r", stdin); freopen((s + ".out").c_str(), "w", stdout); }
using namespace dbg;
 
/*generic printer de todas as estruturas*/
 
 
// Specialized printer for vector<vector<T>> (matrix)
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        os << matrix[i];
        if (i + 1 < matrix.size()) os << '\n';
    }
    return os;
}
 
 
//-------------PAIR-------------//
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) { 
    os << "(" << p.first << "," << p.second << ")"; 
    return os; 
}
//-------------VECTOR-------------//
template<typename T> ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
//-------------SET-------------//
template<typename T> ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
//-------------MULTISET-------------//
template<typename T> ostream& operator<<(ostream& os, const multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
//-------------QUEUE-------------//
template<typename T> ostream& operator<<(ostream& os, queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
//-------------DEQUE-------------//
template<typename T> ostream& operator<<(ostream& os, deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop_front();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
//-------------STACK-------------//
template<typename T> ostream& operator<<(ostream& os, stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
//-------------PRIORITY_QUEUE-------------//
template<typename T> ostream& operator<<(ostream& os, priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
//-------------MAP-------------//
template<typename K, typename V> ostream& operator<<(ostream& os, const map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
 
template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<typename T> ostream& operator<<(ostream& os, min_pq<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
 
// #define DEBUG
 
#if defined(DEBUG)
    #define bg3 (void)0
    #define debug(...) cerr << "[" << __func__ << ":" << __LINE__ << "]" << " "; debug_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define bg3 ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(NULL);
#define debug(...) (void)0
#endif
 
#define f first
#define s second

vector<int> y(3);
vector<int> x(3);

vector<vector<char>> billboard;
vector<bool> taken(3);
int n;

int is_square(){
	
	for(int i=0;i<3;i++){
		if(!taken[i]) return false;
	}
	
	int height=0, length=0;
	while(billboard[height][0] != 'X') height++;
	while(billboard[0][length] != 'X') length++;
	
	if(height != length) return false;
	
	int  total = 0;
	for(int i=0;i<height;i++){
		for(int j=0;j<length;j++){
			if(billboard[i][j] == 'X') return false;
			total++;
		}
	}
	
	if(total != x[0] * y[0] + x[1] * y[1] + x[2] * y[2]) return false;
	
	return height;
}

void print(){
	int height=0, length=0;
	while(billboard[height][0] != 'X') height++;
	while(billboard[0][length] != 'X') length++;
	
	for(int i=0;i<height;i++){
		for(int j=0;j<length;j++){
			cout << billboard[i][j];
		}
		cout << endl;
	}
}

void solve(int X = 0, int Y = 0){
	
	// cout << billboard << endl << endl;
	
	int tam = is_square();
	if(tam){
		cout << tam << endl;
		print();
		exit(0);
	}
	
	for(int rect=0;rect<3;rect++){
		if(!taken[rect]){
			
			taken[rect]=1;
			
			for(int i=X;i<X+x[rect];i++){
				for(int j=Y;j<Y+y[rect];j++){
					billboard[i][j] = 'A' + rect;
				}
			}
			
			solve(X,Y+y[rect]);
			solve(X+x[rect],Y);
			
			for(int i=X;i<X+x[rect];i++){
				for(int j=Y;j<Y+y[rect];j++){
					billboard[i][j] = 'X';
				}
			}
			
			for(int i=X;i<X+y[rect];i++){
				for(int j=Y;j<Y+x[rect];j++){
					billboard[i][j] = 'A' + rect;
				}
			}
			
			solve(X+y[rect],Y);
			solve(X,Y+x[rect]);
			
			for(int i=X;i<X+y[rect];i++){
				for(int j=Y;j<Y+x[rect];j++){
					billboard[i][j] = 'X';
				}
			}
			
			taken[rect] = 0;
		}
	}
}
 
signed main() {
    // setIO("outofplace");
    bg3;
    for(int i=0;i<3;i++){
    		cin >> x[i] >> y[i];
    		n = max({n,x[i],y[i]});
    }
    
    billboard.assign(4*n, vector<char>(4*n, 'X'));
    
    solve();
    
    cout << "-1" << endl;
    
    return 0;
}






















