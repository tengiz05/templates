struct BipartiteGraph {
    static constexpr int INF = 1e9;
    int n, m;
    std::vector<std::vector<int>> e;
    std::vector<int> match, dist;
    BipartiteGraph(int n, int m) : n(n), m(m), e(n + m + 1) {}
    void addEdge(int u, int v) {
        e[u + 1].push_back(v + n + 1);
    }
    bool bfs() {
        std::queue<int> que;
        dist.assign(n + 1, INF);
        for (int i = 1; i <= n; i++) {
            if (match[i] == 0) {
                dist[i] = 0;
                que.push(i);
            }
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto v : e[u]) {
                if (dist[match[v]] == INF) {
                    dist[match[v]] = dist[u] + 1;
                    que.push(match[v]);
                }
            }
        }
        return dist[0] != INF;
    }
    bool dfs(int u) {
        if (u == 0)
            return true;
        for (auto v : e[u]) {
            if (dist[match[v]] == dist[u] + 1) {
                if (dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int count() {
        int ans = 0;
        match.assign(n + m + 1, 0);
        while (bfs()) {
            for (int i = 1; i <= n; i++) {
                if (match[i] == 0 && dfs(i)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
