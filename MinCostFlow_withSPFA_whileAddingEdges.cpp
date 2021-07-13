
struct MinCostFlow {
    static constexpr int INF = 1e9;
    struct Edge {
        int from, to, cap, cost;
    };
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> e, cost, cap;
    MinCostFlow(int n) : n(n) {}
    void addEdge(int u, int v, int cap, int cost) {
        edges.push_back({u, v, cap, cost});
    }
    void SPFA(int s, std::vector<int>& d, std::vector<int>& p) {
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
            for (int v : e[u]) {
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
    int minCost(int K, int s, int t) {
        e.assign(n, std::vector<int>());
        cost.assign(n, std::vector<int>(n, 0));
        cap.assign(n, std::vector<int>(n, 0));
        for (Edge u : edges) {
            e[u.from].push_back(u.to);
            e[u.to].push_back(u.from);
            cost[u.from][u.to] = u.cost;
            cost[u.to][u.from] = -u.cost;
            cap[u.from][u.to] = u.cap;
        }
        int flow = 0;
        int cost = 0;
        std::vector<int> d, p;
        while (flow < K) {
            SPFA(s, d, p);
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
