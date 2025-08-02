#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define endl '\n'

const int N = 1e5 + 5;
const int mod1 = 1e9 + 7, mod2 = 2e9 + 11;
ll base1 = 31, base2 = 37, pw1[N], pw2[N], inv1[N], inv2[N];

ll powmod(ll a, ll b, ll m) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return ans;
}

void init() {
    pw1[0] = pw2[0] = inv1[0] = inv2[0] = 1;
    int temp1 = powmod(base1, mod1 - 2, mod1);
    int temp2 = powmod(base2, mod2 - 2, mod2);
    for (int i = 1; i < N; i++) {
        pw1[i] = (pw1[i - 1] * base1) % mod1;
        pw2[i] = (pw2[i - 1] * base2) % mod2;
        inv1[i] = (inv1[i - 1] * temp1) % mod1;
        inv2[i] = (inv2[i - 1] * temp2) % mod2;
    }
}

struct HashingSegmentTree {
private:
    vector<pair<int, int>> seg;
    int sz;

    pair<int, int> merge(pair<int, int> l, pair<int, int> r) {
        return { (l.first + r.first) % mod1, (l.second + r.second) % mod2 };
    }

    void update(int l, int r, int node, int idx, int ch) {
        if (l == r) {
            seg[node] = { (ch * pw1[idx]) % mod1, (ch * pw2[idx]) % mod2 };
            return;
        }
        int mid = (l + r) >> 1;
        if (idx <= mid) update(l, mid, 2 * node + 1, idx, ch);
        else update(mid + 1, r, 2 * node + 2, idx, ch);
        seg[node] = merge(seg[2 * node + 1], seg[2 * node + 2]);
    }

    pair<int, int> query(int l, int r, int node, int lx, int rx) {
        if (lx > r || rx < l) return {0, 0};
        if (lx <= l && r <= rx) return seg[node];
        int mid = (l + r) >> 1;
        auto left = query(l, mid, 2 * node + 1, lx, rx);
        auto right = query(mid + 1, r, 2 * node + 2, lx, rx);
        return merge(left, right);
    }

public:
    HashingSegmentTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        seg.assign(sz * 2, {0, 0});
    }

    void update(int idx, char ch) {
        update(0, sz - 1, 0, idx, ch - 'a' + 1);
    }

    pair<int, int> query(int l, int r) {
        auto res = query(0, sz - 1, 0, l, r);
        res.first = (res.first * inv1[l]) % mod1;
        res.second = (res.second * inv2[l]) % mod2;
        return res;
    }
};

bool isPalindrome(HashingSegmentTree &fwd, HashingSegmentTree &bwd, int l, int r, int n) {
    // l and r are 0-based inclusive
    return fwd.query(l, r) == bwd.query(n - r - 1, n - l - 1);
}

void solve() {
    init();
    string s = "abccba";
    int n = s.size();

    HashingSegmentTree forward(n), backward(n);
    for (int i = 0; i < n; ++i) {
        forward.update(i, s[i]);
        backward.update(n - i - 1, s[i]);
    }

    int l = 1, r = 4; // 0-based indexing, substring s[1..4] = "bccb"
    cout << "Checking s[" << l << ".." << r << "] = " << s.substr(l, r - l + 1) << endl;

    if (isPalindrome(forward, backward, l, r, n)) {
        cout << "Substring is palindrome\n";
    } else {
        cout << "Not palindrome\n";
    }

    // Update example: change s[2] to 'x'
    cout << "Updating s[2] = 'x'\n";
    forward.update(2, 'x');
    backward.update(n - 2 - 1, 'x');

    if (isPalindrome(forward, backward, l, r, n)) {
        cout << "After update: Substring is palindrome\n";
    } else {
        cout << "After update: Not palindrome\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
