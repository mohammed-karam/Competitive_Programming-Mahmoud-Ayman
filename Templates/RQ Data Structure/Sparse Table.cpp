#include<bits/stdc++.h>
using namespace std;
#define ll long long

// ---------------------------------------------------------
// REUSABLE SPARSE TABLE TEMPLATE
// ---------------------------------------------------------
template<typename T>
struct SparseTable {
    int n, K;
    vector<vector<T>> st;
    vector<int> Log;

    // 1. Define your merge operation here (min, max, gcd, etc.)
    T merge(T a, T b) {
        return min(a, b); 
    }

    // Constructor builds the table in O(N log N)
    SparseTable(const vector<T>& a) {
        n = a.size();
        
        // Precompute logarithms
        Log.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            Log[i] = Log[i >> 1] + 1;
        }
        
        K = Log[n] + 1;
        st.assign(n, vector<T>(K));
        
        // Base case: intervals of length 1
        for (int i = 0; i < n; i++) {
            st[i][0] = a[i];
        }
        
        // Build the rest of the table
        for (int pw = 1; pw < K; pw++) {
            for (int i = 0; i + (1 << pw) <= n; i++) {
                st[i][pw] = merge(st[i][pw - 1], st[i + (1 << (pw - 1))][pw - 1]);
            }
        }
    }

    // 2. O(1) Query for IDEMPOTENT operations (min, max, gcd, bitwise AND/OR)
    T query_O1(int l, int r) {
        if (l > r) swap(l, r); // Safety check
        int sz = r - l + 1;
        int pw = Log[sz];
        return merge(st[l][pw], st[r - (1 << pw) + 1][pw]);
    }

    // 3. O(log N) Query for NON-IDEMPOTENT operations (like sum)
    // Note: If you use this for sum, change neutral_element to 0.
    T query_log(int l, int r, T neutral_element = LLONG_MAX) {
        if (l > r) return neutral_element;
        T ret = neutral_element;
        for (int i = K - 1; i >= 0; i--) {
            if ((1 << i) <= r - l + 1) {
                ret = merge(ret, st[l][i]);
                l += (1 << i);
            }
        }
        return ret;
    }
};
// ---------------------------------------------------------

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<ll> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    // Instantiate your sparse table (you can now create as many as you want!)
    SparseTable<ll> mySparseTable(s);
    
    while (q--) {
        int l, r; 
        cin >> l >> r;
        l--; r--; // Convert to 0-based indexing
        
        // Use query_O1 for minimum
        cout << mySparseTable.query_O1(l, r) << '\n';
    }
    
    return 0;
}
