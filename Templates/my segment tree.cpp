#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;

struct Node {
    int sum;

    Node() {
        sum = 0;
    }

    Node(int x) {
        sum = x;
    }

    void change(int x) {
        sum = x;
    }
};

struct SegmentTree {
    int tree_size;
    vector<Node> SegData;

    SegmentTree(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        SegData.assign(tree_size * 2, Node());
    }

    Node merge(Node &lf, Node &ri) {
        Node ans = Node();
        ans.sum = lf.sum + ri.sum;
        return ans;
    }

    void set(int idx, int val, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            SegData[ni].change(val);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx < mid) {
            set(idx, val, 2 * ni + 1, lx, mid);
        } else {
            set(idx, val, 2 * ni + 2, mid, rx);
        }
        SegData[ni] = merge(SegData[2 * ni + 1], SegData[2 * ni + 2]);
    }

    void set(int idx, int val) {
        set(idx, val, 0, 0, tree_size);
    }

    Node get(int l, int r, int ni, int lx, int rx) {
        if (lx >= l && rx <= r) {
            return SegData[ni];
        }
        if (lx >= r || rx <= l) {
            return Node();
        }

        int mid = (lx + rx) / 2;
        Node lf = get(l, r, 2 * ni + 1, lx, mid);
        Node ri = get(l, r, 2 * ni + 2, mid, rx);
        return merge(lf, ri);
    }

    int get(int l, int r) {
        return get(l, r, 0, 0, tree_size).sum;
    }
};

void solve() {
    int n , m; cin >> n >> m;
    vector<int> a(n);
    SegmentTree st(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.set(i, a[i]);
    }
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y;
            st.set(x, y);
        }else {
            int x, y; cin >> x >> y;
            cout << st.get(x, y) << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
