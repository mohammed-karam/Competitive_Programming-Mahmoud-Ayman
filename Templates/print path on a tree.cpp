bool dfs_path(int v, int p, int target, vector<vector<int>> &g, vector<int> &path) {
    path.push_back(v);
    if (v == target) return true;
    for (int u : g[v]) {
        if (u == p) continue;
        if (dfs_path(u, v, target, g, path)) return true;
    }
    path.pop_back();
    return false;
}

vector<int> get_path(int x, int y, vector<vector<int>> &g) {
    vector<int> path;
    dfs_path(x, -1, y, g, path);
    return path;
}
