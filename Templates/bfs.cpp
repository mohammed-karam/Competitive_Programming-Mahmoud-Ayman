


// simple bfs
void bfs(int start) {
    queue<int> q;
    q.push(start);            // Start BFS from this node
    levels[start] = 0;        // Distance from start to start is 0
    vis[start] = 1;           // Mark start as visited

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto ch : adj[cur]) {   // Iterate over neighbors
            if (!vis[ch]) {          // If not visited
                vis[ch] = 1;         // Mark visited
                q.push(ch);          // Enqueue child
                levels[ch] = levels[cur] + 1; // Update level
            }
        }
    }
}







// bfs with printing the path. 
void bfs(int start) {
    queue<int> q;
    q.push(start);
    levels[start] = 0;
    vis[start] = 1;
    parent[start] = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int ch: adj[cur]) {
            if (!vis[ch]) {
                q.push(ch);
                vis[ch] = 1;
                levels[ch] = levels[cur] + 1;
                parent[ch] = cur;
            }
        }
    }
    if (parent[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
    }else {
        stack<int> st;
        int cur = n;
        while (cur != -1) {
            st.push(cur);
            cur = parent[cur];
        }
        cout << levels[n] + 1 << endl;
        while (!st.empty()) {
            cout << st.top() << " ";
            st.pop();
        }
    }
}
 
void solve() {
    cin >> n >> m;
    adj.assign(n + 1, vector<int>());
    vis.assign(n + 1, 0);
    levels.assign(n + 1, 0);
    parent.assign(n + 1, -1);
 
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    bfs(1);
 
}
 





// topo sort

void bfs() {
    priority_queue<int, vector<int>, greater<int> > q;

    for (int i = 1; i <= n; i++) {
        if (!inDegree[i]) {
            // no prerequisites
            q.push(i);
        }
    }


    while (!q.empty()) {
        int cur = q.top();
        q.pop();
        topo.push_back(cur);

        for (int i: adj[cur]) {
            if (!vis[i]) {
                inDegree[i]--;
                if (!inDegree[i]) {
                    q.push(i);
                    vis[i] = 1;
                }
            }
        }
    }
}


void solve() {
    cin >> n >> m;
    adj.assign(n + 1, vector<int>());
    levels.assign(n + 1, 0);
    inDegree.assign(n + 1, 0);
    vis.assign(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        // adj[v].push_back(u);
        inDegree[v]++;
    }

    bfs();
    if (topo.size() != n) {
        cout << "Sandro fails." << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << topo[i] << " ";
        }
    }

}








// forming teams 
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> levels(n + 1, -1), vis(n + 1, 0), teams(n + 1);
    vector<vector<int> > adj(n + 1, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    auto bfs = [&](int start) {
        queue<int> q;
        q.push(start);
        levels[start] = 0;
        vis[start] = 1;
        teams[start] = 1;

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            for (int v: adj[cur]) {
                if (!vis[v]) {
                    q.push(v);
                    levels[v] = levels[cur] + 1;
                    vis[v] = 1;
                    teams[v] = 3 - teams[cur];
                }else {
                    if (teams[v] == teams[cur]) {
                        return false;
                    }
                }
            }
        }

        return true;
    };

    bool f = true;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            f &= bfs(i);
        }
    }

    if (f) {
        for (int i = 1; i <= n; i++) {
            cout << teams[i] << " ";
        }
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
}


