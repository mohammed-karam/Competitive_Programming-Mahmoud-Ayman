#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Node {
    int ign = 0, val, lazy = 0;
    bool isLazy = 0;

    Node() : val(ign) {
    }

    Node(int x) : val(x) {
    }

    // x is the update value not node number
    void update(int x, int lx, int rx) {
        // val += x * (rx - lx);
        val += x;
        lazy += x;
        isLazy = 1;
    }
};

#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

struct Sagara {
    int n;
    vector<Node> node;

    Sagara(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        node.assign(2 * n, Node());
    }

    Node merge(Node &l, Node &r) {
        Node res = Node();
        res.val = min(l.val, r.val);
        return res;
    }


    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                node[x].val = a[lx];  // leaf = array value
            return;
        }
        build(a, lNode, lx, md);
        build(a, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void build(vector<int> &a) {
        build(a, 0, 0, n);
    }



    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || !node[x].isLazy) return;
        // give the lazy value of the father to his children and make the father's lazy = 0.
        node[lNode].update(node[x].lazy, lx, md);
        node[rNode].update(node[x].lazy, md, rx);
        node[x].lazy = node[x].isLazy = 0;
    }

    void update(int l, int r, int val, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return;
        if (rx <= r && lx >= l) {
            node[x].update(val, lx, rx);
            return;
        }

        update(l, r, val, lNode, lx, md);
        update(l, r, val, rNode, md, rx);

        node[x] = merge(node[lNode], node[rNode]);
    }

    void update(int l, int r, int val) {
        return update(l, r, val, 0, 0, n);
    }

    Node query(int &l, int &r, int x, int lx, int rx) {
        propagate(x, lx, rx);
        if (lx >= r || rx <= l) return Node(((1LL << 60)));
        if (rx <= r && lx >= l) return node[x];

        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);
        return merge(L, R);
    }

    Node query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Sagara s = Sagara(n);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int val;
            cin >> val;
            s.update(l, r, val);
        } else {
            cout << s.query(l, r).val << "\n";
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
