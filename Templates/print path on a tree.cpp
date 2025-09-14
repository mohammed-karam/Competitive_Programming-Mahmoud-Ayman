bool found;
vector<int> ans, path;
 
void dfs(int v, int p, vector<vector<int>> &g, int f){
    path.push_back(v);
    if(v == f){
        ans = path;
        found = true;
        return;
    }
    for(int u: g[v]){
        if(u != p) dfs(u, v, g, f);
        if (found) return;
    }
    path.pop_back();
}
