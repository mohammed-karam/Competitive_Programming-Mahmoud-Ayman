#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pt;

// Computes signed area × 2 (no division)
ll twiceArea(const vector<pt> &p) {
    int n = p.size();
    ll area = 0;
    for (int i = 0; i < n; i++) {
        ll x1 = p[i].first, y1 = p[i].second;
        ll x2 = p[(i + 1) % n].first, y2 = p[(i + 1) % n].second;  // calc area using the vertices only
        area += (x1 * y2 - x2 * y1);
    }
    return abs(area);
}

void solve() {
    int n;
    cin >> n;
    vector<pt> p(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i].first >> p[i].second;

    ll twice = twiceArea(p);
    cout << fixed << setprecision(1) << (twice / 2.0) << '\n';
}

int main() {
    // Uncomment for file IO
    // freopen("area.in", "r", stdin);
    // freopen("area.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}

