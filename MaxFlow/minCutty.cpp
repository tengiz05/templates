struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<int> E;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t)
            return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
        E.push_back(u);
    }
    std::vector<std::tuple<int, int, int, int>> edges() {
        std::vector<std::tuple<int, int, int, int>> ans;
        for (int i = 0; i < int(e.size()); i += 2) {
            int u = E[i / 2];
            ans.emplace_back(u, e[i].to, e[i].cap + e[i ^ 1].cap, e[i ^ 1].cap);
        }
        return ans;
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
    
    std::vector<bool> vis;
    void mark(int u) {
        vis[u] = true;
        for (int i : g[u]) {
            auto [v, c] = e[i];
            if (c > 0 && !vis[v]) {
                mark(v);
            }
        }
    }
    std::vector<bool> minCut(int s) {
        vis.assign(n, 0);
        mark(s);
        return vis;
    }
};
