#include <bits/stdc++.h>
using namespace std;

#define int long long

int MOD = 1e9 + 7;

typedef vector<vector<int>> Matrix;

Matrix multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return res;
}

Matrix power(Matrix A, long long p) {
    int n = A.size();
    Matrix res(n, vector<long long>(n, 0));
    
    // Initialize res as Identity Matrix
    for (int i = 0; i < n; i++) res[i][i] = 1;

    while (p > 0) {
        if (p & 1) res = multiply(res, A);
        A = multiply(A, A);
        p >>= 1;
    }
    return res;
}

int recurrence(int a, int b, int n){

	if (n == 0) return a;
	if (n == 1) return b;
	
	Matrix M = {{1,1},{1,0}};

	Matrix ans = power(M, n - 1);

	int result = (ans[0][0] * b + ans[0][1] * a) % MOD;

	return result;
}

signed main(){
	int a, b, n;
	cin >> n >> a >> b;
	if(n % 2 == 1) cout << "Samuell" << endl;
	else cout << "Lleumas" << endl;
	cout << recurrence(a, b, n - 1) << endl;
	return 0;
}