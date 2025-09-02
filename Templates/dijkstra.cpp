#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 5;
int n , m;
vector<vector<pair<int,ll>>> adj;
vector<ll> dist;
 
void dijkstra(int src) {
    priority_queue<pair<ll , int>,vector<pair<ll,int>>,greater<>> pq;
    pq.push(make_pair(0,src));
    while(!pq.empty()) {
        int cur = pq.top().second;
        ll d =  pq.top().first;
        pq.pop();
 
        if (d > dist[cur]) continue;
        for (auto u : adj[cur]) {
            if (d + u.second < dist[u.first]) {
                dist[u.first] = d + u.second;
                pq.push(make_pair(dist[u.first], u.first));
            }
        }
    }
}
 
void solve() {
    cin >> n >> m;
    adj.assign(n+1, vector<pair<int,ll>>());
    dist.assign(n+1, LLONG_MAX);
    for (int i = 0 ; i < m; i++) {
        int u , v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v,w));
        // adj[v].push_back(make_pair(u,w));
    }
    dist[1] = 0;
    dijkstra(1);
    for (int i = 1 ; i <= n ; i++) cout << dist[i] << " ";
}
 
 
int main() {
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
