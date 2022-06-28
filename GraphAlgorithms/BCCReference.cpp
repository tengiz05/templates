
    vector<bool> vis(n);
    stack<int> st;
    int S = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        in[u] = f[u] = timeStamp++;
        vis[u] = true;
        st.push(u);
        for (auto [v, i] : adj[u]) {
            if (!vis[v]) {
                dfs(v, i);
                f[u] = min(f[u], f[v]);
            } else if (i != p) {
                f[u] = min(f[u], f[v]);
            }
        }
        if (f[u] == in[u]) {
            int x;
            do {
                x = st.top();
                st.pop();
                c[x] = S;
            } while (x != u);
            S++;
        }
    };
