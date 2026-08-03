#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128_t int128; // Used to prevent overflow during k comparisons

// Function to calculate gcd for fraction reduction
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Comparison for fractions: p1/q1 < p2/q2  =>  p1*q2 < p2*q1
bool is_less(ll p1, ll q1, ll p2, ll q2) {
    return (int128)p1 * q2 < (int128)p2 * q1;
}

void solve() {
    ll a, b, c, k;
    if (!(cin >> a >> b >> c >> k)) return;

    // 1. Binary Search for the side length s
    // We use long double for high precision during the search
    long double low = 0, high = 1e9 + 7;
    for (int i = 0; i < 100; ++i) {
        long double mid = (low + high) / 2.0;
        if (mid < 1e-15) { // Avoid division by zero
            low = mid;
            continue;
        }
        
        int128 na = (int128)(a / mid);
        int128 nb = (int128)(b / mid);
        int128 nc = (int128)(c / mid);
        
        // Check if na * nb * nc >= k
        // We cap the product to avoid overflow even with int128
        int128 total = na * nb * nc;
        
        if (total >= (int128)k) {
            low = mid;
        } else {
            high = mid;
        }
    }

    // 2. Extract the integer segment counts
    ll na = a / low;
    ll nb = b / low;
    ll nc = c / low;

    // Handle edge cases where division results in 0
    if (na == 0) na = 1;
    if (nb == 0) nb = 1;
    if (nc == 0) nc = 1;

    // 3. The optimal s is min(a/na, b/nb, c/nc)
    // We initialize with a/na and compare with others
    ll p = a, q = na;

    if (is_less(b, nb, p, q)) {
        p = b;
        q = nb;
    }
    if (is_less(c, nc, p, q)) {
        p = c;
        q = nc;
    }

    // 4. Simplify the fraction
    ll common = gcd(p, q);
    cout << p / common << " " << q / common << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}