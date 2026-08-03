#include <bits/stdc++.h>
using namespace std;

struct segtree {
    int size;
    vector<long long> interval;
    vector<long long> lazy_add;
    vector<bool> lazy_set; // Tracks if a node needs to be reset to 0

    void init(int n) {
        int i = 1;
        while (i < n) i *= 2;
        size = i;
        interval.assign(2 * size, 0);
        lazy_add.assign(2 * size, 0);
        lazy_set.assign(2 * size, false);
    }

    void push(int x, int lx, int rx) {
        if (rx - lx == 1) return; // Leaf node, nothing to push down

        int mid = (lx + rx) / 2;
        int left_child = 2 * x + 1;
        int right_child = 2 * x + 2;

        // 1. Resolve pending "Sets to 0" first
        if (lazy_set[x]) {
            lazy_set[left_child] = true;
            lazy_add[left_child] = 0; // Wipe pending additions
            interval[left_child] = 0;

            lazy_set[right_child] = true;
            lazy_add[right_child] = 0; // Wipe pending additions
            interval[right_child] = 0;

            lazy_set[x] = false;
        }

        // 2. Resolve pending "Adds"
        if (lazy_add[x] != 0) {
            lazy_add[left_child] += lazy_add[x];
            interval[left_child] += lazy_add[x] * (mid - lx);

            lazy_add[right_child] += lazy_add[x];
            interval[right_child] += lazy_add[x] * (rx - mid);

            lazy_add[x] = 0;
        }
    }

    void update(int l, int r, int val, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return;
        
        if (lx >= l && rx <= r) {
            lazy_add[x] += val;
            interval[x] += (long long)val * (rx - lx);
            return;
        }
        
        push(x, lx, rx); // Propagate lazy tags downwards
        
        int mid = (lx + rx) / 2;
        update(l, r, val, 2 * x + 1, lx, mid);
        update(l, r, val, 2 * x + 2, mid, rx);
        
        interval[x] = interval[2 * x + 1] + interval[2 * x + 2];
    }

    void update(int l, int r, int val) {
        update(l, r, val, 0, 0, size);
    }

    void reset(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return;
        
        if (lx >= l && rx <= r) {
            lazy_set[x] = true;
            lazy_add[x] = 0; // A reset wipes out any pending additions
            interval[x] = 0;
            return;
        }
        
        push(x, lx, rx); // Propagate lazy tags downwards
        
        int mid = (lx + rx) / 2;
        reset(l, r, 2 * x + 1, lx, mid);
        reset(l, r, 2 * x + 2, mid, rx);
        
        interval[x] = interval[2 * x + 1] + interval[2 * x + 2];
    }

    void reset(int l, int r) {
        reset(l, r, 0, 0, size);
    }

    long long query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return 0;
        
        if (lx >= l && rx <= r) {
            return interval[x];
        }
        
        push(x, lx, rx); // Propagate lazy tags downwards
        
        int mid = (lx + rx) / 2;
        long long res_left = query(l, r, 2 * x + 1, lx, mid);
        long long res_right = query(l, r, 2 * x + 2, mid, rx);
        
        return res_left + res_right;
    }

    long long query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        vector<int> v(n);
        for(auto &w:v) cin >> w;

        segtree seg;
        seg.init(n);

        vector<int> com(n), sem(n);

        vector<bool> valid_com(n, true), valid_sem(n, true);

        for(int i = 0; i < n; i++){
            com[i] = seg.query(v[i], n);
            sem[i] = seg.query(v[i] - 1, n);
            seg.reset(v[i], n);
            seg.update(0, v[i], 1);
        }

        cout << "com" << endl;
        for(int i = 0; i < n; i++){
            cout << com[i] << " ";
        } cout << endl;

        cout << "sem" << endl;
        for(int i = 0; i < n; i++){
            cout << sem[i] << " ";
        } cout << endl;

        cout << *max_element(sem.begin(), sem.end()) << endl;

    }
}