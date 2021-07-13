struct MinCostFlow {
    static constexpr int INF = 1e9;
    struct Edge {
        int to, cap, cost;
    };
    int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    MinCostFlow(int n) : n(n), g(n) {}
    void addEdge(int u, int v, int cap, int cost) {
        g[u].push_back(e.size());
        e.push_back({v, cap, cost});
        g[v].push_back(e.size());
        e.push_back({u, 0, -cost});
    }
    void SPFA(int s, std::vector<int>& d, std::vector<int>& p, std::vector<int> &par) {
        d.assign(n, INF);
        d[s] = 0;
        std::vector<bool> inq(n, false);
        std::queue<int> que;
        que.push(s);
        p.assign(n, -1);
        par.assign(n, -1);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inq[u] = false;
            for (int i : g[u]) {
                auto [v, cap, cost] = e[i];
                if (cap > 0 && d[v] > d[u] + cost) {
                    d[v] = d[u] + cost;
                    p[v] = i;
                    par[v] = u;
                    if (!inq[v]) {
                        inq[v] = true;
                        que.push(v);
                    }
                }
            }
        }
    }
    int minCost(int K, int s, int t) {
        int flow = 0;
        int cost = 0;
        std::vector<int> d, p, par;
        while (flow < K) {
            SPFA(s, d, p, par);
            if (d[t] == INF)
                break;
            int f = K - flow;
            int cur = t;
            while (cur != s) {
                f = std::min(f, e[p[cur]].cap);
                cur = par[cur];
            }
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                e[p[cur]].cap -= f;
                e[p[cur] ^ 1].cap += f;
                cur = par[cur];
            }
        }
        if (flow < K)
            return -1;
        else
            return cost;
    }
};
