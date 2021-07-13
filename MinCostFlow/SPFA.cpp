struct MinCostFlow {
    static constexpr int INF = 1e9;
    struct Edge {
        int from, to, cap, cost;
    };
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj, cost, cap;
    MinCostFlow(int n) : n(n) {}
    void addEdge(int u, int v, int cap, int cost) {
        edges.push_back({u, v, cap, cost});
    }
    void shortest_paths(int s, std::vector<int>& d, std::vector<int>& p) {
        d.assign(n, INF);
        d[s] = 0;
        std::vector<bool> inq(n, false);
        std::queue<int> que;
        que.push(s);
        p.assign(n, -1);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inq[u] = false;
            for (int v : adj[u]) {
                if (cap[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                    p[v] = u;
                    if (!inq[v]) {
                        inq[v] = true;
                        que.push(v);
                    }
                }
            }
        }
    }
    int min_cost_flow(int K, int s, int t) {
        adj.assign(n, std::vector<int>());
        cost.assign(n, std::vector<int>(n, 0));
        cap.assign(n, std::vector<int>(n, 0));
        for (Edge e : edges) {
            adj[e.from].push_back(e.to);
            adj[e.to].push_back(e.from);
            cost[e.from][e.to] = e.cost;
            cost[e.to][e.from] = -e.cost;
            cap[e.from][e.to] = e.cap;
        }
        int flow = 0;
        int cost = 0;
        std::vector<int> d, p;
        while (flow < K) {
            shortest_paths(s, d, p);
            if (d[t] == INF)
                break;
            int f = K - flow;
            int cur = t;
            while (cur != s) {
                f = std::min(f, cap[p[cur]][cur]);
                cur = p[cur];
            }
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                cap[p[cur]][cur] -= f;
                cap[cur][p[cur]] += f;
                cur = p[cur];
            }
        }
        if (flow < K)
            return -1;
        else
            return cost;
    }
};
