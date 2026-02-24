void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n+1);
    for (int i = 0 ;i < n - 1 ; i++) {
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    int mx = 0 , at = 0;
    function<void(int , int ,int)> dfs = [&] (int u , int p , int cost) {
        if (cost > mx) mx = cost , at = u;
        for (auto v : adj[u]) {
            if (v == p) continue;
            dfs (v , u , cost + 1);
        }
    };

    dfs (1 , -1 , 0);
    dfs (at , -1 , 0);
    cout << mx << endl;
}
