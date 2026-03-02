void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n+1 ,vector<int>()),adjT(n+1 ,vector<int>());

    for (int i = 0 ;i < m; i++) {
        int u , v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }
    stack<int> st;
    vector<bool> visited(n+1, false);

    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (auto v : adj[u]) {
            if(!visited[v]) {
                dfs(v);
            }
        }
        st.push(u);
    };

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    visited.assign(n+1, false);

    function<void(int node)> dfs3 = [&](int node) {
        visited[node] = true;
        for (auto v : adjT[node]) {
            if (!visited[v]) {
                dfs3(v);
            }
        }
    };

    int scc = 0;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            scc++;
            dfs3(u);
        }
    }
    cout << scc << "\n";
}
